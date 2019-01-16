#ifndef CORE_ENGINE_H_
#define CORE_ENGINE_H_

#include <string>
#include "window.h"
#include "time.h"
#include "game.h"

class CoreEngine
{
public:
    CoreEngine(std::string title = TITLE, int width = WIDTH, int height = HEIGHT);

    void start();
    void stop();
    void loadMesh(const std::string& model_path);

    ~CoreEngine();

private:
    Window* m_mainWindow;
    int m_width, m_height;
    const std::string m_title;
    bool m_isRunning;
    Game* m_game;

    void run();
    void render();
};

#endif // CORE_ENGINE_H_
