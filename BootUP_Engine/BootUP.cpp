#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>

#include "State.hpp"
#include "RenderSystem.hpp"
#include "ModelLoader.hpp"
#include "PhysicsSystem.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"

std::string windowTitle = "BootUp Engine";

// Frame Limit Variables
double currentFrameTime = 0.0;
double lastFrameTime = 0.0;
double maxFramerate = 60.0;

double calcFPS(GLFWwindow* window, double theTimeInterval, std::string theWindowTitle)
{
	// Static values which only get initialised the first time the function runs
	static double t0Value = glfwGetTime();	// Set the initial time to now
	static int    fpsFrameCount = 0;		// Set the initial FPS frame count to 0
	static double fps = 0.0;				// Set the initial FPS value to 0.0

	// Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// If the user specified a window title to append the FPS value to...
		if (theWindowTitle != "NONE")
		{
			// Convert the fps value into a string using an output stringstream
			std::ostringstream stream;
			stream << fps;
			std::string fpsString = stream.str();

			// Append the FPS value to the window title details
			theWindowTitle += " | FPS: " + fpsString;

			// Convert the new window title to a c_str and set it
			const char* pszConstString = theWindowTitle.c_str();
			glfwSetWindowTitle(window, pszConstString);
		}
		else // If the user didn't specify a window to append the FPS to then output the FPS to the console
		{
			std::cout << "FPS: " << fps << std::endl;
		}

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}

int main()
{
	GLFWwindow* window;

	//check if glfw failed to initialize
	if (!glfwInit())
		return -1;

	//create window and make a GL context for it
	window = glfwCreateWindow(800, 600, windowTitle.c_str(), 0, 0);
	glfwMakeContextCurrent(window);

	//check if glew failed to initialize
	if (glewInit() != GLEW_OK)
		return -1;

	State* state = new State;
	RenderSystem* render = new RenderSystem;
	PhysicsSystem* physics = new PhysicsSystem;
	ShaderProgram* program = new ShaderProgram;
	Camera* camera = new Camera;

	//set the camera to have a 2D perspective
	camera->set_projective(800, 600, 45.0, 0.1, 100.0);

	//load in the shaders so we can use them in the render system
	program->set_vertex("shaders/test.vert");
	program->set_fragment("shaders/test.frag");
	program->link();

	//pass camera and the shader program to the render system
	render->SetCamera(camera);
	render->SetShaderProgram(program);

	//link the render system to the render system in state
	state->SetSystem(render);
	state->SetSystem(physics);
	
	//test entity: player1
	LoadModel(state, "player1", "models/cube.bm");
	state->AddComponent("player1", new Position(2.0, 0.0, -10.0));

	//test entity: player2
	state->CopyEntity("player1", "player2");
	state->AddComponent("player2", new Position(-2.0, 0.0, -7.0));

	glEnable(GL_CULL_FACE);

	int counter = 0;

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		currentFrameTime = glfwGetTime();

		if (currentFrameTime - lastFrameTime >= 1.0 / maxFramerate)
		{
			
			lastFrameTime = currentFrameTime;
			calcFPS(window, 1.0, windowTitle);

			//clear the depth and color buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0, 0.0, 0.0, 1.0);

			//update all active systems
			state->Update();

			//swap buffers and poll events
			glfwSwapBuffers(window);
			glfwPollEvents();

			counter++;
			if(counter >= 100)
			{
				double x_rand = ((double)rand() / (RAND_MAX)) + 1;
				double y_rand = ((double)rand() / (RAND_MAX)) + 1;
				bool x_negitive = rand() % 2 == 1;
				bool y_negitive = rand() % 2 == 1;

				if (x_negitive)
					x_rand *= -1.0;
				if (y_negitive)
					y_rand *= -1.0;

				state->ChangeComponent("player2", new Velocity(x_rand, y_rand, 0.0));
				std::cout << "New X: " << x_rand << " New Y: " << y_rand << std::endl;
				counter = 0;
			}
		}
	}

	delete state;
	delete render;
	delete program;
	delete camera;

	glfwTerminate();
}