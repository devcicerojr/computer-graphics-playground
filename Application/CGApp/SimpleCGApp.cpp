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

}

} // end of namespace jfj
