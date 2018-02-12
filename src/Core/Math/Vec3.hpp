#ifndef VEC3_HPP
#define VEC3_HPP

#include "Math.hpp"
#include "Vec2.hpp"

template<typename T>
class Vec3 {
private:
    T _x;
    T _y;
    T _z;

public:
    Vec3(T x = 0, T y = 0, T z = 0) : _x(x), _y(y), _z(z) {}
    Vec3(Vec2<T> const &v, T z) : _x(v.getX()), _y(v.getY()), _z(z) {}
    Vec3(Vec3 const &v) : _x(v.getX()), _y(v.getY()), _z(v.getZ()) {}

    Vec3			&operator=(Vec3 const &rhs)
    {
        return (set(rhs));
    }

    Vec3			operator+(Vec3 const &rhs)
    {
        return (Vec3<T>(_x + rhs.getX(), _y + rhs.getY(), _z + rhs.getZ()));
    }

    Vec3			operator-(Vec3 const &rhs)
    {
        return (Vec3<T>(_x - rhs.getX(), _y - rhs.getY(), _z - rhs.getZ()));
    }

    Vec3			operator*(Vec3 const &rhs)
    {
        return (Vec3<T>(_x * rhs.getX(), _y * rhs.getY(), _z * rhs.getZ()));
    }

    Vec3			operator/(Vec3 const &rhs)
    {
        return (Vec3<T>(_x / rhs.getX(), _y / rhs.getY(), _z / rhs.getZ()));
    }

    Vec3			&operator+=(Vec3 const &rhs)
    {
        return (set(_x + rhs.getX(), _y + rhs.getY(), _z + rhs.getZ()));
    }

    Vec3			&operator-=(Vec3 const &rhs)
    {
        return (set(_x - rhs.getX(), _y - rhs.getY(), _z - rhs.getZ()));
    }

    Vec3			&operator*=(Vec3 const &rhs)
    {
        return (set(_x * rhs.getX(), _y * rhs.getY(), _z * rhs.getZ()));
    }

    Vec3			&operator/=(Vec3 const &rhs)
    {
        return (set(_x / rhs.getX(), _y / rhs.getY(), _z / rhs.getZ()));
    }

    template<typename U>
    Vec3			operator*(U const rhs)
    {
        return (Vec3<T>(_x * rhs, _y * rhs, _z * rhs));
    }

    template<typename U>
    Vec3			operator/(U const rhs)
    {
        return (Vec3<T>(_x / rhs, _y / rhs, _z / rhs));
    }

    template<typename U>
    Vec3			operator+(U const rhs)
    {
        return (Vec3<T>(_x + rhs, _y + rhs, _z + rhs));
    }

    template<typename U>
    Vec3			operator-(U const rhs)
    {
        return (Vec3<T>(_x - rhs, _y - rhs, _z - rhs));
    }

    template<typename U>
    Vec3			operator*=(U const rhs)
    {
        return (set(_x * rhs, _y * rhs, _z * rhs));
    }

    template<typename U>
    Vec3			operator/=(U const rhs)
    {
        return (set(_x / rhs, _y / rhs, _z / rhs));
    }

    template<typename U>
    Vec3			operator+=(U const rhs)
    {
        return (set(_x + rhs, _y + rhs, _z + rhs));
    }

    template<typename U>
    Vec3			operator-=(U const rhs)
    {
        return (set(_x - rhs, _y - rhs, _z - rhs));
    }

    T               &operator[](int x)
    {
        if (x < 0 || x > 2)
            throw std::out_of_range("range is invalid!");
        if (x == 1)
            return (_y);
        else if (x == 2)
            return (_z);
        return (_x);
    }

    T               getX(void) const { return (_x); }

    Vec3            &setX(T x)
    {
        _x = x;
        return (*this);
    }

    T               getY(void) const { return (_y); }

    Vec3            &setY(T y)
    {
        _y = y;
        return (*this);
    }

    T               getZ(void) const { return (_z); }

    Vec3            &setZ(T z)
    {
        _z = z;
        return (*this);
    }

    Vec3            &set(T x, T y, T z)
    {
        return (setX(x).setY(y).setY(z));
    }

    Vec3            &set(Vec3 const &rhs)
    {
        return (set(rhs._x, rhs._y, rhs._z));
    }

    double          lengthSqrt(void) { return(_x * _x + _y * _y + _z * _z); }
	double          length(void) { return (sqrt(lengthSqrt())); }

    Vec3			&normalize(void)
    {
        *this /= length();
        return (*this);
    }

	double			distance(Vec3 const &target)
    {
        Vec3<T> vec = target - *this;
        return (vec.length());
    }

	double			dot(Vec3 const &rhs)
    {
        return (_x * rhs.getX() + _y * rhs.getY() + _z * rhs.getZ());
    }

    Vec3		    cross(Vec3 const &v)
    {
        return (Vec3f(_y * v[2] - _z * v[1],
           _z * v[0] - _x * v[2],
            _x * v[1] - _y * v[0]
        ));
    }

    Vec3		    reflect(Vec3 const &normal)
    {
        return (Vec3<T>(*this - normal * (this->dot(normal) * 2.0f)));
    }

    Vec3		    refract(Vec3 const &normal, float eta)
    {
        float d = normal.dot(*this);
        float k = 1.f - eta * eta * (1.f - d * d);
        if (k < 0.f)
            return (Vec3<T>());
        return (Vec3<T>(normal * ((*this * eta) - (eta * d + sqrtf(k)))));
    }

    Vec2<T>            xy()
    {
        return (Vec2<T>(_x, _y));
    }

    Vec2<T>            xz()
    {
        return (Vec2<T>(_x, _z));
    }

    Vec2<T>            yz()
    {
        return (Vec2<T>(_y, _z));
    }

    Vec3            copy(void)
    {
        return (Vec3<T>(*this));
    }
};

template<typename T>
std::ostream &operator<<(std::ostream& os, Vec3<T> const &rhs)  
{  
    os << rhs.getX() << ", " << rhs.getY() << ", " << rhs.getZ();
    return (os);  
}  

typedef Vec3<float> Vec3f;


#endif