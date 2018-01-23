#ifndef MESH_HPP
#define MESH_HPP

#include "global.hpp"

class Mesh {
private:
	unsigned int	_nbVBO;
	GLuint			_vao;
	GLuint			*_vbo;
	unsigned int	_size;
public:
	Mesh(unsigned int nbVBO);
	~Mesh();
	void			add(unsigned int vboIndex, GLenum type, unsigned int width, void *data, unsigned int dataSize, GLenum usage = GL_STATIC_DRAW);
	void			render(GLenum mode = GL_TRIANGLES);
};

#endif