#pragma once

#include <cstdint>

#include "TextureHandler.h"
#include "InputHandler.h"
#include "Menu.h"
#include "MenuHandler.h"
#include "MenuTools/MenuTools.h"
#include "Window.h"

/**
 * Version 1.0.3
 * 
 * LSDLE is a lightweight engine designed for rendering text and PNG images, as well as
 * handling basic user input. It includes various tools for creating simple menus with
 * modular variables and lists. For a detailed explanation, please refer to
 * documentation/Setup_and_Uses.txt.
 */
class LSDLE
{

public:

    // Default constructor is deleted to ensure proper path specification
    LSDLE() = delete;
    LSDLE(std::string _LSDLE_project_path);
    ~LSDLE();

    /**
     * @brief Starts the Engine simulation.
     * 
     */
    void start();

    static int get_screen_width();
    static int get_screen_height();

    static InputHandler* get_input_handler();
    static TextureHandler* get_texture_handler(); 

protected:

    /**
     * @brief Called once per frame. Components that need updating each frame
     * will be updated here.
     */
    virtual void update();

    /**
     * @brief Called once per frame. Components that need rendered each frame
     * will be rendered here.
     */
    virtual void render();

    /**
     * @brief Terminates the engine. 
     * 
     * @attention Note that this function simply flags the engine to quit on 
    * the next frame completion. Any calculation between this function
     * call and the end of the frame will still happen.
     * 
     */
    virtual void quit();

    static InputHandler* input_handler;
    static TextureHandler* texture_handler;

    MenuHandler* menu_handler;

private:

    /**
     * @brief This is the "main" loop of the engine where all its
     * processes are contained. While the engine is active (while the 
     * is_simulating bool is true) this loop will run. 
     */
    void simulation_loop();

    /**
     * @brief Handles SDL_Events such as the application exit button being
     * pressed, and the registering of pressed and released keys on the 
     * user's keyboard.
     */
    void handle_events();

    /**
     * @brief Flags the SDL_Renderer to clear its content, which wipes the 
     * screen.
     */
    void clear_screen();

    /**
     * @brief Flags the SDL_Renderer to present its buffered data, placing it 
     * on the screen.
     * 
     */
    void present_renderer();

    /**
     * @brief If the Engine is running the simulation loop.
     * 
     * @attention Once this bool is set to false after the Engine starts, 
     * simulation will terminate.
     */
    bool is_simulating = false; 

    // Path to the initialization data json file
    const char* init_data_path = "init_data.json";

    // Number of miliseconds that elapsed during this frame
    uint8_t elapsed_miliseconds;

    // Target number of miliseconds per frame to achieve 60 FPS
    const uint8_t TARG_MILISECONDS_PER_FRAME = 16;

    static int screen_width; // Width of the window
    static int screen_height; // Height of the window

    /**
     * @brief Path to the LSDLE directory on the user's computer. This path 
     * is set through the constructor
     */
    std::string LSDLE_project_path;

    // Start timestamp of the beginning of this frame;
    uint64_t frame_start;

    // Instance of the SDL_Event container. 
    SDL_Event event;

    SDL_Window* window;
    SDL_Renderer* renderer;
};
