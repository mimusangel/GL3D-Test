#include "SceneGame.hpp"
#include "../Core/FileUtils.hpp"

SceneGame::SceneGame(void) :
	AWidget(),
	_menu(NULL),
	_pause(false)
{
	projection = Mat4::Perspective(M_TORADIANS(70.0f), 1280.0f / 720.0f, .001f, 1000.0f);
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
	_pause = false;

	/*
	** Terrain
	*/
	_terrainMesh = new Mesh(2);
	const float vertPos[] = {
		-1.0f, 0.0f, -1.0f,
		 1.0f, 0.0f, -1.0f,
		 1.0f, 0.0f,  1.0f,
		 1.0f, 0.0f,  1.0f,
		-1.0f, 0.0f,  1.0f,
		-1.0f, 0.0f, -1.0f,
	};
	_terrainMesh->add(0, GL_FLOAT, 3, (void *)vertPos, 6);
	const float vertColor[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};
	_terrainMesh->add(1, GL_FLOAT, 3, (void *)vertColor, 6);
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
		_menu->update(window);
	else
	{
		
	}
}

void	SceneGame::render(void)
{
	_terrainShader->bind();
	Mat4 model = Mat4::Translate(0, 0, 0) * Mat4::Rotate(0.0f, M_TORADIANS(45.0f), 0.0f);
	Mat4 view = Mat4::Translate(0, -0.5f, 1);
	// std::cout << model << std::endl;
	_terrainShader->uniformMat("model", model);
	_terrainShader->uniformMat("view", view);
	_terrainShader->uniformMat("projection", projection);

	_terrainMesh->render();

	_terrainShader->unbind();

	if (_menu != NULL && _pause)
		_menu->render();
}

void    SceneGame::keyRelease(GLFWwindow *window, int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		_pause = !_pause;
	}
}