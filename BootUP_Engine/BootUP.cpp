#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "State.hpp"
#include "RenderSystem.hpp"
#include "PhysicsSystem.hpp"
#include "Camera.hpp"
#include "ModelLoader.hpp"
#include "ShaderProgram.hpp"
#include "Utility.hpp"

#define FRAME_RATE 60

int main()
{
	//initialize all apis, quit program if any failed
    SDL_Window *window = 0;
    SDL_GLContext gl_context = 0;
    if(!initialize_apis(&window, &gl_context, 800, 600))
        return -1;

	bool is_running = true;

	State state;
	RenderSystem render;
	PhysicsSystem physics;
	ShaderProgram program;
	Camera camera;

	//set the camera to have a 2D perspective
	camera.set_projective(800, 600, 45.0, 0.1, 100.0);

	//load in the shaders so we can use them in the render system
	program.set_vertex("shaders/test.vert");
	program.set_fragment("shaders/test.frag");
	program.link();

	//pass camera and the shader program to the render system
	render.SetCamera(&camera);
	render.SetShaderProgram(&program);

	//link the render system to the render system in state
	state.SetSystem(&render);
	state.SetSystem(&physics);
	
	//test entity: player1
	LoadModel(&state, "player1", "models/cube.bm", "images/crate_texture.png");
	state.AddComponent("player1", new Orientation(glm::vec3(2.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	state.AddComponent("player1", new Velocity(0.01f, 0.01f, 0.0f));

	//test entity: player2
	state.CopyEntity("player1", "player2");
	state.ChangeComponent("player2", new Orientation(glm::vec3(-2.0f, 0.0f, -7.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.005f));
	state.RemoveComponent("player2", COMP_VELOCITY);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

    glClearColor(0.0, 0.0, 0.0, 1.0);

	while (is_running)
	{
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                is_running = false;
            }
        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		state.Update();

		SDL_GL_SwapWindow(window);
		SDL_Delay(1000 / FRAME_RATE);
	}

	shutdown_apis(window, gl_context);
}
