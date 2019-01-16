#ifndef INPUT_H_
#define INPUT_H_

#include <SDL2/SDL.h> //required for getting the keyboard inputs
#include <vector>
#include <glm/glm.hpp>

class Input
{
public:
    inline Input() {};

    static void update(SDL_Event* e); //update the list of keys
    static bool getKey(SDL_Keycode key); //check whether a specific key is pressed
    static bool getKeyDown(SDL_Keycode key);
    static bool getKeyUp(SDL_Keycode key);
    static bool getMouse(Uint8 button); //check whether a specific key is pressed
    static bool getMouseDown(Uint8 button);
    static bool getMouseUp(Uint8 button);
    static glm::vec2 getMousePos();

    virtual ~Input() {};

private:
    static std::vector<SDL_Keycode> currentKeys; //store the keys pressed down
    static std::vector<SDL_Keycode> downKeys; //store the keys pressed in the current frame
    static std::vector<SDL_Keycode> upKeys; //store the keys released in the current frame
    static std::vector<Uint8> currentMouse; //store the mouse buttons pressed down
    static std::vector<Uint8> downMouse; //store the mouse buttons in the current frame
    static std::vector<Uint8> upMouse; //store the mouse buttons released in the current frame
};

#endif // INPUT_H_
