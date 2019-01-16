#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <SDL2/SDL.h>
#include "input.h"

class Window
{
public:
    //ctor
    Window(const std::string title, int width, int height);

    //class functions
    static void clear();
    static void initGraphics(float r, float g, float b, float a);
    inline bool isClosed() { return m_isClosed;	}
    //inline static float getAspect() { return (float)m_width / (float)m_height;  }
    void update();

    //dtor
    virtual ~Window();

    private:
    SDL_Window* m_window;
    SDL_GLContext m_context;
    bool m_isClosed;
    int m_width, m_height;
};

#endif // WINDOW_H_
