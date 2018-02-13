#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "../Core/UI/IListenner.hpp"
#include "../Core/UI/AWidget.hpp"
#include "../Core/Mesh.hpp"
#include "SceneGameMenu.hpp"
#include "Player.hpp"

class SceneGame: public virtual AWidget {
protected:
	SceneGameMenu		*_menu;
	bool				_pause;
	Player				_player;

public:
	SceneGame(void);
	~SceneGame(void);
	void	load(void);
	void	unload(void);
	void	fixedUpdate(GLFWwindow *window);
	void 	update(GLFWwindow *window);
	void	render(void);
	void    keyRelease(GLFWwindow *window, int key);
	
	inline bool isPause(void) { return (_pause); }
	inline void setPause(bool pause) { _pause = pause; }
};

#endif
