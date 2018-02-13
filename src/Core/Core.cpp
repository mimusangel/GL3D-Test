#include "Core.hpp"
#include "Timer.hpp"

#include "UI/Button.hpp"

Core::Core(void) :
	_window(NULL),
	_width(1280),
	_height(720)
{
	_window = glfwCreateWindow(_width, _height, "Color Running", NULL, NULL);
	_scene = NULL;
	_lastScene = NULL;
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
	const double	tickPerSec = 1.0 / 60.0;
	double			tickTimer = 0.0;
	int				tickCount = 0;
	int				frameCount = 0;
	double			timer = 0.0;
	
	while (!glfwWindowShouldClose(_window) && running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Timer::Update();

		tickTimer += Timer::GetDelta();
		if (_lastScene != NULL)
		{
			_lastScene->unload();
			delete _lastScene;
			_lastScene = NULL;
		}
		while (tickTimer >= tickPerSec)
		{
			if (_scene != NULL)
				_scene->fixedUpdate(_window);
			tickCount++;
			tickTimer -= tickPerSec;
		}
		if (_scene != NULL)
		{
			_scene->update(_window);
			_scene->render();
		}
		frameCount++;
		timer += Timer::GetDelta();
		if (timer >= 1.0)
		{
			// std::cout << "FPS: " << frameCount << " / UPS: " << tickCount << std::endl;
			_ups = tickCount;
			_fps = frameCount;
			tickCount = 0;
			frameCount = 0;
			timer -= 1.0;
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void                    Core::viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void                    Core::load(void)
{
	Button::Load();
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	running = true;
}

void                    Core::unload(void)
{

	if (_scene != NULL)
	{
		_scene->unload();
		delete _scene;
		_scene = NULL;
	}
	Button::UnLoad();
}


void                    Core::loadScene(AWidget *scene)
{
	if (_scene != NULL)
	{
		_lastScene = _scene;
		_scene = NULL;
	}
	_scene = scene;
	if (_scene != NULL)
		_scene->load();
}


void                    Core::keyPress(int key)
{
	if (_scene != NULL)
		_scene->keyPress(_window, key);
}

void                    Core::keyRelease(int key)
{
	if (_scene != NULL)
		_scene->keyRelease(_window, key);
}

void                    Core::keyRepeat(int key)
{
	if (_scene != NULL)
		_scene->keyRepeat(_window, key);
}
