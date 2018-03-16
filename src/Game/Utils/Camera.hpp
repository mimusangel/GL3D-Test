#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../Core/Math/Vec3.hpp"
#include "../../Core/Math/Mat.hpp"
#include "../../Core/global.hpp"
#include "../../Core/Timer.hpp"

class Camera {
private:
	Vec3f   _position;
	Vec3f   _rotation;
	bool	_grab;

	Vec2f	_mousePos;
	Vec2f	_mouseDir;
	
public:
	Camera(Vec3f const &pos = Vec3f(), Vec3f const &rot = Vec3f()) :
		_position(pos),
		_rotation(rot),
		_grab(false)
	{}
	
	void	update(void)
	{
		if (_grab)
		{
			// std::cout << _mouseDir << std::endl;
			_rotation += Vec3f(M_TORADIANS(-_mouseDir.getY()), M_TORADIANS(_mouseDir.getX()), 0);
			if (_rotation[0] < M_TORADIANS(-90))
				_rotation[0] = M_TORADIANS(-90);
			if (_rotation[0] > M_TORADIANS(90))
				_rotation[0] = M_TORADIANS(90);
		}
		_mouseDir.set(0, 0);
	}

	bool	isGrab(void)
	{
		return (_grab);
	}

	void	setGrab(GLFWwindow *window, bool grab)
	{
		_grab = grab;
		if (_grab)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_mouseDir.set(0, 0);
		}
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	Mat4    getViewMatrix(void)
	{
		Mat4    posMat = Mat4::Translate(_position.negate());
		Mat4    rotMat = Mat4::Rotate(_rotation);
		return (posMat * rotMat);
	}

	void	setMousePos(float x, float y)
	{
		_mouseDir = Vec2f(x, y) - _mousePos;
		_mousePos.set(x, y);
	}

	Vec3f	getForward(void)
	{
		Vec3f	forward(0, 0, 1);
		Mat4	rotMat = Mat4::RotateY(-_rotation.getY());
		return (rotMat.transform(forward));
	}
	Vec3f	getSide(void)
	{
		Vec3f	forward(0, 0, 1);
		Mat4	rotMat = Mat4::RotateY(-_rotation.getY() - M_TORADIANS(90));
		return (rotMat.transform(forward));
	}

	void	move(Vec3f &dir)
	{
		if (!_grab)
			return ;
		_position += dir * 1.0f;// * (float)Timer::GetDelta();
	}

	void	setKey(int key, bool press)
	{
		if (!_grab)
			return ;
		//GLFW_KEY_W
	}
};

#endif