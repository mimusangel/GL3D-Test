#include "SceneGameMenu.hpp"
#include "SceneGame.hpp"
#include "SceneMain.hpp"
#include "../Core/UI/Button.hpp"
#include "../Core/Core.hpp"
#include "Renderer.hpp"

SceneGameMenu::SceneGameMenu(AWidget *parent, Vec2f pos) :
	AWidget(parent, pos)
{
	_shader = NULL;
}

SceneGameMenu::~SceneGameMenu(void)
{}

void	SceneGameMenu::load(void)
{
	_shader = new Shader(3);
	_shader->load(0, GL_VERTEX_SHADER, 
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"uniform vec2 panelCenter;"
		"out vec2 gSize;"
		"void main()"
		"{"
		"	vec2 pos = (panelCenter - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 0, 1);"
		"	gSize = vec2(135, 240);"
		"}"
	);
	_shader->load(1, GL_FRAGMENT_SHADER,
		"#version 330 core\n"
		"out vec4 color;"
		"void main()"
		"{"
		"    color = vec4(0.6, 0.6, 0.6, 1);"
		"}"
	);
	_shader->load(2, GL_GEOMETRY_SHADER, 
		"#version 330 core\n"
		"layout(points) in;"
		"layout(triangle_strip, max_vertices = 4) out;"
		"in vec2 gSize[];"
		"const vec2	PIXEL = vec2(1.0 / 640.0, 1.0 / -360.0);"
		"void main()"
		"{"
		"	vec2 size = PIXEL * gSize[0];"
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
	_list.push_back(new Button("X", this, Vec2f(104, -235), Vec2f(26, 26), this));
	_list.push_back(new Button("Back", this, Vec2f(-130, 205), Vec2f(260, 30), this));
}

void	SceneGameMenu::unload(void)
{
	while (!_list.empty())
	{
		delete _list.back();
		_list.pop_back();
	}
	if (_shader != NULL)
		delete _shader;
}

void 	SceneGameMenu::update(GLFWwindow *window)
{
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->update(window);
		++it;
	}
}

void	SceneGameMenu::render(void)
{
	static Renderer *renderer = Renderer::GetInstance();
	// BACKGROUND
	_shader->bind();
	_shader->uniform2f("panelCenter", getPosition());
	renderer->getMeshPoint()->render(GL_POINTS);
	Shader::Unbind();
	// WIDGET
	std::vector<AWidget *>::iterator it = _list.begin();
	while (it != _list.end())
	{
		(*it)->render();
		++it;
	}
}

void	SceneGameMenu::action(GLFWwindow *window, AWidget *src)
{
	Core *game = (Core *)glfwGetWindowUserPointer(window);
	if (game == NULL)
		return ;
	if (src == _list[0])
	{
		try {
			SceneGame *sGame = dynamic_cast<SceneGame *>(_parent);
			sGame->setPause(false);
		} catch (const std::exception& e) {}
		return ;
	}
	if (src == _list[1])
	{
		game->loadScene(new SceneMain());
		return ;
	}
}
