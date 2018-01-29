#include "Loader.hpp"


Loader	&Loader::GetInstance(void)
{
	static Loader loader;

	return (loader);
}

Loader::Loader(void)
{
	_base = new Shader(3);
	_base->load(0, GL_VERTEX_SHADER, 
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"layout(location = 1) in vec4 vertexColor;"
		"uniform vec2 blockScale;"
		"out vec4 gColor;"
		"out vec2 gScale;"
		"void main()"
		"{"
		"	vec2 pos = (vertexPosition - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 0, 1);"
		"	gColor = vertexColor;"
		"	gScale = blockScale;"
		"}"
	);
	_base->load(1, GL_FRAGMENT_SHADER,
		"#version 330 core\n"
		"out vec4 color;"
		"in vec4 fColor;"
		"void main()"
		"{"
		"    color = fColor;"
		"}"
	);
	_base->load(2, GL_GEOMETRY_SHADER, 
		"#version 330 core\n"
		"layout(points) in;"
		"layout(triangle_strip, max_vertices = 4) out;"
		"in vec4 gColor[];"
		"in vec2 gScale[];"
		"out vec4 fColor;"
		"const vec2	PIXEL = vec2(1.0 / 640.0, 1.0 / -360.0);"
		"void main()"
		"{"
		"   fColor = gColor[0];"
		"	vec2 offsetPos = (PIXEL * 20.0) * gScale[0];"
		"	gl_Position = gl_in[0].gl_Position + vec4(-offsetPos.x, -offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(-offsetPos.x, offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(offsetPos.x, -offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(offsetPos.x, offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}"
	);
	_base->compile();
}

void	Loader::unload(void)
{
	delete _base;
}