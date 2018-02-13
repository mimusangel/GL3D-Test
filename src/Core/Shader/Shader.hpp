#ifndef SHADER_HPP
#define SHADER_HPP

#include "../global.hpp"
#include "../Math/Vec2.hpp"
#include "../Math/Vec3.hpp"
#include "../Math/Mat.hpp"

class Shader {
private:
	int				_size;
	GLuint			_program;
	GLuint			*_shaders;
public:
	Shader(int size);
	~Shader(void);
	void			load(unsigned int shaderIndex, GLenum shaderType, const char *script);
	void			compile(void);
	void			bind(void);
	void			unbind(void);
	static void		Unbind(void);
	void			uniform1i(std::string const &name, int i);
	void			uniform1f(std::string const &name, float x);
	void			uniform2f(std::string const &name, float x, float y);
	void			uniform2f(std::string const &name, float *data);
	void			uniform2f(std::string const &name, Vec2f const &vec);
	void			uniform3f(std::string const &name, float x, float y, float z);
	void			uniform3f(std::string const &name, Vec3f const &vec);
	void			uniform3f(std::string const &name, float *data);
	void			uniform4f(std::string const &name, float x, float y, float z, float w);
	void			uniform4f(std::string const &name, float *data);
	void			uniformMat(std::string const &name, Mat4 &mat);
};

#endif