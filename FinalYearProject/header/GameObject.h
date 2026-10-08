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
	void updateHitbox();
	void applyForce(Vector3 t_force);
	BoundingBox getHitbox() { return m_hitbox3D; }
	BoundingBox getNextHitbox(int t_x, int t_y, int t_z);
	Vector3 getPosition() { return m_position3D; }
	Vector3 getDirection() { return Vector3Normalize(m_velocity3D); }
	void stopVelocity(int t_x, int t_y, int t_z);
	void toggleHitbox() { m_drawHitbox = !m_drawHitbox; }

protected:
	Vector3 m_position3D;
	Vector3 m_velocity3D;
	BoundingBox m_hitbox3D;

	Vector2 m_position2D;
	Vector2 m_velocity2D;
	Rectangle m_hitbox2D;
	Color m_colour = DARKBLUE;

	float m_width = 2.0f;
	float m_length = 2.0f;
	float m_height = 2.0f;

	float m_speed = 0.5f;
	const float MAX_SPEED = 2.0f;

	bool m_drawHitbox = false;
};

