#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "IListenner.hpp"
#include "AWidget.hpp"

class Button : public AWidget {
private:
	static Mesh	*_mesh;
	static Shader *_shader;

protected:
	std::string	_name;
	IListenner	*_listenner;

public:
	Button(std::string const &name, AWidget *parent = NULL, Vec2f const &pos = Vec2f(), Vec2f const &size = Vec2f(100, 20), IListenner *listenner = NULL);
	void	load(void);
	void	unload(void);
	void	render(void);
	Button	&setListenner(IListenner *listenner);
	void	mouseClick(GLFWwindow *window, double x, double y, int button);
	inline std::string	&getName(void) { return (_name); }
	static void	Load(void);
	static void	UnLoad(void);
};

#endif