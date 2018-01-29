#include "AWidget.hpp"

bool		AWidget::_LClick = false;
bool		AWidget::_RClick = false;
AWidget		*AWidget::_Focus = NULL;

AWidget::AWidget(AWidget *parent, Vec2f const &pos, Vec2f const &size) :
	_parent(parent),
	_pos(pos),
	_size(size)
{}

AWidget::~AWidget(void)
{}

void 	AWidget::update(GLFWwindow *window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (xpos >= _pos.getX() && xpos < _pos.getX() + _size.getX()
		&& ypos >= _pos.getY() && ypos < _pos.getY() + _size.getY())
	{
		if (!_enter)
		{
			mouseEnter(window, xpos, ypos);
			_enter = true;
		}
		mouseOver(window, xpos, ypos);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			mouseDown(window, xpos, ypos, GLFW_MOUSE_BUTTON_LEFT);
			mouseDrag(window, xpos, ypos, xpos - _pos.getX(), ypos - _pos.getY());
			_dad = true;
			_LClick = true;
			_Focus = this;
		}
		else
		{
			mouseUp(window, xpos, ypos, GLFW_MOUSE_BUTTON_LEFT);
			if (_LClick)
			{
				mouseClick(window, xpos, ypos, GLFW_MOUSE_BUTTON_LEFT);
				_LClick = false;
			}
			if (_dad)
			{
				mouseDrop(window, xpos, ypos, xpos - _pos.getX(), ypos - _pos.getY());
				_dad = false;
			}
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mouseDown(window, xpos, ypos, GLFW_MOUSE_BUTTON_RIGHT);
			_RClick = true;
			_Focus = this;
		}
		else
		{
			if (_RClick)
			{
				mouseClick(window, xpos, ypos, GLFW_MOUSE_BUTTON_RIGHT);
				_RClick = false;
			}
			mouseUp(window, xpos, ypos, GLFW_MOUSE_BUTTON_RIGHT);
		}
	}
	else
	{
		_LClick = false;
		_RClick = false;
		if (_dad)
		{
			mouseDrop(window, xpos, ypos, xpos - _pos.getX(), ypos - _pos.getY());
			_dad = false;
		}
		if (_enter)
		{
			mouseLeave(window, xpos, ypos);
			_enter = false;
		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS
		&& glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS
		&& _Focus == this)
	{
		_Focus = NULL;
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