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

	Matrix4 ortho = Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("Graphics/Shaders/basic.vert", "Graphics/Shaders/basic.frag");
	shader.enable();
	shader.setUniform("pr_matrix", ortho);
	shader.setUniform("ml_matrix", Matrix4::translation(Vector3(4, 3, 0)));

	shader.setUniform("light_position", Vector2(0.0f, 0));
	shader.setUniform("colour", Vector4(0.6f, 0.3f, 0.8f, 1.0f));

	Mesh testMesh = Utilities::loadOBJ("Graphics/Objects/Cube.obj");

	if (!testMesh.structureExists())
		cout << "Object has no structure!" << endl;

	while (!myWindow.isClosed()) 
	{ 
		myWindow.clear();

		double x, y;

		//1. Process I/O
		myWindow.getMousePosition(x, y);

		//2. Update objects
		shader.setUniform("light_position", Vector2((float)(x * 16.0f / myWindow.getWidth()), (float)(9.0f - y * 9.0f / myWindow.getHeight())));

		//3. Draw objects
		testMesh.draw(shader);

		//4. Post Processing
		myWindow.update();
		
		calculateFPS();
	}
	
	cout << "-----------------------------------" << endl;

	return 0;
}