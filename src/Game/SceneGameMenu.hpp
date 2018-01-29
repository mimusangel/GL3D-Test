#ifndef SCENEGAMEMENU_HPP
#define SCENEGAMEMENU_HPP

#include <vector>

#include "../Core/IListenner.hpp"
#include "../Core/AWidget.hpp"
#include "../Core/Mesh.hpp"

class SceneGameMenu: public virtual AWidget, public IListenner {
protected:
	std::vector<AWidget *>	_list;

public:
	SceneGameMenu(Vec2f pos);
	~SceneGameMenu(void);
	void	load(void);
	void	unload(void);
	void 	update(GLFWwindow *window);
	void	render(void);
	void	action(GLFWwindow *window, AWidget *src);
};

#endif
