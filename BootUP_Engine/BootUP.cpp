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
#include "Utility.hpp"

std::string windowTitle = "BootUp Engine";

// Frame Limit Variables
double currentFrameTime = 0.0;
double lastFrameTime = 0.0;
double maxFramerate = 60.0;

int main()
{
	Framerate fps_viewer;
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
	state->AddComponent("player1", new Orientation(glm::vec3(2.0, 0.0, -10.0), glm::vec3(0.0, 1.0, 0.0), 1.0f));
	state->AddComponent("player1", new Velocity(0.01, 0.01, 0.0));

	//test entity: player2
	state->CopyEntity("player1", "player2");
	state->AddComponent("player2", new Orientation(glm::vec3(-2.0, 0.0, -7.0), glm::vec3(0.0, 0.0, 1.0), 1.0f));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	int counter = 0;

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		currentFrameTime = glfwGetTime();

		if (currentFrameTime - lastFrameTime >= 1.0 / maxFramerate)
		{
			
			lastFrameTime = currentFrameTime;
			fps_viewer.calculateFPS(window, 1.0, windowTitle);

			//clear the depth and color buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0, 0.0, 0.0, 1.0);

			//update all active systems
			state->Update();

			//swap buffers and poll events
			glfwSwapBuffers(window);
			glfwPollEvents();

			counter++;
		}
	}

	delete state;
	delete render;
	delete physics;
	delete program;
	delete camera;

	glfwTerminate();
}