#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "State.hpp"
#include "RenderSystem.hpp"
#include "ModelLoader.hpp"
#include "PhysicsSystem.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "Utility.hpp"

int main(int argc, char *argv[])
{
    // initialize all apis, but quit program if any failed
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context;

    // Try Version 4.1 else fall back to 3.0
    if (!initialize_apis(&window, &gl_context, 800, 600, 4, 1))
    {
        if (!initialize_apis(&window, &gl_context, 800, 600, 3, 0))
        {
            return -1;
        }
    }

    bool is_running = true;
	const static double minimal_frame_time = 1.0 / 60.0;

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
    state.AddComponent("player1", new Orientation(glm::vec3(2.0, 0.0, -10.0), glm::vec3(0.0, 1.0, 0.0), 0.01f));
    state.AddComponent("player1", new Velocity(0.01, 0.01, 0.0));

    //test entity: player2
    state.CopyEntity("player1", "player2");
    state.ChangeComponent("player2", new Orientation(glm::vec3(-2.0, 0.0, -7.0), glm::vec3(1.0, 1.0, 0.0), 0.005f));
	state.RemoveComponent("player2", COMP_VELOCITY);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    while (is_running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT ||
               (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
            {
                is_running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        state.Update();
		render.Draw();
        
        SDL_GL_SwapWindow(window);
        
        update_frame_time_info();
        double frame_time = get_last_frametime();

        if(frame_time < minimal_frame_time) 
		{
            SDL_Delay(1000.0 * (minimal_frame_time - frame_time));
        }
    }

    shutdown_apis(window, gl_context);
}
