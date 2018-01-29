#ifndef LOADER_HPP
#define LOADER_HPP

#include "../Core/Shader.hpp"

class Loader {
private:
	Shader	*_base;

	Loader(void);

public:
	static Loader	&GetInstance(void);
	inline Shader	*getShaderBase(void) { return (_base); }
	void			unload(void);
	
};

#endif