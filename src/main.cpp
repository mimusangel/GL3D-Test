#include "Core/global.hpp"
#include "Core/Core.hpp"
#include "Game/Renderer.hpp"
#include "Game/SceneMain.hpp"

#include "Core/Math/Mat.hpp"
#include "Core/Math/Vec3.hpp"

static void win_resize_callback(GLFWwindow *window, int width, int height)
{
	Core	*core;

	core = (Core *)glfwGetWindowUserPointer(window);
	if (!core)
		return ;
    core->viewport(width, height);
}

static void win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Core	*core;

	core = (Core *)glfwGetWindowUserPointer(window);
	if (!core)
		return ;
    if (action == GLFW_PRESS)
        core->keyPress(key);
    else if (action == GLFW_REPEAT)
        core->keyRepeat(key);
    else if (action == GLFW_RELEASE)
        core->keyRelease(key);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Core	*core;

	core = (Core *)glfwGetWindowUserPointer(window);
	if (!core)
		return ;
    core->mouseMove((float)xpos, (float)ypos);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Core	*core;

	core = (Core *)glfwGetWindowUserPointer(window);
	if (!core)
		return ;
    if (action == GLFW_PRESS)
        core->mouseButtonPress(button);
    else if (action == GLFW_RELEASE)
        core->mouseButtonRelease(button);
}

int main(void)
{
    // Mat4 mat = Mat4::RotateY(M_TORADIANS(45.0));
    // Vec3f vec(0, 0, 1);
    // Vec3f rVec = mat.transform(vec);
    // std::cout << rVec << std::endl;
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
            glfwSetFramebufferSizeCallback(core.getWindow(), win_resize_callback);
		    glfwSetCursorPosCallback(core.getWindow(), cursor_position_callback);
		    glfwSetMouseButtonCallback(core.getWindow(), mouse_button_callback);
            glfwSetKeyCallback(core.getWindow(), win_key_callback);
            glfwSwapInterval(0);
            glewExperimental=true;
            if (glewInit() != GLEW_OK)
                std::cout << "Failed to initialize GLEW\n";
            else
            {
                Renderer *renderer = Renderer::GetInstance();
                core.load();
                core.loadScene(new SceneMain());
                core.loop();
                core.unload();
                renderer->unload();
                delete renderer;
            }
        }
        glfwTerminate();
    }
    return (0);
}