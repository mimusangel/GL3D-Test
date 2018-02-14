#ifndef AWIDGET_HPP
#define AWIDGET_HPP

#include "../global.hpp"
#include "../Math/Vec2.hpp"

class AWidget {
private:
	bool		_dad;
	bool		_enter;
	bool		_lClick;
	bool		_rClick;

	static AWidget	*_Focus;

protected:
	AWidget		*_parent;
	Vec2f		_pos;
	Vec2f		_size;

public:
	AWidget(AWidget *parent = NULL, Vec2f const &pos = Vec2f(), Vec2f const &size = Vec2f());
	virtual ~AWidget(void);
	virtual void	load(void) = 0;
	virtual void	unload(void) = 0;
	virtual void	fixedUpdate(GLFWwindow *window) {};
	virtual void 	update(GLFWwindow *window);
	virtual void	render(void) = 0;
	virtual void	mouseOver(GLFWwindow *window, double x, double y) {};
	virtual void	mouseDown(GLFWwindow *window, double x, double y, int button) {};
	virtual void	mouseDrag(GLFWwindow *window, double x, double y, double offsetx, double offsety) {};
	virtual void	mouseDrop(GLFWwindow *window, double x, double y, double offsetx, double offsety) {};
	virtual void	mouseEnter(GLFWwindow *window, double x, double y) {};
	virtual void	mouseLeave(GLFWwindow *window, double x, double y) {};
	virtual void	mouseUp(GLFWwindow *window, double x, double y, int button) {};
	virtual void	mouseClick(GLFWwindow *window, double x, double y, int button) {};
    virtual void    keyPress(GLFWwindow *window, int key) {};
    virtual void    keyRelease(GLFWwindow *window, int key) {};
    virtual void    keyRepeat(GLFWwindow *window, int key) {};
	virtual void	mouseMove(GLFWwindow *window, float x, float y) {};
    virtual void    mouseButtonPress(GLFWwindow *window, int button) {};
    virtual void    mouseButtonRelease(GLFWwindow *window, int button) {};

	Vec2f	getPosition(void);
	Vec2f	&getLocalPosition(void);
	AWidget	&setLocalPosition(Vec2f const &rhs);
	Vec2f	&getSize(void);
	AWidget	&setSize(Vec2f const &rhs);
	inline bool		isMouseOver(void) { return (_enter); }
};

#endif