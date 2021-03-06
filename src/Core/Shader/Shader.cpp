#include "Shader.hpp"

Shader::Shader(int size) :
	_size(size),
	_program(0),
	_shaders(NULL)
{
	if (_size > 0)
	{
		_shaders = new GLuint[_size];
		for (unsigned int i = 0; i < _size; i++)
			_shaders[i] = 0;
	}
}

Shader::~Shader()
{
	if (_shaders != NULL)
	{
		for (unsigned int i = 0; i < _size; i++)
		{
			if (_shaders[i])
			{
				glDetachShader(_program, _shaders[i]);
				glDeleteShader(_shaders[i]);
				_shaders[i] = 0;
			}
		}
		delete[] _shaders;
	}
	if (_program)
		glDeleteProgram(_program);
}

void			Shader::load(unsigned int shaderIndex, GLenum shaderType, const char *script)
{
	if (shaderIndex >= _size)
		return ;
	_shaders[shaderIndex] = glCreateShader(shaderType);
	glShaderSource(_shaders[shaderIndex], 1, (const GLchar *const *)&script, NULL);
	glCompileShader(_shaders[shaderIndex]);
	// TEST DEBUG
	GLint	result;
	glGetShaderiv(_shaders[shaderIndex], GL_COMPILE_STATUS, &result);
	if (result == 0)
	{
		int		log_length;
		glGetShaderiv(_shaders[shaderIndex], GL_INFO_LOG_LENGTH, &log_length);
		if (!log_length)
			return ;
		char	*log = new char[log_length];
		glGetShaderInfoLog(_shaders[shaderIndex], log_length, NULL, log);
		if (shaderType == GL_VERTEX_SHADER)
			std::cout << "Vertex Shader:" << std::endl;
		else if (shaderType == GL_FRAGMENT_SHADER)
			std::cout << "Fragment Shader:" << std::endl;
		else if (shaderType == GL_GEOMETRY_SHADER)
			std::cout << "Geometry Shader:" << std::endl;
		else
			std::cout << "Other Shader:" << std::endl;
		std::cout << log;
		delete[] log;
	}
}

void			Shader::compile(void)
{
	_program = glCreateProgram();
	if (!_program)
		return ;
	for (unsigned int i = 0; i < _size; i++)
	{
		if (_shaders[i])
			glAttachShader(_program, _shaders[i]);
	}
	glLinkProgram(_program);
	// TEST DEBUG
	GLint	result;
	glGetProgramiv(_program, GL_LINK_STATUS, &result);
	if (result == 0)
	{
		int log_length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
		if (log_length)
		{
			char	*log = new char[log_length];
			glGetProgramInfoLog(_program, log_length, NULL, log);
			std::cout << log;
			delete[] log;
		}
	}
	// DELETE LAST
	for (unsigned int i = 0; i < _size; i++)
	{
		if (_shaders[i])
		{
			glDetachShader(_program, _shaders[i]);
			glDeleteShader(_shaders[i]);
			_shaders[i] = 0;
		}
	}
}

void			Shader::bind(void)
{
	glUseProgram(_program);
}

void			Shader::unbind(void)
{
	Shader::Unbind();
}

void			Shader::Unbind(void)
{
	glUseProgram(0);
}


void			Shader::uniform1i(std::string const &name, int i)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniform1i(id, i);
}

void			Shader::uniform1f(std::string const &name, float x)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniform1f(id, x);
}

void			Shader::uniform2f(std::string const &name, float x, float y)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniform2f(id, x, y);
}

void			Shader::uniform2f(std::string const &name, float *data)
{
	uniform2f(name, data[0], data[1]);
}

void			Shader::uniform2f(std::string const &name, Vec2f const &vec)
{
	uniform2f(name, vec.getX(), vec.getY());
}

void			Shader::uniform3f(std::string const &name, float x, float y, float z)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniform3f(id, x, y, z);
}

void			Shader::uniform3f(std::string const &name, Vec3f const &vec)
{
	uniform3f(name, vec.getX(), vec.getY(),vec.getY());
}

void			Shader::uniform3f(std::string const &name, float *data)
{
	uniform3f(name, data[0], data[1], data[2]);
}

void			Shader::uniform4f(std::string const &name, float x, float y, float z, float w)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniform4f(id, x, y, z, w);
}

void			Shader::uniform4f(std::string const &name, float *data)
{
	uniform4f(name, data[0], data[1], data[2], data[3]);
}

void			Shader::uniformMat(std::string const &name, Mat4 &mat)
{
	GLint id = glGetUniformLocation(_program, name.c_str());
	glUniformMatrix4fv(id, 1, GL_FALSE, &mat[0]);
}