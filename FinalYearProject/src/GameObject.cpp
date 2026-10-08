#include "../header/GameObject.h"

GameObject::GameObject() : m_position3D({0.0f, 2.0f, 0.0f}), m_velocity3D({0.0f, 0.0f, 0.0f})
{
}

void GameObject::setHitbox()
{
	updateHitbox();
}

void GameObject::update()
{
	move();
}

void GameObject::draw()
{
	DrawCube(m_position3D, m_width, m_height, m_length, m_colour);
	
	if (m_drawHitbox)
	{
		DrawBoundingBox(m_hitbox3D, RED);
	}
}

void GameObject::move()
{
	m_position3D += m_velocity3D;
	updateHitbox();
	m_velocity3D = { 0.0f, 0.0f, 0.0f };
}

void GameObject::updateHitbox()
{
	m_hitbox3D.min = { m_position3D.x - (m_width / 2.0f), m_position3D.y - (m_height / 2.0f), m_position3D.z - (m_length / 2.0f) };
	m_hitbox3D.max = { m_position3D.x + (m_width / 2.0f), m_position3D.y + (m_height / 2.0f), m_position3D.z + (m_length / 2.0f) };
}

void GameObject::applyForce(Vector3 t_force)
{
	m_velocity3D += t_force * m_speed;

	m_velocity3D = Vector3ClampValue(m_velocity3D, 0.0f, MAX_SPEED);
}

BoundingBox GameObject::getNextHitbox(int t_x, int t_y, int t_z)
{
	BoundingBox tempBox = m_hitbox3D;
	Vector3 tempVelocity = m_velocity3D * Vector3{ (float)t_x, (float)t_y, (float)t_z };

	tempBox.min += tempVelocity * m_speed;
	tempBox.max += tempVelocity * m_speed;
	return tempBox;
}

void GameObject::stopVelocity(int t_x, int t_y, int t_z)
{
	m_velocity3D.x *= t_x;
	m_velocity3D.y *= t_y;
	m_velocity3D.z *= t_z;
}
