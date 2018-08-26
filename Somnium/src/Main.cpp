#include <iostream>
#include <set>

#ifdef WEB_BUILD
	#include <emscripten.h>
#endif

#include "Audio/AudioEngine.h"

#include "Graphics/Window.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderers/BatchRenderer.h"
#include "Graphics/Renderers/SerialRenderer.h"
#include "Graphics/RenderableObject.h"
#include "Graphics/Camera.h"
#include "Graphics/Font.h"

#include "Graphics/PostProcessing/PostProcessor.h"
#include "Graphics/PostProcessing/GaussianBlur.h"
#include "Graphics/PostProcessing/BrightFilter.h"
#include "Graphics/PostProcessing/Bloom.h"

#include "Utilities/FileUtilities.h"
#include "Utilities/FrameRateUtilities.h"
#include "Utilities/DebugTools/ReferenceGrid.h"
#include "Utilities/DebugUtilities.h"

using namespace Somnium;
using namespace Graphics;
using namespace Maths;
using namespace Audio;

#ifdef WEB_BUILD
static void startMain(void *mainFunction)
{
	(*(function<void()>*)mainFunction)();
}
#endif

int main(int argc, char** argv) {
	Utilities::Debug::printWelcomeMessage();

	std::set<std::string> flags = std::set<std::string>();
	for (int f = 0; f < argc; f++) flags.insert(argv[f]);

	Window myWindow("Somnium Engine", 1920, 1080, (flags.find("-f") != flags.end()) || (flags.find("--fullscreen") != flags.end()));

	Buffers::FrameBuffer::setWindow(&myWindow);

	PostProcessing::PostProcessor::initialise();
	Camera mainCamera = Camera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0,0,0), Vector3(180, 90, 0));

	Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());

	Shaders::Shader* shader = new Shaders::Shader("Resources/Graphics/Shaders/PBR/basic.vs", "Resources/Graphics/Shaders/PBR/basic.fs");
	Shaders::Shader* textShader = new Shaders::Shader("Resources/Graphics/Shaders/Basic/basicText.vs", "Resources/Graphics/Shaders/Basic/basicText.fs");

	#ifdef ENABLE_DEBUG_CAMERA
		Shaders::Shader* naviShader = new Shaders::Shader("Resources/Graphics/Shaders/Debug/navigation.vs", "Resources/Graphics/Shaders/Debug/navigation.fs");
	#endif
	
	textShader->enable();
	textShader->setMatrix4("projection", Matrix4::orthographic(0, myWindow.getWidth(), 0, myWindow.getHeight(), -1.0f, 100.0f));

	shader->enable();
	shader->setVector3("albedo", Maths::Vector3(1, 1, 1));
	shader->setFloat("ao", 0.01);
	shader->setFloat("metallic", 0.9f);
	shader->setFloat("roughness", 0.1f);

	shader->setVector3("lightPositions[0]", Maths::Vector3(-10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[1]", Maths::Vector3(10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[2]", Maths::Vector3(-10.0f, -10.0f, 10.0f));
	shader->setVector3("lightPositions[3]", Maths::Vector3(10.0f, -10.0f, 10.0f));

	char buff[24];
	for (unsigned int i = 0; i < 5; i++)
	{
		sprintf(buff, "lightColors[%d]", i);
		shader->setVector3(buff, Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	}

	Buffers::FrameBuffer frameBuffer;

#ifdef ENABLE_DEBUG_CAMERA
	Utilities::Debug::initialiseDebugCamera(myWindow.getWidth(), myWindow.getHeight(), &mainCamera, arial, textShader);
	Utilities::Debug::initialiseReferenceGrid(naviShader, 5, Maths::Vector3(10000));
#endif

	Matrix4 view = Matrix4::identity();

	Mesh monkeyMesh = Mesh(Utilities::File::loadOBJ("Resources/Graphics/Objects/Monkey.obj", *shader));
	monkeyMesh.translate(0,0,-50);

	std::vector<RenderableObject*> objects;

	for(int i = 0; i < 50; i++)
		objects.push_back(new RenderableObject(new Mesh(monkeyMesh)));

	Renderers::SerialRenderer* renderer = new Renderers::SerialRenderer(myWindow, mainCamera);

	for (RenderableObject* object : objects)
	{
		float scale = (float)rand() / RAND_MAX;
		object->getMesh()->scale(scale, scale, scale);
		object->getMesh()->translate((float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * -1.0f);
	}

	cout << "---------RUNNING GAME LOOP---------" << endl;

#ifdef WEB_BUILD
	function<void()> webMain = [&]() {
#else
	while (!myWindow.isClosed())
	{
#endif
		Utilities::FrameRate::startFrameCounting();

		myWindow.clear();

		int x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		//2. Update objects

		static float monkeyZPos = 0;
		static float offset = -0.001f;

		if (monkeyZPos >= 0)  offset = -0.001f;
		else if (monkeyZPos <= -10) offset = 0.001f;

		monkeyZPos += offset;

		//renderer->beginMapping();

		for (RenderableObject* object : objects)
		{
			object->getMesh()->translate(0, 0, offset);
			object->getMesh()->setOrientation(0.01f, 0.01f, 0.01f); //TODO: Setup a glPop/glPushMatrix() functionality system
			renderer->submitToQueue(object);
		}

		renderer->updateCamera();
		shader->enable();
		shader->setVector3("lightPositions[4]", mainCamera.getPosition());
		//3. Draw objects
		//renderer->endMapping();
		frameBuffer.clear();
		frameBuffer.bind();

		renderer->render(true);

		frameBuffer.unbind();

		//DO POST PROCESSING
		PostProcessing::PostProcessor::submitToQueue(Graphics::PostProcessing::Bloom::getInstance());

		PostProcessing::PostProcessor::process(&frameBuffer);

		frameBuffer.bindColourTexture();

		Graphics::PostProcessing::PostProcessor::drawScreen();

		Utilities::FrameRate::update();
#ifdef ENABLE_DEBUG_CAMERA
		Utilities::Debug::drawReferenceGrid();
		Utilities::Debug::updateDebugCamera();
#endif

		//4. Post Processing
		mainCamera.updateUI();
		mainCamera.drawUI();
		myWindow.update();

		Utilities::FrameRate::limitFrameRate(60);
	};
#ifdef WEB_BUILD
	emscripten_set_main_loop_arg(startMain, &webMain, false, true);
#endif

	cout << "-----------------------------------" << endl;

	return 0;
}
