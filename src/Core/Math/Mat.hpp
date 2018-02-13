#ifndef MAT_HPP
#define MAT_HPP

#include "Math.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

template<int S>
class Mat {
private:
    float   _data[S * S];

public:
    typedef Mat<4> Mat4;


    Mat(void)
    {
        for (int i = 0; i < S * S; i++)
            _data[i] = 0.0f;
    }

    float               &operator[](int x)
    {
        if (x < 0 || x >= S * S)
            throw std::out_of_range("range is invalid!");
        return (_data[x]);
    }

    Mat<S>		operator*(const Mat<S> &v)
    {
        Mat<S>	mat;

        for (int i = 0; i < S; i++)
            for (int j = 0; j < S; j++)
                for (int k = 0; k < S; k++)
                    mat[i + j * S] += _data[k + j * S] * v.at(i + k * S);
        return (mat);
    }

    float               at(int x) const
    {
        if (x < 0 || x >= S * S)
            throw std::out_of_range("range is invalid!");
        return (_data[x]);
    }

    float       *data(void) { return (_data); }

    Vec3f		transform(Vec3f &v)
    {
        return (Vec3f(
            _data[0] * v[0] + _data[4] * v[1] + _data[8] * v[2] + _data[12],
            _data[1] * v[0] + _data[5] * v[1] + _data[9] * v[2] + _data[13],
            _data[2] * v[0] + _data[6] * v[1] + _data[10] * v[2] + _data[14]
        ));
    }    

    /*
    ** Matrice Static
    */
    static Mat4     Identity(void)
    {
        Mat4 mat;
        for (int i = 0; i < 4; i++)
            mat[i * 4 + i] = 1.0f;
        return (mat);
    }

    static Mat4     Translate(float x, float y, float z)
    {
        Mat4 mat = Identity();
        mat[12] = x;
        mat[13] = y;
        mat[14] = z;
        return (mat);
    }

    static Mat4     Translate(Vec3f const &vec)
    {
        return (Translate(vec.getX(), vec.getY(), vec.getZ()));
    }

    static Mat4     Translate(float x, float y)
    {
        return (Translate(x, y, 0));
    }

    static Mat4     Translate(Vec2f const &vec)
    {
        return (Translate(vec.getX(), vec.getY(), 0));
    }

    static Mat4     Scale(float x, float y, float z)
    {
        Mat4 mat = Identity();
        mat[0] = x;
        mat[5] = y;
        mat[10] = z;
        return (mat);
    }

    static Mat4     Scale(Vec3f const &vec)
    {
        return (Scale(vec.getX(), vec.getY(), vec.getZ()));
    }

    static Mat4     Scale(float x, float y)
    {
        return (Scale(x, y, 1));
    }

    static Mat4     Scale(Vec2f const &vec)
    {
        return (Scale(vec.getX(), vec.getY(), 1));
    }

    static Mat4     ScaleAll(float i)
    {
        return (Scale(i, i, i));
    }

    static Mat4	Rotate(float x, float y, float z)
    {
        Mat4 rx = RotateX(x);
        Mat4 ry = RotateY(y);
        Mat4 rz = RotateZ(z);
        return rz * (ry * rx);
    }

    static Mat4	RotateX(float r)
    {
        Mat4 mat = Identity();
        float rcos = cosf(r);
        float rsin = sinf(r);
        mat[5] = rcos;
        mat[6] = rsin;
        mat[9] = -rsin;
        mat[10] = rcos;
        return (mat);
    }

    static Mat4	RotateY(float r)
    {
        Mat4 mat = Identity();
        float rcos = cosf(r);
        float rsin = sinf(r);
        mat[0] = rcos;
        mat[2] = rsin;
        mat[8] = -rsin;
        mat[10] = rcos;
        return (mat);
    }

    static Mat4	RotateZ(float r)
    {
        Mat4 mat = Identity();
        float rcos = cosf(r);
        float rsin = sinf(r);
        mat[0] = rcos;
        mat[1] = rsin;
        mat[4] = -rsin;
        mat[5] = rcos;
        return (mat);
    }

    static Mat4	Rotate(Vec3f const &vec)
    {
        return (Rotate(vec.getX(), vec.getY(), vec.getZ()));
    }


    static Mat4	Perspective(float fov, float aspect, float zNear, float zFar)
    {
        Mat4 result;
        fov = tanf(fov / 2.f);
        float dist = zNear - zFar;
        result[0] = 1.f / (fov * aspect);
        result[5] = 1.f / fov;
        result[10] = (-zNear - zFar) / dist;
        result[11] = 1.f;
        result[14] = 2.f * zFar * zNear / dist;
        return (result);
    }

    static Mat4	Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        Mat4 result = Identity();
        result[0] = 2.f / (right - left);
        result[5] = 2.f / (top - bottom);
        result[10] = -2.f / (zFar - zNear);
        result[12] = -(right + left) / (right - left);
        result[13] = -(top + bottom) / (top - bottom);
        result[14] = -(zFar + zNear) / (zFar - zNear);
        return (result);
    }
};

typedef Mat<4> Mat4;

template<int S>
std::ostream &operator<<(std::ostream& os, Mat<S> const &rhs)  
{  
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < S; j++)
        {
            if (j != 0)
                os << ", ";
            os << rhs.at(j + i * S);
        }
        os << std::endl;
    }
    return (os);  
}  

#endif