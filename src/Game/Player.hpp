#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Core/global.hpp"
#include "../Core/Shader/Shader.hpp"
#include "../Core/Math/Vec2.hpp"
#include "../Core/Math/Vec3.hpp"

class Player {
private:
	Vec2f	_pos;
	Vec2f	_velocity;
	bool	_ground;
	Shader	*_shader;
public:
	Player(Vec2f const &pos = Vec2f());
	~Player();

	void	render(void);
	void	update(GLFWwindow *window);

	inline bool		isGround(void) { return (_ground); }
	inline void		setGround(bool ground) { _ground = ground; }
};

#endif