#include "SceneGame.hpp"

SceneGame::SceneGame(void) :
	AWidget(),
	_menu(NULL)
{}

SceneGame::~SceneGame(void)
{}

void	SceneGame::load(void)
{
	_menu = new SceneGameMenu(Vec2f(640, 360));
	glClearColor(0.4, 0.4, 0.4, 1.0);
}

void	SceneGame::unload(void)
{
	if (_menu != NULL)
	{
		delete _menu;
		_menu = NULL;
	}
}

void	SceneGame::fixedUpdate(GLFWwindow *window)
{
	if (!pause)
	{

	}
}

void 	SceneGame::update(GLFWwindow *window)
{
	if (_menu != NULL && pause)
		_menu->update(window);
	else
	{

	}
}

void	SceneGame::render(void)
{
	if (_menu != NULL && pause)
		_menu->render();
}

void    SceneGame::keyRelease(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		pause = !pause;
		std::cout << pause << std::endl;
	}
}