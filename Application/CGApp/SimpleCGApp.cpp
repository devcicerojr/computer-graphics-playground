#include "SimpleCGApp.hpp"

namespace jfj
{

void SimpleCGApp::init(void)
{
    createWindow();
    createObjects();
    createShaders();
    // GLuint uniform_model = 0, uniform_projection = 0, uniform_view = 0;

    initCamera();
}

void SimpleCGApp::exec(void)
{
    while (!(window_.shouldClose()))
    {
        controller_.pollEvents();
        theLoop();
    }
}

void SimpleCGApp::theLoop(void)
{
    buildCommands();
    window_.clearScreen();
    window_.showScene();
    window_.swapBuffers();
}

} // end of namespace jfj
