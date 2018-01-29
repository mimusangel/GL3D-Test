#include "Vec2f.hpp"

Vec2f::Vec2f(float x, float y) :
	_x(x),
	_y(y)
{}

Vec2f::Vec2f(Vec2f const &copy)
{
	*this = copy;
}

Vec2f			&Vec2f::operator=(Vec2f const &rhs)
{
	setX(rhs.getX());
	setY(rhs.getY());
	return (*this);
}

Vec2f			Vec2f::operator+(Vec2f const &rhs)
{
	return (Vec2f(_x + rhs.getX(), _y + rhs.getY()));
}

Vec2f			Vec2f::operator-(Vec2f const &rhs)
{
	return (Vec2f(_x - rhs.getX(), _y - rhs.getY()));
}

Vec2f			Vec2f::operator*(Vec2f const &rhs)
{
	return (Vec2f(_x * rhs.getX(), _y * rhs.getY()));
}

Vec2f			Vec2f::operator/(Vec2f const &rhs)
{
	return (Vec2f(_x / rhs.getX(), _y / rhs.getY()));
}

Vec2f			&Vec2f::operator+=(Vec2f const &rhs)
{
	_x += rhs.getX();
	_y += rhs.getY();
	return (*this);
}

Vec2f			&Vec2f::operator-=(Vec2f const &rhs)
{
	_x -= rhs.getX();
	_y -= rhs.getY();
	return (*this);
}

Vec2f			&Vec2f::operator*=(Vec2f const &rhs)
{
	_x *= rhs.getX();
	_y *= rhs.getY();
	return (*this);
}

Vec2f			&Vec2f::operator/=(Vec2f const &rhs)
{
	_x /= rhs.getX();
	_y /= rhs.getY();
	return (*this);
}

Vec2f			Vec2f::operator*(float const rhs)
{
	return (Vec2f(_x * rhs, _y * rhs));
}

Vec2f			&Vec2f::operator*=(float const rhs)
{
	_x *= rhs;
	_y *= rhs;
	return (*this);
}

Vec2f			&Vec2f::setX(float x)
{
	_x = x;
	return (*this);
}

Vec2f			&Vec2f::setY(float y)
{
	_y = y;
	return (*this);
}

Vec2f			&Vec2f::rotate(double deg)
{
	double theta = deg / 180.0 * M_PI;
	double c = cos(theta);
	double s = sin(theta);
	double tx = _x * c - _y * s;
	double ty = _x * s + _y * c;
	_x = tx;
	_y = ty;
	return (*this);
}

Vec2f			&Vec2f::normalize(void)
{
	double len = length();
	if (len == 0.0)
		return (*this);
	*this /= len;
	return (*this);
}

double			Vec2f::distance(Vec2f const &target)
{
	Vec2f vec(target);
	vec -= *this;
	return (vec.length());
}

double			Vec2f::dot(Vec2f const &rhs)
{
	return (getX() * rhs.getX() + getY() * rhs.getY());
}

Vec2f			Vec2f::normal(void)
{
	return (Vec2f(_y, -_x));
}

Vec2f			Vec2f::getRotate(double deg)
{
	return ((Vec2f(*this)).rotate(deg));
}

Vec2f			Vec2f::getNormalize(void)
{
	return ((Vec2f(*this)).normalize());
}


std::ostream	&operator<<(std::ostream &os, const Vec2f &rhs)
{
	os << "Vec2f(" << rhs.getX() << ", " << rhs.getY() << ")" << std::endl;
	return (os);
}