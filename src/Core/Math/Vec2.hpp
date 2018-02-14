#ifndef VEC2_HPP
#define VEC2_HPP

#include "Math.hpp"


template<typename T>
class Vec2 {
private:
    T _x;
    T _y;

public:
    Vec2(T x = 0, T y = 0) : _x(x), _y(y) {}
    Vec2(Vec2 const &v) : _x(v.getX()), _y(v.getY()) {}

    Vec2			&operator=(Vec2 const &rhs)
    {
        return (set(rhs));
    }

    Vec2			operator+(Vec2 const &rhs)
    {
        return (Vec2<T>(_x + rhs.getX(), _y + rhs.getY()));
    }

    Vec2			operator-(Vec2 const &rhs)
    {
        return (Vec2<T>(_x - rhs.getX(), _y - rhs.getY()));
    }

    Vec2			operator*(Vec2 const &rhs)
    {
        return (Vec2<T>(_x * rhs.getX(), _y * rhs.getY()));
    }

    Vec2			operator/(Vec2 const &rhs)
    {
        return (Vec2<T>(_x / rhs.getX(), _y / rhs.getY()));
    }

    Vec2			&operator+=(Vec2 const &rhs)
    {
        return (set(_x + rhs.getX(), _y + rhs.getY()));
    }

    Vec2			&operator-=(Vec2 const &rhs)
    {
        return (set(_x - rhs.getX(), _y - rhs.getY()));
    }

    Vec2			&operator*=(Vec2 const &rhs)
    {
        return (set(_x * rhs.getX(), _y * rhs.getY()));
    }

    Vec2			&operator/=(Vec2 const &rhs)
    {
        return (set(_x / rhs.getX(), _y / rhs.getY()));
    }

    template<typename U>
    Vec2			operator*(U const rhs)
    {
        return (Vec2<T>(_x * rhs, _y * rhs));
    }

    template<typename U>
    Vec2			operator/(U const rhs)
    {
        return (Vec2<T>(_x / rhs, _y / rhs));
    }

    template<typename U>
    Vec2			operator+(U const rhs)
    {
        return (Vec2<T>(_x + rhs, _y + rhs));
    }

    template<typename U>
    Vec2			operator-(U const rhs)
    {
        return (Vec2<T>(_x - rhs, _y - rhs));
    }

    template<typename U>
    Vec2			operator*=(U const rhs)
    {
        return (set(_x * rhs, _y * rhs));
    }

    template<typename U>
    Vec2			operator/=(U const rhs)
    {
        return (set(_x / rhs, _y / rhs));
    }

    template<typename U>
    Vec2			operator+=(U const rhs)
    {
        return (set(_x + rhs, _y + rhs));
    }

    template<typename U>
    Vec2			operator-=(U const rhs)
    {
        return (set(_x - rhs, _y - rhs));
    }

    T               &operator[](int x)
    {
        if (x < 0 || x > 1)
            throw std::out_of_range("range is invalid!");
        if (x == 1)
            return (_y);
        return (_x);
    }

    float               at(int x) const
    {
        if (x < 0 || x > 1)
            throw std::out_of_range("range is invalid!");
        if (x == 1)
            return (_y);
        return (_x);
    }

    T               getX(void) const { return (_x); }

    Vec2            &setX(T x)
    {
        _x = x;
        return (*this);
    }

    T               getY(void) const { return (_y); }

    Vec2            &setY(T y)
    {
        _y = y;
        return (*this);
    }

    Vec2            &set(T x, T y)
    {
        return (setX(x).setY(y));
    }

    Vec2            &set(Vec2 const &rhs)
    {
        return (set(rhs._x, rhs._y));
    }

    Vec2			&rotate(double rad)
    {
        double c = cos(rad);
        double s = sin(rad);
        double tx = _x * c - _y * s;
        double ty = _x * s + _y * c;
        return (set(tx, ty));
    }

    double          lengthSqrt(void) { return(_x * _x + _y * _y); }
	double          length(void) { return (sqrt(lengthSqrt())); }

    Vec2			&normalize(void)
    {
        *this /= length();
        return (*this);
    }

	double			distance(Vec2 const &target)
    {
        Vec2<T> vec = target - *this;
        return (vec.length());
    }

	double			dot(Vec2 const &rhs)
    {
        return (_x * rhs.getX() + _y * rhs.getY());
    }

	Vec2			normal(void)
    {
        return (Vec2<T>(-_y, _x));
    }

    Vec2            copy(void)
    {
        return (Vec2<T>(*this));
    }
};

template<typename T>
std::ostream &operator<<(std::ostream& os, Vec2<T> const &rhs)  
{  
    os << rhs.getX() << ", " << rhs.getY();
    return (os);  
}  

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;


#endif