#ifndef CORE_HPP
#define CORE_HPP

#include "global.hpp"

class Core {
private:
    GLFWwindow  *_window;
    int         _width;
    int         _height;

public:
    Core(void);
    ~Core(void);

    inline void             setWindow(GLFWwindow *window) { _window = window; }
    inline GLFWwindow       *getWindow(void) { return (_window); }
    
    void                    loop(void);
    void                    viewport(int width, int height);
};

#endif