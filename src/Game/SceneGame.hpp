#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "../Core/UI/IListenner.hpp"
#include "../Core/UI/AWidget.hpp"
#include "../Core/Shader/Shader.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Math/Mat.hpp"

#include "SceneGameMenu.hpp"
#include "Utils/Camera.hpp"

class SceneGame: public virtual AWidget {
protected:
	SceneGameMenu		*_menu;
	bool				_pause;

	Camera				_camera;
	Mat4				_projection;
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
	void    keyPress(GLFWwindow *window, int key);
	void    keyRepeat(GLFWwindow *window, int key);
	void    mouseButtonPress(GLFWwindow *window, int button);
	void	mouseMove(GLFWwindow *window, float x, float y);

	inline bool isPause(void) { return (_pause); }
	void setPause(bool pause);
};

#endif
