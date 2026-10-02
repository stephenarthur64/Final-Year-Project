#include "GameObject.h"

GameObject::GameObject() : m_position({0.0f, 2.0f, 0.0f}), m_velocity({0.0f, 0.0f, 0.0f}), m_speed(0.5f), MAX_SPEED(2.0f), m_length(2.0f), m_width(2.0f), m_height(2.0f), m_drawHitbox(false),
							m_colour(DARKBLUE)
{
}

void GameObject::setHitbox()
{
	m_hitbox.min = { m_position.x - (m_width / 2.0f), m_position.y - (m_height / 2.0f), m_position.z - (m_length / 2.0f) };
	m_hitbox.max = { m_position.x + (m_width / 2.0f), m_position.y + (m_height / 2.0f), m_position.z + (m_length / 2.0f) };
}

void GameObject::update()
{
	move();
}

void GameObject::draw()
{
	DrawCube(m_position, m_width, m_height, m_length, m_colour);
	
	if (m_drawHitbox)
	{
		DrawBoundingBox(m_hitbox, RED);
	}
}

void GameObject::move()
{
	m_position += m_velocity;
	m_hitbox.min += m_velocity;
	m_hitbox.max += m_velocity;
	m_velocity = { 0.0f, 0.0f, 0.0f };
}

void GameObject::applyForce(Vector3 t_force)
{
	m_velocity += t_force * m_speed;

	m_velocity = Vector3ClampValue(m_velocity, 0.0f, MAX_SPEED);
}

BoundingBox GameObject::getNextHitbox(int t_x, int t_y, int t_z)
{
	BoundingBox tempBox = m_hitbox;
	Vector3 tempVelocity = m_velocity * Vector3{ (float)t_x, (float)t_y, (float)t_z };

	tempBox.min += tempVelocity * m_speed;
	tempBox.max += tempVelocity * m_speed;
	return tempBox;
}

void GameObject::stopVelocity(int t_x, int t_y, int t_z)
{
	m_velocity.x *= t_x;
	m_velocity.y *= t_y;
	m_velocity.z *= t_z;
}
