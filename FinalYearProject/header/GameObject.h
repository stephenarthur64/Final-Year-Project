#pragma once
#include <raylib.h>
#include <raymath.h>
#include "GameState.h"
#include <iostream>

class GameObject
{
public:
	GameObject();
	void setHitbox();
	virtual void update();
	void draw();
	void move();
	void updateHitbox();
	void applyForce(Vector3 t_force);
	BoundingBox getHitbox() { return m_hitbox; }
	BoundingBox getNextHitbox();
	Vector3 getPosition() { return m_position; }
	Vector3 getPosition3D() { return m_position + m_axisBuffer; }
	Vector3 getDirection() { return Vector3Normalize(m_velocity); }
	Vector3 getVelocity() { return m_velocity; }
	void toggleHitbox() { m_drawHitbox = !m_drawHitbox; }
	virtual void swapDimension(GameState t_state, Vector3 t_activeAxis, Vector3 t_camPos);
	virtual void swapAxis(Vector3 t_activeAxis, Vector3 t_camPos);

protected:
	Vector3 m_position;
	Vector3 m_velocity;
	BoundingBox m_hitbox;
	Vector3 m_axisBuffer;

	Color m_colour = DARKBLUE;

	float m_width = 2.0f;
	float m_length = 2.0f;
	float m_height = 2.0f;

	float m_defaultWidth = 2.0f;
	float m_defaultLength = 2.0f;
	float m_defaultHeight = 2.0f;

	float m_sizeMod = 1.0f;

	float m_speed = 0.5f;
	const float MAX_SPEED = 2.0f;

	bool m_drawHitbox = false;

	GameState m_state;

	const float DISTANCE_SCALE_FACTOR = 1.0f;
};

