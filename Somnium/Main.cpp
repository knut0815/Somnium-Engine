#include <thread>
#include <iostream>
#include <set>

#ifdef WEB_BUILD
	#include <emscripten.h>
#endif

#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderers/BatchRenderer.h"
#include "Graphics/Renderers/SerialRenderer.h"
#include "Graphics/RenderableObject.h"
#include "Graphics/Camera.h"
#include "Graphics/Font.h"
#include "DebugTools/ReferenceGrid.h"

#include "Audio/AudioEngine.h"
#include "Utilities/FileUtilities.h"

using namespace std;
using namespace Somnium;
using namespace Graphics;
using namespace Maths;
using namespace Audio;

void calculateFPS(unsigned int &frameRate, float &timePerFrame)
{
	static double lastTime = glfwGetTime();
	static int nbFrames = 0;

	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) {
		frameRate = nbFrames;
		timePerFrame = 1000.0 / double(nbFrames);

		nbFrames = 0;
		lastTime += 1.0;
	}
}

#ifdef WEB_BUILD
static void startMain(void *mainFunction)
{
	(*(function<void()>*)mainFunction)();
}
#endif

int main(int argc, char** argv) {
	cout << "SOMNIUM by LUMACAL Software Group - Built " << __TIMESTAMP__ << endl << endl;

	std::set<std::string> flags = std::set<std::string>();
	for (int f = 0; f < argc; f++)
		flags.insert(argv[f]);

	Window myWindow("Somnium Engine", 1920, 1080, (flags.find("-f") != flags.end()) || (flags.find("--fullscreen") != flags.end()));
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Sound demo
    //AudioEngine au;
    //thread at{&AudioEngine::playSound, this, "Synth1.wav"};
    //at.join();
  //  AudioEngine au;
   // au.playSound("Synth1.wav");

	cout << "---------RUNNING GAME LOOP---------" << endl;

//	Camera mainCamera = Camera(Matrix4::orthographic(-myWindow.getAspectRatio() / 2.0f, myWindow.getAspectRatio() / 2.0f, -0.5f, 0.5f, 1.0f, 100.0f));
	Camera mainCamera = Camera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0,0,0), Vector3(180, 90, 0));

	Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());
	Shader* shader = new Shader("Resources/Graphics/Shaders/GL/PBR/basic.vert", "Resources/Graphics/Shaders/GL/PBR/basic.frag");
	Shader* textShader = new Shader("Resources/Graphics/Shaders/GL/Basic/basicText.vert", "Resources/Graphics/Shaders/GL/Basic/basicText.frag");
	
	shader->enable();
	shader->setVector3("albedo", Maths::Vector3(1, 1, 1));
	shader->setFloat("ao", 0.01);
	
	shader->setFloat("metallic", 0.9f);
	shader->setFloat("roughness", 0.1f);

	shader->setVector3("lightPositions[1]", Maths::Vector3(-10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[2]", Maths::Vector3(10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[3]", Maths::Vector3(-10.0f, -10.0f, 10.0f));
	shader->setVector3("lightPositions[4]", Maths::Vector3(10.0f, -10.0f, 10.0f));

	shader->setVector3("lightColors[1]", Maths::Vector3(300.0f, 300.0f, 300.0f));
	shader->setVector3("lightColors[2]", Maths::Vector3(300.0f, 300.0f, 300.0f));
	shader->setVector3("lightColors[3]", Maths::Vector3(300.0f, 300.0f, 300.0f));
	shader->setVector3("lightColors[4]", Maths::Vector3(300.0f, 300.0f, 300.0f));
	shader->setVector3("lightColors[5]", Maths::Vector3(500.0f, 500.0f, 500.0f));
	
/*
#ifdef WEB_BUILD
	Shader* shader = new Shader("Resources/Graphics/Shaders/GLES/Basic/basic.vert", "Resources/Graphics/Shaders/GLES/Basic/basic.frag");
	Shader* textShader = new Shader("Resources/Graphics/Shaders/GLES/Basic/basicText.vert", "Resources/Graphics/Shaders/GLES/Basic/basicText.frag");

#else
	Shader* shader = new Shader("Resources/Graphics/Shaders/GL/Basic/basic.vert", "Resources/Graphics/Shaders/GL/Basic/basic.frag");
	Shader* textShader = new Shader("Resources/Graphics/Shaders/GL/Basic/basicText.vert", "Resources/Graphics/Shaders/GL/Basic/basicText.frag");

#endif
*/

	textShader->enable();
	textShader->setMatrix4("projection", Matrix4::orthographic(0, myWindow.getWidth(),0, myWindow.getHeight(), -1.0f, 100.0f));

#ifdef ENABLE_DEBUG_CAMERA
	#ifdef WEB_BUILD
		Shader* naviShader = new Shader("Resources/Graphics/Shaders/GLES/Debug/navigation.vert", "Resources/Graphics/Shaders/GLES/Debug/navigation.frag");	
	#else
		Shader* naviShader = new Shader("Resources/Graphics/Shaders/GL/Debug/navigation.vert", "Resources/Graphics/Shaders/GL/Debug/navigation.frag");
	#endif
	DebugTools::ReferenceGrid grid = DebugTools::ReferenceGrid(5, Maths::Vector3(10000), *naviShader);

	UI::UIText
		*fpsCount = new UI::UIText("FPS", arial, Maths::Vector2(0, myWindow.getHeight() - 25), textShader),
		*camPos = new UI::UIText("CAM POS", arial, Maths::Vector2(0, myWindow.getHeight() - 50), textShader),
		*camRot = new UI::UIText("CAM ROT", arial, Maths::Vector2(0, myWindow.getHeight() - 75), textShader),
		*camFOV = new UI::UIText("CAM FOV", arial, Maths::Vector2(0, myWindow.getHeight() - 100), textShader),
		*engName = new UI::UIText("SOMNIUM ENGINE", arial, Maths::Vector2(myWindow.getWidth() - 225, myWindow.getHeight() - 25), textShader),
		*engVer = new UI::UIText("DEVELOPMENT BUILD", arial, Maths::Vector2(myWindow.getWidth() - 270, myWindow.getHeight() - 50), textShader);

	camPos->setScale(0.5f);
	camRot->setScale(0.5f);
	camFOV->setScale(0.5f);
	engName->setScale(0.5f);
	engVer->setScale(0.5f);
	fpsCount->setScale(0.5f);

	mainCamera.addUIObject("CameraPosition", camPos);
	mainCamera.addUIObject("CameraOrientation", camRot);
	mainCamera.addUIObject("FieldOfView", camFOV);

	mainCamera.addUIObject("EngineName", engName);
	mainCamera.addUIObject("EngineVersion", engVer);
	mainCamera.addUIObject("FrameRate", fpsCount);
#endif

	Matrix4 view = Matrix4::identity();

	Mesh monkeyMesh = Mesh(Utilities::loadOBJ("Resources/Graphics/Objects/Monkey.obj", *shader));
	monkeyMesh.translate(0,0,-50);

	shader->setVector3("CamPos", mainCamera.getPosition());

	std::vector<RenderableObject*> objects;

	Mesh* monkey = new Mesh(monkeyMesh);

	for(int i = 0; i < 250; i++)
		objects.push_back(new RenderableObject(new Mesh(monkeyMesh)));

	Renderers::SerialRenderer* renderer = new Renderers::SerialRenderer(myWindow, mainCamera);

	shader->enable();

	for (RenderableObject* object : objects)
	{
		float scale = (float)rand() / RAND_MAX;
		object->getMesh()->scale(scale, scale, scale);
		object->getMesh()->translate((float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * 10 * ((rand() % 2) ? 1 : -1), (float)rand() / RAND_MAX * -1.0f);
	}

#ifdef WEB_BUILD
	function<void()> webMain = [&]() {
#else
	while (!myWindow.isClosed())
	{
#endif
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

		//3. Draw objects
		//renderer->endMapping();
		renderer->flushQueue();

#ifdef ENABLE_DEBUG_CAMERA
		naviShader->enable();
		naviShader->setMatrix4("projectionMatrix", mainCamera.getProjection());
		naviShader->setMatrix4("viewMatrix", mainCamera.getView());
		grid.draw();
#endif

		shader->enable();
		shader->setVector3("lightPositions[5]", mainCamera.getPosition());

		//4. Post Processing
		myWindow.update();
#ifdef ENABLE_DEBUG_CAMERA
		static unsigned int fps;
		static float timePerFrame;
		static char fpsUI[128];

		snprintf(fpsUI, 128, "FPS %d (%f ms)", fps, timePerFrame);

		calculateFPS(fps, timePerFrame);
		fpsCount->setText(fpsUI);
#endif
	};
#ifdef WEB_BUILD
	emscripten_set_main_loop_arg(startMain, &webMain, false, true);
#endif

	cout << "-----------------------------------" << endl;

	return 0;
}
