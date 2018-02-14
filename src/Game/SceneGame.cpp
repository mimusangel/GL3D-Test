#include "SceneGame.hpp"
#include "../Core/FileUtils.hpp"

SceneGame::SceneGame(void) :
	AWidget(),
	_menu(NULL),
	_pause(false),
	_camera(Vec3f(-1, 0.5f, -1))
{
	_projection = Mat4::Perspective(M_TORADIANS(70.0f), 1280.0f / 720.0f, .001f, 1000.0f);
	_terrainShader = NULL;
	_terrainMesh = NULL;
}

SceneGame::~SceneGame(void)
{}

void	SceneGame::load(void)
{
	_menu = new SceneGameMenu(this, Vec2f(640, 360));
	_menu->load();
	glClearColor(0, 0, 0, 1.0);
	setPause(false);

	/*
	** Terrain
	*/

	// Vec3f v0(-1.0f, 0.0f, -1.0f);
	// Vec3f v1(1.0f, 0.0f, -1.0f);
	// Vec3f v2(1.0f, 0.0f,  1.0f);
	// Vec3f n0 = (v2 - v0).cross(v1 - v0).normalize();
	// std::cout << n0 << std::endl;

	_terrainMesh = new Mesh(2);
	// const float vertPos[] = {
	// 	-1.0f, 0.0f, -1.0f,
	// 	 1.0f, 0.0f, -1.0f,
	// 	 1.0f, 0.0f,  1.0f,
	// 	 1.0f, 0.0f,  1.0f,
	// 	-1.0f, 0.0f,  1.0f,
	// 	-1.0f, 0.0f, -1.0f,

	// 	-1.0f, 0.0f,  1.0f,
	// 	1.0f, 0.0f,  1.0f,
	// 	-1.0f, 2.0f,  1.0f,
	// };
	const Vec3f vertPos[] = {
		Vec3f(-1.0f, 0.0f, -1.0f),
		Vec3f(1.0f, 0.0f, -1.0f),
		Vec3f(1.0f, 0.0f,  1.0f),
		Vec3f(1.0f, 0.0f,  1.0f),
		Vec3f(-1.0f, 0.0f,  1.0f),
		Vec3f(-1.0f, 0.0f, -1.0f),
		Vec3f(-1.0f, 0.0f,  1.0f),
		Vec3f(1.0f, 0.0f,  1.0f),
		Vec3f(-1.0f, 2.0f,  1.0f),
	};
	_terrainMesh->add(0, GL_FLOAT, 3, (void *)vertPos, 9);
	const float vertColor[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
	};
	_terrainMesh->add(1, GL_FLOAT, 3, (void *)vertColor, 9);
	_terrainShader = new Shader(2);
	_terrainShader->load(0, GL_VERTEX_SHADER, FileUtils::LoadFile("res/shaders/terrain.vs").c_str());
	_terrainShader->load(1, GL_FRAGMENT_SHADER, FileUtils::LoadFile("res/shaders/terrain.fs").c_str());
	_terrainShader->compile();
}

void	SceneGame::unload(void)
{
	if (_menu != NULL)
	{
		_menu->unload();
		delete _menu;
		_menu = NULL;
	}
	if (_terrainShader == NULL)
	{
		delete _terrainShader;
		_terrainShader = NULL;
	}
	if (_terrainMesh == NULL)
	{
		delete _terrainMesh;
		_terrainMesh = NULL;
	}
}

void	SceneGame::fixedUpdate(GLFWwindow *window)
{
	if (!_pause)
	{

	}
}

void 	SceneGame::update(GLFWwindow *window)
{
	if (_menu != NULL && _pause)
	{

		_menu->update(window);
		
	}
	else
	{
		_camera.update();
	}
}

void	SceneGame::render(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	_terrainShader->bind();

	Mat4 model = Mat4::Translate(0, 0, 0);
	Mat4 view = _camera.getViewMatrix();
	
	_terrainShader->uniformMat("model", model);
	_terrainShader->uniformMat("view", view);
	_terrainShader->uniformMat("projection", _projection);

	_terrainMesh->render();

	_terrainShader->unbind();

	if (_menu != NULL && _pause)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		_menu->render();
	}
}

void    SceneGame::keyRelease(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		_pause = !_pause;
		_camera.setGrab(window, false);
	}
}

void    SceneGame::keyPress(GLFWwindow *window, int key)
{
	
	if (key == GLFW_KEY_W)
	{
		Vec3f dir = _camera.getForward();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_S)
	{
		Vec3f dir = _camera.getForward().negate();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_D)
	{
		Vec3f dir = _camera.getSide();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_A)
	{
		Vec3f dir = _camera.getSide().negate();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_SPACE)
	{
		Vec3f dir(0, 1, 0);
		_camera.move(dir);
	}
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		Vec3f dir(0, -1, 0);
		_camera.move(dir);
	}
}

void    SceneGame::keyRepeat(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_W)
	{
		Vec3f dir = _camera.getForward();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_S)
	{
		Vec3f dir = _camera.getForward().negate();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_D)
	{
		Vec3f dir = _camera.getSide();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_A)
	{
		Vec3f dir = _camera.getSide().negate();
		_camera.move(dir);
	}
	if (key == GLFW_KEY_SPACE)
	{
		Vec3f dir(0, 1, 0);
		_camera.move(dir);
	}
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		Vec3f dir(0, -1, 0);
		_camera.move(dir);
	}
}

void    SceneGame::mouseButtonPress(GLFWwindow *window, int button)
{
	if (!_pause && button == GLFW_MOUSE_BUTTON_LEFT)
	{
		_camera.setGrab(window, true);
	}
}

void	SceneGame::mouseMove(GLFWwindow *window, float x, float y)
{
	_camera.setMousePos(x, y);
}

void	SceneGame::setPause(bool pause)
{
	_pause = pause;
}