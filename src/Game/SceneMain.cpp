#include "SceneMain.hpp"
#include "Renderer.hpp"
#include "../Core/Button.hpp"
#include "../Core/Core.hpp"
#include "SceneGame.hpp"

SceneMain::SceneMain(void) :
	AWidget()
{}

SceneMain::~SceneMain(void)
{}

void	SceneMain::load(void)
{
	glClearColor(0.4, 0.4, 1.0, 1.0);
	_list.push_back(new Button("Start", this, Vec2f(1060, 684), Vec2f(100, 26), this));
	_list.push_back(new Button("Exit", this, Vec2f(1170, 684), Vec2f(100, 26), this));
}

void	SceneMain::unload(void)
{
	while (!_list.empty())
	{
		delete _list.back();
		_list.pop_back();
	}
}

void 	SceneMain::update(GLFWwindow *window)
{
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->update(window);
		++it;
	}
}

void	SceneMain::render(void)
{
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->render();
		++it;
	}
}


void	SceneMain::action(GLFWwindow *window, AWidget *src)
{
	Core *game = (Core *)glfwGetWindowUserPointer(window);
	if (game == NULL)
		return ;
	if (src == _list[0])
	{
		game->loadScene(new SceneGame());
		return ;
	}
	if (src == _list[1])
	{
		game->closeRequest();
		return ;
	}
}
