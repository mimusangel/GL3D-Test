#include "SceneGameMenu.hpp"

#include "../Core/Button.hpp"
#include "../Core/Core.hpp"

SceneGameMenu::SceneGameMenu(Vec2f pos) :
	AWidget(NULL, pos)
{}

SceneGameMenu::~SceneGameMenu(void)
{
	
}

void	SceneGameMenu::load(void)
{

}

void	SceneGameMenu::unload(void)
{
	while (!_list.empty())
	{
		delete _list.back();
		_list.pop_back();
	}
}

void 	SceneGameMenu::update(GLFWwindow *window)
{
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->update(window);
		++it;
	}
}

void	SceneGameMenu::render(void)
{
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->render();
		++it;
	}
}

void	SceneGameMenu::action(GLFWwindow *window, AWidget *src)
{
	Core *game = (Core *)glfwGetWindowUserPointer(window);
	if (game == NULL)
		return ;

}
