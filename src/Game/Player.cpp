#include "Player.hpp"
#include "Renderer.hpp"
#include "../Core/Timer.hpp"

Player::Player(Vec2f const &pos) :
	_pos(pos),
	_velocity(0),
	_ground(false),
	_shader(NULL)
{
	_shader = new Shader(3);
	_shader->load(0, GL_VERTEX_SHADER, 
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"uniform vec2 playerPos;"
		"void main()"
		"{"
		"	vec2 pos = (playerPos - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 0, 1);"
		"}"
	);
	_shader->load(1, GL_FRAGMENT_SHADER,
		"#version 330 core\n"
		"out vec4 color;"
		"void main()"
		"{"
		"    color = vec4(0.0, 0.0, 0.6, 1);"
		"}"
	);
	_shader->load(2, GL_GEOMETRY_SHADER, 
		"#version 330 core\n"
		"layout(points) in;"
		"layout(triangle_strip, max_vertices = 4) out;"
		"const vec2	PIXEL = vec2(1.0 / 640.0, 1.0 / -360.0);"
		"void main()"
		"{"
		"	vec2 size = PIXEL * 20.0;"
		"	gl_Position = gl_in[0].gl_Position + vec4(-size.x, -size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(-size.x, size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(size.x, -size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(size.x, size.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}"
	);
	_shader->compile();
}

Player::~Player()
{
	if (_shader != NULL)
		delete _shader;
}

void	Player::render(void)
{
	static Renderer *renderer = Renderer::GetInstance();

	_shader->bind();
	_shader->uniform2f("playerPos", _pos);
	renderer->getMeshPoint()->render(GL_POINTS);
	Shader::Unbind();
}

void	Player::update(GLFWwindow *window)
{
	Vec2f nDir;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		nDir.setX(nDir.getX() + 1);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		nDir.setX(nDir.getX() - 1);
	}
	if (_ground && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		nDir.setY(-150.0f);
		_ground = false;
	}
	_velocity += Vec2f(0.0, 1.0) * 10.0f;
	_velocity += nDir * 10.0f;
	_pos += _velocity * Timer::GetDelta();
	if (_ground)
		_velocity.setX(_velocity.getX() * 0.99f);
	else
		_velocity.setX(_velocity.getX() * 0.999f);
	if (_velocity.getX() > -0.001f && _velocity.getX() < 0.001f)
		_velocity.setX(0.0);
	

	if (_pos.getY() >= 700)
	{
		_pos.setY(700);
		_ground = true;
		_velocity.setY(0);
	}
}
