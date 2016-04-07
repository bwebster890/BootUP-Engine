#ifndef UTILITY_HPP
#define UTILITY_HPP

const static std::string windowTitle = "BootUp Engine";

inline double get_real_time() 
{
    return SDL_GetPerformanceCounter() / double(SDL_GetPerformanceFrequency());
}

const static int FRAME_TIME_INFO_SAMPLE_COUNT = 4; // four should be enough
struct 
{
    double samples[FRAME_TIME_INFO_SAMPLE_COUNT];
} frame_time_info;

void update_frame_time_info()
{
    int copy_size = sizeof(double) * (FRAME_TIME_INFO_SAMPLE_COUNT - 1);
    memmove(frame_time_info.samples + 1, frame_time_info.samples, copy_size);
    frame_time_info.samples[0] = get_real_time();
}
inline double get_last_frametime() {
    return frame_time_info.samples[0] - frame_time_info.samples[1];
}
void indicate_frame_time_info_on_window_title(SDL_Window *window, const char *base_title) 
{
    double frametime = get_last_frametime();
    int size = snprintf(0, 0, "%s | fps=%lf frametime=%lf",
                        base_title, 1.0 / frametime, frametime);
    char *new_title = (char*)malloc(size);
    snprintf(new_title, size, "%s | fps=%lf frametime=%lf",
             base_title, 1.0 / frametime, frametime);
    SDL_SetWindowTitle(window, new_title);
    free(new_title);
}

bool initialize_apis(SDL_Window** window, SDL_GLContext* gl_context, int w, int h, int gl_major, int gl_minor)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        printf("Failed to initialize SDL: '%s'.\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    *window = SDL_CreateWindow(windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_OPENGL);
    if (!*window)
    {
        printf("Failed to create a window (Version: %d.%d): '%s'.\n", gl_major, gl_minor, SDL_GetError());
        return false;
    }

    *gl_context = SDL_GL_CreateContext(*window);
    if (!*gl_context)
    {
        printf("Failed to create an OpenGL context (Version: %d.%d): '%s'.\n", gl_major, gl_minor, SDL_GetError());
        return false;
    }

    glewExperimental = true; // allows glew to use experimental features
    auto glew_init_status = glewInit();
    if (glew_init_status != GLEW_OK)
    {
        printf("Failed to initialize GLEW: '%s'.\n", glewGetErrorString(glew_init_status));
        return false;
    }

    return true;
}
void shutdown_apis(SDL_Window *window, SDL_GLContext gl_context)
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif // UTILITY_HPP
