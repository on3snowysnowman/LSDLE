#include <fstream>

#include "LSDLE.h"
#include "Json.h"
#include "JsonLoader.h"
#include "Debug.h"

// Static Members

int LSDLE::screen_width = 0;
int LSDLE::screen_height = 0;

uint64_t LSDLE::total_elapsed_frames;

InputHandler* LSDLE::input_handler = nullptr;
TextureHandler* LSDLE::texture_handler = nullptr;


// Constructors / Deconstructor 

LSDLE::LSDLE(std::string _LSDLE_project_path)
{
    // Clear the Output Log
    Debug::clear_debug_output_file();

    // Output the LSDLE file directory to an external file so other components
    // that need the LSDLE's directory can access it through this file

    std::fstream file_stream("path.txt", std::ios::out);

    if(file_stream.is_open())
    {
        file_stream << _LSDLE_project_path;
        file_stream.close();
    }

    LSDLE_project_path = _LSDLE_project_path;

    // Get init data for the Engine. The path to the init file is the path to
    // the LSDLE directory concatinated with the init data path.
    Json init_data = JsonLoader::get((LSDLE_project_path + '/' + init_data_path).c_str());

    // If SDL Failed to initialize
    if(SDL_Init(SDL_INIT_EVENTS) != 0 || 
        SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Debug::log("SDL failed to initialize", Debug::ERR);
        exit(1);
    }

    SDL_ShowCursor(SDL_DISABLE);

    if(init_data["fullscreen"])
    {
        Debug::log("Fullscreen : true");

        // Create a fullscreen SDL Window
        window = SDL_CreateWindow(
            std::string(init_data["application_window_title"]).c_str(),
            0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

        // Get the created window size, and update the screen width and screen 
        // height
        SDL_GetWindowSize(window, &screen_width, &screen_height);
    }

    else
    {
        Debug::log("Fullscreen : false");

        // Get the width and height from the init file
        screen_width = init_data["width"];
        screen_height = init_data["height"];

        if(screen_width < 500 || screen_height < 500)
        {
            // Don't allow the user to create a window with size dimensions
            // less than 500, the screen would be too small for most programs
            // to efficiently run

            std::string message = "Screen dimensions cannot be less than a "
                "value of 500. Change these dimensions under the directory: "
                + std::string(init_data_path) + " -> width and height";

            Debug::log(message, Debug::ERR);
            exit(1);
        }

        // Create a window with the init data dimensions
        window = SDL_CreateWindow(std::string(
            init_data["application_window_title"]).c_str(), 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, 
            screen_height, 0);
    }

    // Create the SDL_Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    input_handler = new InputHandler;
    texture_handler = new TextureHandler(renderer, LSDLE_project_path + "/colors.json");

    // Set the background color of the renderer
    SDL_SetRenderDrawColor(renderer, 
        init_data["background_color"].at(0),
        init_data["background_color"].at(1),
        init_data["background_color"].at(2), 
        255);
}

LSDLE::~LSDLE()
{   
    SDL_Quit();
}


// Public

void LSDLE::start()
{
    is_simulating = true;
    simulation_loop();
}

int LSDLE::get_screen_width() { return screen_width; }

int LSDLE::get_screen_height() { return screen_height; }

uint64_t LSDLE::get_total_elapsed_frames() { return total_elapsed_frames; }

InputHandler* LSDLE::get_input_handler() { return input_handler; }

TextureHandler* LSDLE::get_texture_handler() { return texture_handler; }

// Protected

void LSDLE::update() {}

void LSDLE::render() {}

void LSDLE::quit()
{
    is_simulating = false;
}

// Private

void LSDLE::simulation_loop()
{
    /**
     * Every function of the engine occurs here, such as the updating of 
     * components that need updating, along with clearing the screen before 
     * the virtual render() method and presenting teh SDL_Renderer after the 
     * render() method has been called. The engine also calculates the amount
     * of miliseconds that need to be delayed between each frame to obtain the
     * target fps.
     */

    while(is_simulating)
    {
        ++total_elapsed_frames;

        // Track when this frame started
        frame_start = SDL_GetTicks64();

        input_handler->update();
        handle_events();
        MenuHandler::update();
        update();
        clear_screen();
        WindowManager::update();
        render();
        present_renderer();

        // Calculate how long this frame took in miliseconds
        elapsed_miliseconds = SDL_GetTicks64() - frame_start;

        // If this frame was quicker than the target
        if(elapsed_miliseconds < TARG_MILISECONDS_PER_FRAME)
        {
            /**
             * Delay for the difference between the elapsed miliseconds and 
             * the target
             */
            SDL_Delay(TARG_MILISECONDS_PER_FRAME - elapsed_miliseconds);
        }
    }
}

void LSDLE::handle_events()
{
    // While there are still events in the SDL event queue
    while(SDL_PollEvent(&event))
    {
        // The application window's close button has been pressed by the user's
        // mouse
        if(event.type == SDL_QUIT)
        {
            quit();
        }

        // A key has been pressed on the user's keyboard
        else if(event.type == SDL_KEYDOWN)
        {
            input_handler->flag_key_pressed(event.key.keysym.sym);
        }

        // A key has been pressed on the user's keyboard
        else if(event.type == SDL_KEYUP)
        {
            input_handler->flag_key_released(event.key.keysym.sym);
        }
    }
}

void LSDLE::clear_screen()
{
    SDL_RenderClear(renderer);
}

void LSDLE::present_renderer()
{
    SDL_RenderPresent(renderer);
}