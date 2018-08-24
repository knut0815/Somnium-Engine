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

	Camera mainCamera = Camera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0,0,0), Vector3(180, 90, 0));

	Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());

	Shaders::Shader blurShader = Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/gaussianBlur.frag");
	Shaders::Shader bloomShader = Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/bloom.frag");
	Shaders::Shader screenShader = Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/texture2D.vert", "Resources/Graphics/Shaders/GL/Basic/texture2D.frag");
	Shaders::Shader brightFilter = Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert","Resources/Graphics/Shaders/GL/Post-Processing/Filters/brightnessFilter.frag");

#ifdef WEB_BUILD
	Shaders::Shader* shader = new Shaders::Shader("Resources/Graphics/Shaders/GLES/PBR/basic.vert", "Resources/Graphics/Shaders/GLES/PBR/basic.frag");
	Shaders::Shader* textShader = new Shaders::Shader("Resources/Graphics/Shaders/GLES/Basic/basicText.vert", "Resources/Graphics/Shaders/GLES/Basic/basicText.frag");

	#ifdef ENABLE_DEBUG_CAMERA
		Shaders::Shader* naviShader = new Shaders::Shader("Resources/Graphics/Shaders/GLES/Debug/navigation.vert", "Resources/Graphics/Shaders/GLES/Debug/navigation.frag");
	#endif
#else
	Shaders::Shader* shader = new Shaders::Shader("Resources/Graphics/Shaders/GL/PBR/basic.vert", "Resources/Graphics/Shaders/GL/PBR/basic.frag");
	Shaders::Shader* textShader = new Shaders::Shader("Resources/Graphics/Shaders/GL/Basic/basicText.vert", "Resources/Graphics/Shaders/GL/Basic/basicText.frag");
	#ifdef ENABLE_DEBUG_CAMERA
		Shaders::Shader* naviShader = new Shaders::Shader("Resources/Graphics/Shaders/GL/Debug/navigation.vert", "Resources/Graphics/Shaders/GL/Debug/navigation.frag");
	#endif
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

	char buff[256];
	for (unsigned int i = 0; i < 5; i++)
	{
		sprintf(buff, "lightColors[%d]", i);
		shader->setVector3(buff, Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	}

	Buffers::FrameBuffer frameBuffer[3] = { Buffers::FrameBuffer(1) };

#ifdef ENABLE_DEBUG_CAMERA
	Utilities::Debug::initialiseDebugCamera(myWindow.getWidth(), myWindow.getHeight(), &mainCamera, arial, textShader);
	Utilities::Debug::initialiseReferenceGrid(naviShader, 5, Maths::Vector3(10000));
#endif

	static float screen[] = {
					-1.0f, -1.0f,
					1.0f, -1.0f,
					1.0f, 1.0f,
					-1.0f, 1.0f
			};

	static float screenTexCoords[] = {
						0, 0,
						1, 0,
						1, 1,
						0, 1
				};

	Buffers::VertexArray screenVAO = Buffers::VertexArray();
	Buffers::IndexBuffer screenIBO = Buffers::IndexBuffer( {0, 1, 2, 2, 3, 0} );

	screenVAO.addBuffer(new Buffers::VertexBuffer(screen, 4, 2, GL_STATIC_DRAW), SHADER_POSITION_INDEX);
	screenVAO.addBuffer(new Buffers::VertexBuffer(screenTexCoords, 4, 2, GL_STATIC_DRAW), SHADER_TEXTURE_COORDINATE_INDEX);

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

		for(unsigned int i = 0; i < sizeof(frameBuffer) / sizeof(Buffers::FrameBuffer); i++)
			frameBuffer[i].clear();

		frameBuffer[0].bind();

		renderer->render(true);
		
		//DO POST PROCESSING
		glDisable(GL_DEPTH_TEST);

		screenVAO.bind();
		screenIBO.bind();

		brightFilter.enable();
		glBindTexture(GL_TEXTURE_2D, frameBuffer[0].getColourTexture());
		
		frameBuffer[1].bind();

		screenVAO.draw(screenIBO.getCount());
		frameBuffer[1].draw();

		blurShader.enable();
		bool horz = true;

		for(unsigned int i = 0; i < 25; i++){
			blurShader.setInt("horizontal", horz);
			frameBuffer[horz + 1].bind();

			glBindTexture(GL_TEXTURE_2D, frameBuffer[(!horz) + 1].getColourTexture());

			screenVAO.draw(screenIBO.getCount());

			horz = !horz;
		}

		frameBuffer[1].unbind();

		bloomShader.enable();
		bloomShader.setInt("original", 1);
		bloomShader.setInt("blurred", 2);
		bloomShader.setFloat("exposure", 1);

		frameBuffer[0].bindColourTexture(0, GL_TEXTURE1);
		frameBuffer[!horz + 1].bindColourTexture(0, GL_TEXTURE2);

		glActiveTexture(GL_TEXTURE0);

		screenVAO.draw(screenIBO.getCount());

		screenIBO.unbind();
		screenVAO.unbind();

		glEnable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, 0);
		//renderer->clear();
	//	renderer->render(true);

#ifdef ENABLE_DEBUG_CAMERA
		Utilities::FrameRate::update();
		Utilities::Debug::drawReferenceGrid();
		Utilities::Debug::updateDebugCamera();
#endif

		//4. Post Processing
		mainCamera.updateUI();
		mainCamera.drawUI();
		myWindow.update();

		Utilities::FrameRate::limitFrameRate();
	};
#ifdef WEB_BUILD
	emscripten_set_main_loop_arg(startMain, &webMain, false, true);
#endif

	cout << "-----------------------------------" << endl;

	return 0;
}
