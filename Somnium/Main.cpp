#include <thread>
#include <iostream>
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"

//#include "Audio/AudioEngine.h"
#include "Utilities/FileUtilities.h"

using namespace std;
using namespace Somnium;
using namespace Graphics;
using namespace Maths;
//using namespace Audio;

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

    Shader shader("Graphics/Shaders/Basic/basic.vert", "Graphics/Shaders/Basic/basic.frag");

	if(shader.getID() == 0){
        int n;
        cin >> n;
        return 0;
	}

	shader.enable();
	shader.setMatrix4("projectionMatrix", mainCamera.getProjection());
	shader.setMatrix4("viewMatrix", mainCamera.getView());
	Matrix4 model, rotM, sca, tra;

	shader.setVector2("light_position", Vector2(0.0f, 0));
	shader.setVector4("colour", Vector4(1.f, 1.f, 1.f, 1.0f));

	Mesh* monkeyMesh = new Mesh(Utilities::loadOBJ("Graphics/Objects/Monkey.obj"));
	RenderableObject monkey = RenderableObject(monkeyMesh);

	const float MAX_Z = -10, MIN_Z = 0;
	float CURRENT_Z = MIN_Z,
	      Z_DIR = -1,
	      Z_MAG = 0.001f;

	while (!myWindow.isClosed())
	{
		myWindow.clear();

		double x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		if (myWindow.isKeyPressed(GLFW_KEY_LEFT) || myWindow.isKeyPressed(GLFW_KEY_A))
		{
			cout << "Pressed Left" << endl;
			mainCamera.move(Maths::Vector3(-0.01f, 0, 0));
		}
		else if (myWindow.isKeyPressed(GLFW_KEY_RIGHT) || myWindow.isKeyPressed(GLFW_KEY_D))
		{
			cout << "Pressed Right" << endl;
			mainCamera.move(Maths::Vector3(0.01f,0,0));
		}
		else if (myWindow.isKeyPressed(GLFW_KEY_UP) || myWindow.isKeyPressed(GLFW_KEY_W))
		{
			cout << "Pressed Up" << endl;
			if (myWindow.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || myWindow.isKeyPressed(GLFW_KEY_RIGHT_CONTROL))
			{
				cout << "Pressed CTRL" << endl;
				mainCamera.move(Maths::Vector3(0, 0.01f, 0));
			}
			else
				mainCamera.move(Maths::Vector3(0, 0, -0.01f));
		}
		else if (myWindow.isKeyPressed(GLFW_KEY_DOWN) || myWindow.isKeyPressed(GLFW_KEY_S))
		{
			cout << "Pressed Down" << endl;
			if (myWindow.isKeyPressed(GLFW_KEY_LEFT_CONTROL) || myWindow.isKeyPressed(GLFW_KEY_RIGHT_CONTROL)) 
			{
				cout << "Pressed CTRL" << endl;
				mainCamera.move(Maths::Vector3(0, -0.01f, 0));
			}
			else
				mainCamera.move(Maths::Vector3(0, 0, 0.01f));
		}

		//2. Update objects
		shader.setVector2("light_position", Vector2((float)(x * 16.0f / myWindow.getWidth()), (float)(9.0f - y * 9.0f / myWindow.getHeight())));

		CURRENT_Z += Z_DIR * Z_MAG;
		if (CURRENT_Z <= MAX_Z) Z_DIR = 1.0f;
		else if (CURRENT_Z >= MIN_Z) Z_DIR = -1.0f;

		cout << CURRENT_Z << endl;

		static float rot = 0;

		sca = Matrix4::scale(Vector3(.1f, .1f, .1f));
		tra = Matrix4::translation(Vector3(0, 0, CURRENT_Z));
		rotM = Matrix4::rotationX(rot+=0.01f) * Matrix4::rotationY(rot) * Matrix4::rotationZ(rot);
		model = sca * rotM * tra;
		shader.setMatrix4("viewMatrix", mainCamera.getView());
		shader.setMatrix4("modelMatrix", model);

		//3. Draw objects
		monkey.draw();
		//testMesh.draw();

		//4. Post Processing
		myWindow.update();

		calculateFPS();
	}

	cout << "-----------------------------------" << endl;

	return 0;
}
