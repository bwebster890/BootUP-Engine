#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "State.hpp"
#include "System.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"

int main()
{
	GLFWwindow* window;

	glfwInit();

	window = glfwCreateWindow(800, 600, "BootUp", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	Camera camera;
	camera.set_ortho(800, 600, 0.0, -100.0);

	ShaderProgram program;
	program.set_vertex("shaders/test.vert");
	program.set_fragment("shaders/test.frag");
	program.link();

	RenderSystem render;
	render.SetCamera(&camera);
	render.SetShaderProgram(&program);

	State state;
	state.SetSystem(&render);

	state.AddComponent("player", new Position(200.0, 250.0, 0.0));
	state.AddComponent("player", new Rect(150.0, 100.0));
	state.AddComponent("player", new Texture("images/test.png"));

	state.AddComponent("player2", new Position(500.0, 250.0, 0.0));
	state.AddComponent("player2", new Rect(100.0, 100.0));
	state.AddComponent("player2", new Texture("images/test2.png"));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);

		state.Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}