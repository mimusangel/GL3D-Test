#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Core/global.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Vec2f.hpp"

class Player {
private:
	Vec2f	_pos;
	Vec2f	_velocity;
	Shader	*_shader;
public:
	Player(Vec2f const &pos = Vec2f());
	~Player();

	void	render(void);
	void	update(GLFWwindow *window);
};

#endif