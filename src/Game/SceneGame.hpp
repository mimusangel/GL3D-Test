#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "../Core/UI/IListenner.hpp"
#include "../Core/UI/AWidget.hpp"
#include "../Core/Shader/Shader.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Math/Mat.hpp"

#include "SceneGameMenu.hpp"

class SceneGame: public virtual AWidget {
protected:
	SceneGameMenu		*_menu;
	bool				_pause;

	Mat4				projection;
	Shader				*_terrainShader;
	Mesh				*_terrainMesh;
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
