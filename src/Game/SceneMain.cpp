#include "SceneMain.hpp"
#include "Loader.hpp"
#include "Renderer.hpp"

SceneMain::SceneMain(void) :
	AWidget(),
	_mesh(NULL)
{}
SceneMain::~SceneMain(void)
{
	while (!_list.empty())
	{
		delete _list.back();
		_list.pop_back();
	}
}

void	SceneMain::load(void)
{
	_mesh = new Mesh(2);
	const float vertPos[] = {
		640.0f, 360.0f,
	};
	const float vertColor[] = {
		0.1f,   0.4f,   0.1f,   1.0f,
	};
	_mesh->add(0, GL_FLOAT, 2, (void *)vertPos, 1);
	_mesh->add(1, GL_FLOAT, 4, (void *)vertColor, 1);
}

void	SceneMain::unload(void)
{
	if (_mesh != NULL)
		delete _mesh;
}

void 	SceneMain::update(GLFWwindow *window)
{

}

void	SceneMain::render(void)
{
	static Loader loader = Loader::GetInstance();
	if (_mesh == NULL)
		return ;
	glPointSize(3.0f);
	loader.getShaderBase()->bind();
	loader.getShaderBase()->uniform2f("blockScale", 2.0f, 1.0f);
	_mesh->render(GL_POINTS);
	Shader::Unbind();
	glPointSize(1.0f);
}
