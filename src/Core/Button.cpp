#include "Button.hpp"

Button::Button(std::string const &name, AWidget *parent, Vec2f const &pos, Vec2f const &size, IListenner *listenner) :
	_name(name),
	AWidget(parent, pos, size),
	_listenner(listenner)
{}

void	Button::load(void)
{

}

void	Button::unload(void)
{

}

void	Button::render(void)
{
	_shader->bind();
	_shader->uniform2f("btnPos", _pos);
	_shader->uniform2f("btnSize", _size);
	if (isMouseOver())
		_shader->uniform4f("btnColor", 1.0, 1.0, 0.5, 1.0);
	else
		_shader->uniform4f("btnColor", 1.0, 1.0, 1.0, 1.0);
	_mesh->render(GL_POINTS);
	Shader::Unbind();
}

Button	&Button::setListenner(IListenner *listenner)
{
	_listenner = listenner;
	return (*this);
}

void	Button::mouseClick(GLFWwindow *window, double x, double y, int button)
{
	if (_listenner == NULL)
		return ;
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		_listenner->action(window, this);
}


/* ********** */
/* * STATIC * */
/* ********** */

Mesh	*Button::_mesh = NULL;
Shader 	*Button::_shader = NULL;

void	Button::Load(void)
{
	_mesh = new Mesh(1);
	const float vertPos[] = {
		0.0f, 0.0f,
	};
	_mesh->add(0, GL_FLOAT, 2, (void *)vertPos, 1);
	_shader = new Shader(3);
	_shader->load(0, GL_VERTEX_SHADER, 
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"uniform vec2 btnPos;"
		"uniform vec2 btnSize;"
		"uniform vec4 btnColor;"
		"out vec2 gSize;"
		"out vec4 gColor;"
		"void main()"
		"{"
		"	vec2 pos = ((vertexPosition + btnPos) - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 0, 1);"
		"	gSize = btnSize;"
		"	gColor = btnColor;"
		"}"
	);
	_shader->load(1, GL_FRAGMENT_SHADER,
		"#version 330 core\n"
		"out vec4 color;"
		"in vec4 fColor;"
		"void main()"
		"{"
		"    color = fColor;"
		"}"
	);
	_shader->load(2, GL_GEOMETRY_SHADER, 
		"#version 330 core\n"
		"layout(points) in;"
		"layout(triangle_strip, max_vertices = 4) out;"
		"in vec2 gSize[];"
		"in vec4 gColor[];"
		"out vec4 fColor;"
		"const vec2	PIXEL = vec2(1.0 / 640.0, 1.0 / -360.0);"
		"void main()"
		"{"
		"	fColor = gColor[0];"
		"	vec2 size = PIXEL * gSize[0];"
		"	gl_Position = gl_in[0].gl_Position;"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(0.0, size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(size.x, 0.0, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(size.x, size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}"
	);
	_shader->compile();

}

void	Button::UnLoad(void)
{
	delete _mesh;
	_mesh = NULL;
	delete _shader;
	_shader = NULL;
}
