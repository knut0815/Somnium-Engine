#include <iostream>
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Utilities/FileUtilities.h"

using namespace std;
using namespace Somnium;
using namespace Graphics;
using namespace Maths;

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

	cout << "---------RUNNING GAME LOOP---------" << endl;

	Matrix4 projection = Matrix4::orthographic(0, 16.0f, 0, 9.0f, 0.1f, 100.0f);

	Matrix4 view = Matrix4::identity();

	Shader shader("Graphics/Shaders/basic.vert", "Graphics/Shaders/basic.frag");
	if(shader.getID() == 0){
        int n;
        cin >> n;
        return 0;
	}

	shader.enable();
	shader.setMatrix4("projectionMatrix", projection);
	Matrix4 model;

	shader.setVector2("light_position", Vector2(0.0f, 0));
	shader.setVector4("colour", Vector4(1.f, 1.f, 1.f, 1.0f));

	Mesh testMesh = Utilities::loadOBJ("Graphics/Objects/Monkey.obj");

	if (!testMesh.structureExists())
		cout << "Object has no structure!" << endl;

	while (!myWindow.isClosed())
	{
		myWindow.clear();

		double x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		//2. Update objects
		shader.setVector2("light_position", Vector2((float)(x * 16.0f / myWindow.getWidth()), (float)(9.0f - y * 9.0f / myWindow.getHeight())));

		static float rot = 0;

		model = Matrix4::scale(Vector3(3, 3, 3)) * Matrix4::rotation(rot += 0.01f, Vector3(0, 1, 0)) * Matrix4::translation(Vector3(8, 4.5f, -5));
		shader.setMatrix4("modelMatrix", model);

		//3. Draw objects
		testMesh.draw(shader);

		//4. Post Processing
		myWindow.update();

		calculateFPS();
	}

	cout << "-----------------------------------" << endl;

	return 0;
}
