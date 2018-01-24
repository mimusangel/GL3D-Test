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
	Shader  *test = new Shader(3);
	const char *testVertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec2 vertexPosition;"
		"layout(location = 1) in vec4 vertexColor;"
		"out vec4 gColor;"
		"void main()"
		"{"
		"	vec2 pos = (vertexPosition - vec2(640, 360)) / vec2(640, -360);"
		"   gl_Position = vec4(pos, 0, 1);"
		"	gColor = vertexColor;"
		"}"
	;
	const char *testFragmentShader =
		"#version 330 core\n"
		"out vec4 color;"
		"in vec4 oColor;"
		"void main()"
		"{"
		"    color = oColor;"
		"}"
	;
	const char *testGeomShader =
		"#version 330 core\n"
		"layout(points) in;"
		"layout(triangle_strip, max_vertices = 4) out;"
		"in vec4 gColor[];"
		"out vec4 oColor;"
		"const vec2	PIXEL = vec2(1.0 / 640.0, 1.0 / -360.0);"
		"void main()"
		"{"
		"   oColor = gColor[0];"
		"	vec2 offsetPos = PIXEL * 40.0;"
		"	gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(0.0, offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(offsetPos.x, 0.0, 0.0, 0.0);"
		"	EmitVertex();"
		"	gl_Position = gl_in[0].gl_Position + vec4(offsetPos.x, offsetPos.y, 0.0, 0.0);"
		"	EmitVertex();"
		"	EndPrimitive();"
		"}"
	;
	test->load(0, GL_VERTEX_SHADER, testVertexShader);
	test->load(1, GL_FRAGMENT_SHADER, testFragmentShader);
	test->load(2, GL_GEOMETRY_SHADER, testGeomShader);
	test->compile();
	Mesh    *mesh = new Mesh(2);
	const float vertPos[] = {
		0.0f,   0.0f,
		640.0f, 360.0f,
	};
	const float vertColor[] = {
		1.0f,   1.0f,   1.0f,   1.0f,
		0.1f,   0.1f,   0.1f,   1.0f,
	};
	mesh->add(0, GL_FLOAT, 2, (void *)vertPos, 2);
	mesh->add(1, GL_FLOAT, 4, (void *)vertColor, 2);

	const double	tickPerSec = 1.0 / 60.0;
	double			tickTimer = 0.0;
	int				tickCount = 0;
	int				frameCount = 0;
	double			timer = 0.0;
	glEnable(GL_CULL_FACE);
	glClearColor(0.4, 0.4, 0.4, 1.0);
	while (!glfwWindowShouldClose(_window))
	{
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		Timer::Update();

		tickTimer += Timer::GetDelta();
		while (tickTimer >= tickPerSec)
		{
			// Static Update
			
			tickCount++;
			tickTimer -= tickPerSec;
		}
		// Dynamic Update
		
		// Render
		test->bind();
		mesh->render(GL_POINTS);
		Shader::Unbind();
		frameCount++;

		timer += Timer::GetDelta();
		if (timer >= 1.0)
		{
			_ups = tickCount;
			_fps = frameCount;
			tickCount = 0;
			frameCount = 0;
			timer -= 1.0;
		}

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