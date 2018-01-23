#ifndef SHADER_HPP
#define SHADER_HPP

#include "global.hpp"

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
};

#endif