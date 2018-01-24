#ifndef VEC2F_HPP
#define VEC2F_HPP

#include <iostream>
#include <cmath>

class Vec2f {
protected:
	float	_x;
	float	_y;

public:
	Vec2f(float x = 0.0f, float y = 0.0f);
	Vec2f(Vec2f const &copy);
	~Vec2f() {}
	Vec2f			&operator=(Vec2f const &rhs);
	Vec2f			operator+(Vec2f const &rhs);
	Vec2f			operator-(Vec2f const &rhs);
	Vec2f			operator*(Vec2f const &rhs);
	Vec2f			operator/(Vec2f const &rhs);
	Vec2f			&operator+=(Vec2f const &rhs);
	Vec2f			&operator-=(Vec2f const &rhs);
	Vec2f			&operator*=(Vec2f const &rhs);
	Vec2f			&operator/=(Vec2f const &rhs);
	Vec2f			operator*(float const rhs);
	Vec2f			&operator*=(float const rhs);

	inline float 	getX(void) const { return (_x); }
	Vec2f			&setX(float x);
	inline float 	getY(void) const { return (_y); }
	Vec2f			&setY(float y);

	inline double	lengthSqrt(void) { return(_x * _x + _y * _y); }
	inline double	length(void) { return (sqrt(lengthSqrt())); }
	Vec2f			&rotate(double deg);
	Vec2f			&normalize(void);
	double			distance(Vec2f const &target);
	double			dot(Vec2f const &rhs);
	Vec2f			normal(void);
	Vec2f			getRotate(double deg);
	Vec2f			getNormalize(void);
};

std::ostream	&operator<<(std::ostream &os, const Vec2f &rhs);

#endif