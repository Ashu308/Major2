#include "window.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cassert>

//ctor
Window::Window(const std::string title, int width, int height) : m_width(width), m_height(height) {
    assert(height > 0 && width > 0);

    SDL_Init(SDL_INIT_EVERYTHING);


    //set the space for colour buffers
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLenum status = glewInit();

    if (status != GLEW_OK) {
        std::cerr << "Glew failed to initialize" << std::endl;
    }

    m_isClosed = false;
}

//dtor
Window::~Window()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::clear() {
    //clear the screen with the selected colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::initGraphics(float r, float g, float b, float a) {
    //set the clearing colour
    glClearColor(r, g, b, a);

    //enable back face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //gpu will know which vertex is at the top (z value)
    glEnable(GL_DEPTH_TEST);

    //for gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);
}

//update the buffer and update m_isClosed when applicable
void Window::update() {
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT){
            m_isClosed = true;
        }
        //else send the input to the input class
        else
        {
            Input::update(&e);
        }
    }
    else
        Input::update(NULL);
}
