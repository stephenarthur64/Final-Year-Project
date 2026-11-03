#include "../header/MovingWall.h"

MovingWall::MovingWall(Vector3 t_pos, float t_l, float t_w, float t_h, Vector3 t_upLimit, Vector3 t_lowLimit) : Wall(t_pos, t_l, t_w, t_h),
		m_upperLimit(t_upLimit), m_lowerLimit(t_lowLimit)
{
	m_speed = 0.1f;
}

void MovingWall::update()
{
	if (Vector3Length(m_direction) == 0.0f)
	{
		m_position = m_upperLimit;
		m_target = &m_lowerLimit;
		m_direction = *m_target - m_position;
		m_direction = Vector3Normalize(m_direction);
	}

	if (m_position.x >= m_upperLimit.x && m_position.y >= m_upperLimit.y && m_position.z >= m_upperLimit.z && m_target != &m_lowerLimit)
	{
		m_target = &m_lowerLimit;
		m_direction = *m_target - m_position;
		m_direction = Vector3Normalize(m_direction);
	}
	else if (m_position.x <= m_lowerLimit.x && m_position.y <= m_lowerLimit.y && m_position.z <= m_lowerLimit.z && m_target != &m_upperLimit)
	{
		m_target = &m_upperLimit;
		m_direction = *m_target - m_position;
		m_direction = Vector3Normalize(m_direction);
	}

	applyForce(m_direction);
	move();
}
