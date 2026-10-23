#pragma once
#include <raylib.h>
#include <raymath.h>
#include "GameState.h"

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
	BoundingBox getHitbox() { return m_hitbox; }
	BoundingBox getNextHitbox();
	Vector3 getPosition() { return m_position; }
	Vector3 getDirection() { return Vector3Normalize(m_velocity); }
	void toggleHitbox() { m_drawHitbox = !m_drawHitbox; }
	void swapDimension(GameState t_state, Vector3 t_activeAxis);
	void swapAxis(Vector3 t_activeAxis);

protected:
	Vector3 m_position;
	Vector3 m_velocity;
	BoundingBox m_hitbox;
	Vector3 m_axisBuffer;

	Color m_colour = DARKBLUE;

	float m_width = 2.0f;
	float m_length = 2.0f;
	float m_height = 2.0f;

	float m_speed = 0.5f;
	const float MAX_SPEED = 2.0f;

	bool m_drawHitbox = false;

	GameState m_state;
};

