#include "AWidget.hpp"

AWidget::AWidget(AWidget *parent, Vec2f const &pos, Vec2f const &size) :
	_parent(parent),
	_pos(pos),
	_size(size)
{}

void 	AWidget::update(GLFWwindow *window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (xpos >= _pos.getX() && xpos < _pos.getX() + _size.getX()
		&& ypos >= _pos.getY() && ypos < _pos.getY() + _size.getY())
	{
		mouseOver(window, xpos, ypos);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			mouseDown(window, xpos, ypos);
		else
			mouseUp(window, xpos, ypos);
	}
}

Vec2f	AWidget::getPosition(void)
{
	if (_parent != NULL)
		return (_parent->getPosition() + getLocalPosition());
	return (getLocalPosition());
}

Vec2f	&AWidget::getLocalPosition(void)
{
	return (_pos);
}

AWidget	&AWidget::setLocalPosition(Vec2f const &rhs)
{
	_pos = rhs;
	return (*this);
}

Vec2f	&AWidget::getSize(void)
{
	return (_size);
}

AWidget	&AWidget::setSize(Vec2f const &rhs)
{
	_size = rhs;
	return (*this);
}