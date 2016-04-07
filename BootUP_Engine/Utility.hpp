#ifndef UTILITY_HPP
#define UTILITY_HPP

double get_real_time() {
    return SDL_GetPerformanceCounter() / double(SDL_GetPerformanceFrequency());
}
const int FRAME_TIME_INFO_SAMPLE_COUNT = 4; // four should be enough
struct {
    double samples[FRAME_TIME_INFO_SAMPLE_COUNT];
} frame_time_info;
void update_frame_time_info() {
    int copy_size = sizeof(double) * FRAME_TIME_INFO_SAMPLE_COUNT - 1;
    memmove(frame_time_info.samples + 1, frame_time_info.samples, copy_size);
    frame_time_info.samples[0] = get_real_time();
}
double get_average_frametime() {
    double frametime = 0.0;
    for(int i = 1; i < FRAME_TIME_INFO_SAMPLE_COUNT; ++i) {
        frametime += frame_time_info.samples[i - 1] - frame_time_info.samples[i];
    }
    return frametime / FRAME_TIME_INFO_SAMPLE_COUNT;
}
void indicate_frame_time_info_on_window_title(SDL_Window *window, const char *base_title) {
    double average_frametime = get_average_frametime();
    int size = snprintf(0, 0, "%s | fps=%lf frametime=%lf",
                        base_title, 1.0 / average_frametime, average_frametime);
    char *new_title = (char*)malloc(size);
    snprintf(new_title, size, "%s | fps=%lf frametime=%lf",
             base_title, 1.0 / average_frametime, average_frametime);
    SDL_SetWindowTitle(window, new_title);
    free(new_title);
}




//class Framerate
//{
	//double framerate;
    //double t0Value = get_real_time();
    //int    fpsFrameCount = 0;
    //double fps = 0.0;

	//Framerate() :
        //framerate(0.0)
	//{
	//}
	//virtual ~Framerate() {}

	//void calculateFPS(SDL_Window const* window, double time_interval, std::string window_title)
	//{
		//// Static values which only get initialised the first time the function runs
		

                                                //// Get the current time in seconds since the program started (non-static, so executed every time)
		//double currentTime = get_real_time();

		//// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
		//// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
		//if (time_interval < 0.1)
		//{
			//time_interval = 0.1;
		//}
		//if (time_interval > 10.0)
		//{
			//time_interval = 10.0;
		//}

		//// Calculate and display the FPS every specified time interval
		//if ((currentTime - t0Value) > time_interval)
		//{
			//// Calculate the FPS as the number of frames divided by the interval in seconds
			//fps = (double)fpsFrameCount / (currentTime - t0Value);

			//// If the user specified a window title to append the FPS value to...
			//if (window_title != "NONE")
			//{
				//// Convert the fps value into a string using an output stringstream
				//std::ostringstream stream;
				//stream << fps;
				//std::string fpsString = stream.str();

				//// Append the FPS value to the window title details
				//window_title += " | FPS: " + fpsString;

				//// Update the window title
				//SDL_SetWindowTitle(window, window_title.c_str());
			//}
			//else // If the user didn't specify a window to append the FPS to then output the FPS to the console
			//{
				//std::cout << "FPS: " << fps << std::endl;
			//}

			//// Reset the FPS frame counter and set the initial time to be now
			//fpsFrameCount = 0;
			//t0Value = get_real_time();
		//}
		//else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
		//{
			//fpsFrameCount++;
		//}

		//// Set Current FPS for display
		//this->framerate = fps;
	//}
//};

#endif // UTILITY_HPP
