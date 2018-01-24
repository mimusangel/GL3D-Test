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

void		Shader::load(unsigned int shaderIndex, GLenum shaderType, const char *script)
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

void		Shader::compile(void)
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

void		Shader::bind(void)
{
	glUseProgram(_program);
}

void		Shader::unbind(void)
{
	Shader::Unbind();
}

void		Shader::Unbind(void)
{
	glUseProgram(0);
}
