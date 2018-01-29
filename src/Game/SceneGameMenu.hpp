#ifndef SCENEGAMEMENU_HPP
#define SCENEGAMEMENU_HPP

#include <vector>

#include "../Core/IListenner.hpp"
#include "../Core/AWidget.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Shader.hpp"

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
