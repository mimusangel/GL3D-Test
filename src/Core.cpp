#include "Core.hpp"
#include "Timer.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"

Core::Core(void) :
	_window(NULL),
	_width(1280),
	_height(720)
{
	_window = glfwCreateWindow(_width, _height, "Color Running", NULL, NULL);
}

Core::~Core(void)
{
	if (_window != NULL)
	{
		glfwDestroyWindow(_window);
		_window = NULL;
	}
}

void                    Core::loop(void)
{
	Shader  *test = new Shader(2);
	const char *testVertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"void main()"
		"{"
		"	vec2 pos = (vertexPosition - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 1, 1);"
		"}"
	;
	const char *testFragmentShader =
		"#version 330 core\n"
		"out vec4 color;"
		"void main()"
		"{"
		"    color = vec4(1.0);"
		"}"
	;
	test->load(0, GL_VERTEX_SHADER, testVertexShader);
	test->load(1, GL_FRAGMENT_SHADER, testFragmentShader);
	test->compile();
	Mesh    *mesh = new Mesh(1);
	const float vertPos[] = {
		0.0f,   0.0f,
		0.0f,   20.0f,
		20.0f,  0.0f,
		640.0f, 360.0f,
		640.0f, 380.0f,
		660.0f, 360.0f,
	};
	mesh->add(0, GL_FLOAT, 2, (void *)vertPos, 6);
	glEnable(GL_CULL_FACE);
	while (!glfwWindowShouldClose(_window))
	{
		Timer::Update();

		test->bind();
		mesh->render();
		Shader::Unbind();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	delete mesh;
	delete test;
}

void                    Core::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}