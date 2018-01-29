#ifndef CORE_HPP
#define CORE_HPP

#include "global.hpp"
#include "AWidget.hpp"

class Core {
private:
    GLFWwindow  *_window;
    int         _width;
    int         _height;
    int         _ups;
    int         _fps;

    AWidget     *_lastScene;
    AWidget     *_scene;
    bool        running;

public:
    Core(void);
    ~Core(void);

    inline void             setWindow(GLFWwindow *window) { _window = window; }
    inline GLFWwindow       *getWindow(void) { return (_window); }
    inline int              getUPS(void) { return (_ups); }
    inline int              getFPS(void) { return (_fps); }
    inline void             closeRequest(void) { running = false; }
    void                    loop(void);
    void                    viewport(int width, int height);
    void                    load(void);
    void                    unload(void);
    void                    loadScene(AWidget *scene);
    void                    keyPress(int key);
    void                    keyRelease(int key);
    void                    keyRepeat(int key);
};

#endif