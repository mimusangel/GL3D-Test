#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:
	Renderer(void);
public:
	static Renderer	&GetInstance(void);
	void			unload(void);
};

#endif