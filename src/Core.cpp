#include "Core.hpp"
#include "Timer.hpp"

Core::Core(void) :
    _window(NULL),
    _width(1280),
    _height(720)
{
    _window = glfwCreateWindow(_width, _height, "Color Running", NULL, NULL);
}

Core::~Core(void)
{
    if (_window != NULL)
    {
        glfwDestroyWindow(_window);
        _window = NULL;
    }
}

void                    Core::loop(void)
{
    while (!glfwWindowShouldClose(_window))
    {
        Timer::Update();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}
void                    Core::viewport(int width, int height)
{
    glViewport(0, 0, width, height);
}