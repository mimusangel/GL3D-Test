#include "Core/global.hpp"
#include "Core/Core.hpp"
#include "Game/Renderer.hpp"
#include "Game/Loader.hpp"
#include "Game/SceneMain.hpp"

static void win_resize_callback(GLFWwindow *window, int width, int height)
{
	Core	*core;

	core = (Core *)glfwGetWindowUserPointer(window);
	if (!core)
		return ;
    core->viewport(width, height);
}

int main(void)
{
    if (!glfwInit())
        std::cout << "Failed to initialize GLFW\n";
    else
    {
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DEPTH_BITS, 32);
        Core core;
        if (core.getWindow() == NULL)
            std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 4.1 compatible.\n";
        else
        {
            glfwMakeContextCurrent(core.getWindow());
            glfwSetWindowUserPointer(core.getWindow(), &core);
            //glfwSetKeyCallback(game.window, key_callback);
            glfwSetFramebufferSizeCallback(core.getWindow(), win_resize_callback);
            glfwSwapInterval(0);
            glewExperimental=true;
            if (glewInit() != GLEW_OK)
                std::cout << "Failed to initialize GLEW\n";
            else
            {
                Renderer renderer = Renderer::GetInstance();
                Loader loader = Loader::GetInstance();
                core.load();
                core.loadScene(new SceneMain());
                core.loop();
                core.unload();
                loader.unload();
                renderer.unload();
            }
        }
        glfwTerminate();
    }
    return (0);
}