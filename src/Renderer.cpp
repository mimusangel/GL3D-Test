#include "Renderer.hpp"

Renderer	&Renderer::GetInstance(void)
{
	static Renderer renderer;

	return (renderer);
}

Renderer::Renderer(void)
{

}

void		Renderer::unload(void)
{

}