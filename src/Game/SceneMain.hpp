#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP

#include <vector>

#include "../Core/AWidget.hpp"
#include "../Core/Mesh.hpp"

class SceneMain: public virtual AWidget {
protected:
	Mesh					*_mesh;
	std::vector<AWidget *>	_list;

public:
	SceneMain(void);
	~SceneMain(void);
	void	load(void);
	void	unload(void);
	void 	update(GLFWwindow *window);
	void	render(void);
};

#endif
