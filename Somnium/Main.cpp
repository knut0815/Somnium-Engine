#include <thread>
#include <iostream>
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/BatchRenderer.h"
#include "Graphics/SerialRenderer.h"
#include "Graphics/RenderableObject.h"
#include "Graphics/Camera.h"

#include "Audio/AudioEngine.h"
#include "Utilities/FileUtilities.h"

using namespace std;
using namespace Somnium;
using namespace Graphics;
using namespace Maths;
using namespace Audio;

void calculateFPS()
{
	static double lastTime = glfwGetTime();
	static int nbFrames = 0;

	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last printf() was more than 1 sec ago
										 // printf and reset timer
		printf("FPS %d, %f ms/frame\n", nbFrames, 1000.0 / double(nbFrames));

		nbFrames = 0;
		lastTime += 1.0;
	}
}

int main(int argc, char** argv) {
	cout << "SOMNIUM by LUMACAL Software Group - Built " << __TIMESTAMP__ << endl << endl;

	Window myWindow("Somnium Engine", 1920, 1080);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    //Sound demo
    //AudioEngine au;
    //thread at{&AudioEngine::playSound, this, "Synth1.wav"};
    //at.join();
  //  AudioEngine au;
   // au.playSound("Synth1.wav");

	cout << "---------RUNNING GAME LOOP---------" << endl;

	//Camera mainCamera = Camera(Matrix4::orthographic(-myWindow.getAspectRatio() / 2.0f, myWindow.getAspectRatio() / 2.0f, -0.5f, 0.5f, 1.0f, 100.0f));
	Camera mainCamera = Camera(Matrix4::perspective(30, (float)myWindow.getWidth() / myWindow.getHeight(), 0.1f, 100.0f));

	Matrix4 view = Matrix4::identity();

	//Renderer renderer = new Renderer();

    Shader* shader = new Shader("Graphics/Shaders/Basic/basic.vert", "Graphics/Shaders/Basic/basic.frag");
	Mesh monkeyMesh = Mesh(Utilities::loadOBJ("Graphics/Objects/Monkey.obj", *shader));
	monkeyMesh.translate(0,0,-5);

	std::vector<RenderableObject*> objects;

	for(int i = 0; i < 1000; i++)
		objects.push_back(new RenderableObject(new Mesh(monkeyMesh)));

	SerialRenderer* renderer = new SerialRenderer(myWindow, mainCamera);

	for (RenderableObject* object : objects)
	{
		object->getMeshes().front()->scale(0.1f, 0.1f, 0.1f);
		object->getMeshes().front()->translate((float)rand()/RAND_MAX * 10.0f, (float)rand() / RAND_MAX * 10.0f, (float)rand() / RAND_MAX * 10.0f);
	}

	while (!myWindow.isClosed())
	{
		myWindow.clear();

		double x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		//2. Update objects
		//shader.setVector2("light_position", Vector2((float)(x * 16.0f / myWindow.getWidth()), (float)(9.0f - y * 9.0f / myWindow.getHeight())));

		static float monkeyZPos = 0;
		static float offset = -0.001f;

		if (monkeyZPos >= 0)  offset = -0.001f;
		else if (monkeyZPos <= -10) offset = 0.001f;

		monkeyZPos += offset;

		for (RenderableObject* object : objects)
		{
			object->getMeshes().front()->translate(0, 0, offset);
			object->getMeshes().front()->setOrientation(0.01f, 0.01f, 0.01f); //TODO: Setup a glPop/glPushMatrix() functionality system
			renderer->submitToQueue(object);
		}

		renderer->updateCamera();

		//3. Draw objects
		renderer->flushQueue();

		//4. Post Processing
		myWindow.update();

		calculateFPS();
	}

	cout << "-----------------------------------" << endl;

	return 0;
}
