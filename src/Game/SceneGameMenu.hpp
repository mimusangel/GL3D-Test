#ifndef SCENEGAMEMENU_HPP
#define SCENEGAMEMENU_HPP

#include <vector>

#include "../Core/UI/IListenner.hpp"
#include "../Core/UI/AWidget.hpp"
#include "../Core/Shader/Shader.hpp"

class SceneGameMenu: public virtual AWidget, public IListenner {
protected:
	std::vector<AWidget *>	_list;
	Shader					*_shader;

public:
	SceneGameMenu(AWidget *parent, Vec2f pos);
	~SceneGameMenu(void);
	void	load(void);
	void	unload(void);
	void 	update(GLFWwindow *window);
	void	render(void);
	void	action(GLFWwindow *window, AWidget *src);
};

#endif
