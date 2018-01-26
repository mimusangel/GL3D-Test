#include "Core.hpp"
#include "Timer.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Loader.hpp"
#include "Renderer.hpp"

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
	Loader			loader = Loader::GetInstance();
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
		loader.getShaderBase()->bind();
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
	loader.unloader();
}

void                    Core::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}