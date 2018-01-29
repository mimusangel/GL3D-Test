#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "../Core/Mesh.hpp"

class Renderer {
private:
	Mesh			*_meshPoint;
	
	Renderer(void);
public:
	static Renderer	*GetInstance(void);
	void			unload(void);
	inline Mesh		*getMeshPoint(void) { return (_meshPoint); }
};

#endif