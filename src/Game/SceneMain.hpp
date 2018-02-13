#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP

#include <vector>

#include "../Core/UI/IListenner.hpp"
#include "../Core/UI/AWidget.hpp"
#include "../Core/Mesh.hpp"

class SceneMain: public virtual AWidget, public IListenner {
protected:
	std::vector<AWidget *>	_list;

public:
	SceneMain(void);
	~SceneMain(void);
	void	load(void);
	void	unload(void);
	void 	update(GLFWwindow *window);
	void	render(void);
	void	action(GLFWwindow *window, AWidget *src);
};

#endif
