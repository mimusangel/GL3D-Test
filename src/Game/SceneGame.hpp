#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "../Core/IListenner.hpp"
#include "../Core/AWidget.hpp"
#include "../Core/Mesh.hpp"
#include "SceneGameMenu.hpp"

class SceneGame: public virtual AWidget {
protected:
	SceneGameMenu		*_menu;
	bool				pause;

public:
	SceneGame(void);
	~SceneGame(void);
	void	load(void);
	void	unload(void);
	void	fixedUpdate(GLFWwindow *window);
	void 	update(GLFWwindow *window);
	void	render(void);
	void    keyRelease(GLFWwindow *window, int key);
};

#endif
