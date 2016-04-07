#include <GL/glew.h>
#include <SDL2/SDL.h>
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

const static std::string window_title = "BootUp Engine";

// Frame Limit Variables
double currentFrameTime = 0.0;
double lastFrameTime = 0.0;
double maxFramerate = 60.0;

bool initialize_apis(SDL_Window** window, SDL_GLContext* gl_context, int w, int h) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("Failed to initialize SDL: '%s'.\n", SDL_GetError());
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    *window = SDL_CreateWindow(window_title.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               w, h,
                               SDL_WINDOW_OPENGL);
    if(!*window) {
        printf("Failed to create a window: '%s'.\n", SDL_GetError());
        return false;
    }
    
    *gl_context = SDL_GL_CreateContext(*window);
    if(!*gl_context) {
        printf("Failed to create an OpenGL context: '%s'.\n", SDL_GetError());
        return false;
    }
    
    glewExperimental = true; // allows glew to use experimental features
    auto glew_init_status = glewInit();
    if(glew_init_status != GLEW_OK) {
        printf("Failed to initialize GLEW: '%s'.\n", glewGetErrorString(glew_init_status));
        return false;
    }
    
    return true;
}
void shutdown_apis(SDL_Window *window, SDL_GLContext gl_context) {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main()
{
	// initialize all apis, but quit program if any failed
    SDL_Window *window = 0;
    SDL_GLContext gl_context = 0;
    if(!initialize_apis(&window, &gl_context, 800, 600))
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
	state->AddComponent("player1", new Velocity());

	//test entity: player2
	state->CopyEntity("player1", "player2");
	state->AddComponent("player2", new Position(-2.0, 0.0, -7.0));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

	int counter = 0;

	bool is_running = true;
	while (is_running)
	{
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                is_running = false;
            }
        }
        
		currentFrameTime = get_real_time();
		if (currentFrameTime - lastFrameTime >= 1.0 / maxFramerate)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			state->Update();
			SDL_GL_SwapWindow(window);
			++counter;
			lastFrameTime = currentFrameTime;
            update_frame_time_info();
            indicate_frame_time_info_on_window_title(window, "bootupengine"); // crashes if window_title.c_str() is used. temporary.
		}
	}

	delete state;
	delete render;
	delete program;
	delete camera;

	shutdown_apis(window, gl_context);
}
