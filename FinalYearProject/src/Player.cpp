#include "../header/Player.h"
#include <iostream>

void Player::update(float t_levelSize)
{
	if (Vector3Distance((m_position + m_velocity), { 0.0f, 0.0f, 0.0f }) < t_levelSize)
	{
		move();
	}
}

void Player::repulsiveForce(RayCollision t_rc)
{
	Vector3 tempPosition = ((t_rc.normal * (m_width/2.0f)) + t_rc.point);
	m_velocity = {0.0f, 0.0f, 0.0f};

	// If snapping to ground
	if (tempPosition.y != m_position.y && m_yBuffer == 0.0f)
	{
		m_yBuffer = m_position.y;
	}

	if (Vector3Length(tempPosition) < 100)
	{
		m_position = tempPosition;
	}
	updateHitbox();
}

void Player::addGroundVelocity(Vector3 t_vel)
{
	m_position += t_vel;
}
