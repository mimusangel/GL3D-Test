#include "Renderer.hpp"

Renderer	*Renderer::GetInstance(void)
{
	static Renderer *renderer = new Renderer();

	return (renderer);
}

Renderer::Renderer(void)
{
	_meshPoint = new Mesh(1);
	const float vertPos[] = {
		0.0f, 0.0f,
	};
	_meshPoint->add(0, GL_FLOAT, 2, (void *)vertPos, 1);
}

void		Renderer::unload(void)
{
	delete _meshPoint;
}