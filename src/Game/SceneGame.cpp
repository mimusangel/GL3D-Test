#include "SceneGame.hpp"

SceneGame::SceneGame(void) :
	AWidget(),
	_menu(NULL)
{}

SceneGame::~SceneGame(void)
{}

void	SceneGame::load(void)
{
	_menu = new SceneGameMenu(this, Vec2f(640, 360));
	_menu->load();
	glClearColor(0.4, 0.4, 0.4, 1.0);
	_pause = false;
}

void	SceneGame::unload(void)
{
	if (_menu != NULL)
	{
		_menu->unload();
		delete _menu;
		_menu = NULL;
	}
}

void	SceneGame::fixedUpdate(GLFWwindow *window)
{
	if (!_pause)
	{

	}
}

void 	SceneGame::update(GLFWwindow *window)
{
	if (_menu != NULL && _pause)
		_menu->update(window);
	else
	{

	}
}

void	SceneGame::render(void)
{
	if (_menu != NULL && _pause)
		_menu->render();
}

void    SceneGame::keyRelease(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		_pause = !_pause;
	}
}