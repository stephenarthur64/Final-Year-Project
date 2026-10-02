#pragma once
#include <raylib.h>
#include <raymath.h>

class GameObject
{
public:
	GameObject();
	void setHitbox();
	void update();
	void draw();
	void move();
	void applyForce(Vector3 t_force);
	BoundingBox getHitbox() { return m_hitbox; }
	BoundingBox getNextHitbox(int t_x, int t_y, int t_z);
	Vector3 getPosition() { return m_position; }
	void stopVelocity(int t_x, int t_y, int t_z);
	void toggleHitbox() { m_drawHitbox = !m_drawHitbox; }

protected:
	Vector3 m_position;
	Vector3 m_velocity;
	BoundingBox m_hitbox;
	Color m_colour;

	float m_width;
	float m_length;
	float m_height;

	float m_speed;
	const float MAX_SPEED;

	bool m_drawHitbox;
};

