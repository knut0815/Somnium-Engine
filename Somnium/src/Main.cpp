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

const unsigned int frameRateLimit = 60;

void pauseDrawing(unsigned int elapsed)
{
	double  sleep = ((1000000.0 / frameRateLimit) - elapsed) / 1000000.0,
			start = glfwGetTime();

	while ((glfwGetTime() - start) < sleep);
}

void calculateFPS(unsigned int &frameRate, float &timePerFrame)
{
	static double lastTime = glfwGetTime();
	static int nbFrames = 0;

	nbFrames++;

	if (glfwGetTime() - lastTime >= 1.0) {
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

	Buffers::FrameBuffer::setWindow(&myWindow);

    //Sound demo
    //AudioEngine au;
    //thread at{&AudioEngine::playSound, this, "Synth1.wav"};
    //at.join();
	//AudioEngine au;
    //au.playSound("Synth1.wav");

	cout << "---------RUNNING GAME LOOP---------" << endl;

//	Camera mainCamera = Camera(Matrix4::orthographic(-myWindow.getAspectRatio() / 2.0f, myWindow.getAspectRatio() / 2.0f, -0.5f, 0.5f, 1.0f, 100.0f));
	Camera mainCamera = Camera(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 1000.0f, false, Vector3(0,0,0), Vector3(180, 90, 0));

	Font* arial = new Font("Resources/Graphics/Fonts/arial.ttf", myWindow.getFreeTypeInstance());

	Shader blurShader = Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/gaussianBlur.frag");
	Shader bloomShader = Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert", "Resources/Graphics/Shaders/GL/Post-Processing/bloom.frag");
	Shader screenShader = Shader("Resources/Graphics/Shaders/GL/Basic/texture2D.vert", "Resources/Graphics/Shaders/GL/Basic/texture2D.frag");
	Shader brightFilter = Shader("Resources/Graphics/Shaders/GL/Basic/passthrough2D.vert","Resources/Graphics/Shaders/GL/Post-Processing/Filters/brightnessFilter.frag");

#ifdef WEB_BUILD
	Shader* shader = new Shader("Resources/Graphics/Shaders/GLES/PBR/basic.vert", "Resources/Graphics/Shaders/GLES/PBR/basic.frag");
	Shader* textShader = new Shader("Resources/Graphics/Shaders/GLES/Basic/basicText.vert", "Resources/Graphics/Shaders/GLES/Basic/basicText.frag");

	#ifdef ENABLE_DEBUG_CAMERA
		Shader* naviShader = new Shader("Resources/Graphics/Shaders/GLES/Debug/navigation.vert", "Resources/Graphics/Shaders/GLES/Debug/navigation.frag");
	#endif
#else
	Shader* shader = new Shader("Resources/Graphics/Shaders/GL/PBR/basic.vert", "Resources/Graphics/Shaders/GL/PBR/basic.frag");
	Shader* textShader = new Shader("Resources/Graphics/Shaders/GL/Basic/basicText.vert", "Resources/Graphics/Shaders/GL/Basic/basicText.frag");
	#ifdef ENABLE_DEBUG_CAMERA
		Shader* naviShader = new Shader("Resources/Graphics/Shaders/GL/Debug/navigation.vert", "Resources/Graphics/Shaders/GL/Debug/navigation.frag");
	#endif
#endif
	
	shader->enable();
	shader->setVector3("albedo", Maths::Vector3(1, 1, 1));
	shader->setFloat("ao", 0.01);
	shader->setFloat("metallic", 0.9f);
	shader->setFloat("roughness", 0.1f);

	shader->setVector3("lightPositions[0]", Maths::Vector3(-10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[1]", Maths::Vector3(10.0f, 10.0f, 10.0f));
	shader->setVector3("lightPositions[2]", Maths::Vector3(-10.0f, -10.0f, 10.0f));
	shader->setVector3("lightPositions[3]", Maths::Vector3(10.0f, -10.0f, 10.0f));

	shader->setVector3("lightColors[0]", Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	shader->setVector3("lightColors[1]", Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	shader->setVector3("lightColors[2]", Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	shader->setVector3("lightColors[3]", Maths::Vector3(3000.0f, 3000.0f, 3000.0f));
	shader->setVector3("lightColors[4]", Maths::Vector3(100.0f, 100.0f, 100.0f));

	textShader->enable();
	textShader->setMatrix4("projection", mainCamera.getProjection());
	screenShader.setMatrix4("projection", mainCamera.getProjection());
	//blurShader.setMatrix4("projection", mainCamera.getProjection());

	Buffers::FrameBuffer frameBuffer[3] = { Buffers::FrameBuffer(1) };

#ifdef ENABLE_DEBUG_CAMERA
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

	Mesh monkeyMesh = Mesh(Utilities::loadOBJ("Resources/Graphics/Objects/Monkey.obj", *shader));
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

#ifdef WEB_BUILD
	function<void()> webMain = [&]() {
#else
	while (!myWindow.isClosed())
	{
#endif

		double startTime = glfwGetTime();

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

		frameBuffer[0].bind();

		glClearColor(0.f,0.f,0.f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		renderer->render(true);

		//DO POST PROCESSING
		glDisable(GL_DEPTH_TEST);

		screenVAO.bind();
		screenIBO.bind();

		brightFilter.enable();
		glBindTexture(GL_TEXTURE_2D, frameBuffer[0].getColourTexture());
		frameBuffer[1].bind();
		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		screenVAO.draw(screenIBO.getCount());
		frameBuffer[1].draw();

		blurShader.enable();
		bool horz = true;

		for(unsigned int i = 0; i < 10; i++){
			blurShader.setInt("horizontal", horz);
			frameBuffer[(!horz) + 1].bind();

			//glClearColor(0.f,0.f,0.f,1.0f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glBindTexture(GL_TEXTURE_2D, frameBuffer[(!horz) + 1].getColourTexture());

			screenVAO.draw(screenIBO.getCount());

			//frameBuffer[horz + 1].draw();
			horz = !horz;
		}

		frameBuffer[1].unbind();

		bloomShader.enable();
		bloomShader.setInt("original", 0);
		bloomShader.setInt("blurred", 1);
		bloomShader.setFloat("exposure", 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frameBuffer[0].getColourTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, frameBuffer[!horz + 1].getColourTexture());

		screenVAO.draw(screenIBO.getCount());

		screenIBO.unbind();
		screenVAO.unbind();

		glEnable(GL_DEPTH_TEST);
	//	renderer->render(true);

#ifdef ENABLE_DEBUG_CAMERA
		naviShader->enable();
		naviShader->setMatrix4("projectionMatrix", mainCamera.getProjection());
		naviShader->setMatrix4("viewMatrix", mainCamera.getView());
		grid.draw();

		static unsigned int fps;
		static float timePerFrame;
		static char fpsUI[128];

		snprintf(fpsUI, 128, "FPS %d (%f ms)", fps, timePerFrame);

		calculateFPS(fps, timePerFrame);
		fpsCount->setText(fpsUI);
#endif

		//4. Post Processing
		mainCamera.updateUI();
		mainCamera.drawUI();
		myWindow.update();

		if(frameRateLimit > 0)
			pauseDrawing(glfwGetTime() - startTime);

	};
#ifdef WEB_BUILD
	emscripten_set_main_loop_arg(startMain, &webMain, false, true);
#endif

	cout << "-----------------------------------" << endl;

	return 0;
}
