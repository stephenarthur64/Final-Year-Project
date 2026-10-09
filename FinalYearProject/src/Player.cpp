#include "../header/Player.h"
#include <iostream>

void Player::repulsiveForce(RayCollision t_rc)
{
	Vector3 tempPosition = ((t_rc.normal * (m_width/2.0f)) + t_rc.point);
	//std::cout << "velocity" << m_velocity.x << " " << m_velocity.y << " " << m_velocity.z << "\n";
	std::cout << "position" << tempPosition.x << " " << tempPosition.y << " " << tempPosition.z << "\n";
	std::cout << "normal" << t_rc.normal.x << " " << t_rc.normal.y << " " << t_rc.normal.z << "\n";
	m_velocity = {0.0f, 0.0f, 0.0f};

	if (Vector3Length(tempPosition) < 100)
	{
		m_position = tempPosition;
	}
	updateHitbox();

}