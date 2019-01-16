#include "coreEngine.h"
#include <iostream>
#include <thread>

CoreEngine::CoreEngine(std::string title, int width, int height) : m_title(title), m_width(width), m_height(height)
{
    m_mainWindow = new Window(title, width, height);
    Window::initGraphics(0.0f, 0.0f, 0.0f, 0.0f);
    m_game = new Game();

    m_isRunning = true;
}


CoreEngine::~CoreEngine()
{
    delete m_mainWindow;
    delete m_game;
}



void CoreEngine::start() {
    std::cout << "Core engine started." << std::endl;
    if (!m_isRunning) {
        std::cout << "Core engine closing." << std::endl;
        return;
    }

    Time::reset();
    run();
}

void CoreEngine::render() {
    Window::clear();
    m_game->render();
    m_mainWindow->update();
}

//game loop
void CoreEngine::run() {
    m_isRunning = true;
    std::cout << "Engine starting...";

    int frames = 0;
    long frameCounter = 0;

    double frameTime = 1.0 / FRAME_CAP;

    //lastTime before running the game loop
    long long lastTime = Time::elapsed();
    double unprocessedTime = 0;

    while (m_isRunning) {
        bool render = false;
        long long startTime = Time::elapsed();
        long long passedTime = startTime - lastTime;
        lastTime = startTime;

        unprocessedTime += (double)passedTime/SECOND; //store the time in seconds
        frameCounter += passedTime; //store the time in nanoseconds

        //update the time when the loop has run for frame time seconds
        while (unprocessedTime > frameTime) {
            render = true;
            unprocessedTime -= frameTime;

            if (m_mainWindow->isClosed())
                stop();

            Time::setDelta(frameTime);

            //update the game here
            m_game->input(); //process the inputs
            m_game->update(); //update game values

            //display the frame count every second
            if (frameCounter >= SECOND) {
                std::cout << frames << std::endl;
                frames = 0;
                frameCounter = 0;
            }
        }

        if (render) {
            this->render();
            frames++;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //delay the loop so that calculations are not made too often
        }
    }

}

void CoreEngine::stop() {
    m_isRunning = false;
}

void CoreEngine::loadMesh(const std::string& model_path) {
    m_game->loadMesh(model_path);
}

