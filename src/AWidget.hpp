#ifndef AWIDGET_HPP
#define AWIDGET_HPP

#include "global.hpp"
#include "Vec2f.hpp"

class AWidget {
private:
	AWidget		*_parent;
	Vec2f		_pos;
	Vec2f		_size;

public:
	AWidget(AWidget *parent = NULL, Vec2f const &pos = Vec2f(), Vec2f const &size = Vec2f());
	virtual void	load(void) = 0;
	virtual void	unload(void) = 0;
	virtual void 	update(GLFWwindow *window);
	virtual void	render(void) = 0;
	virtual void	mouseOver(GLFWwindow *window, double x, double y) = 0;
	virtual void	mouseDown(GLFWwindow *window, double x, double y) = 0;
	virtual void	mouseUp(GLFWwindow *window, double x, double y) = 0;

	Vec2f	getPosition(void);
	Vec2f	&getLocalPosition(void);
	AWidget	&setLocalPosition(Vec2f const &rhs);
	Vec2f	&getSize(void);
	AWidget	&setSize(Vec2f const &rhs);
};

#endif