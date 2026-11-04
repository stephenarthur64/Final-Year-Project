#include "../header/MovingWall.h"

MovingWall::MovingWall(Vector3 t_pos, float t_l, float t_w, float t_h, Vector3 t_upLimit, Vector3 t_lowLimit) : Wall(t_pos, t_l, t_w, t_h),
		m_upperLimit(t_upLimit), m_lowerLimit(t_lowLimit), m_direction({0.0f, 0.0f, 0.0f}), m_lowerAxisBuffer({0.0f, 0.0f, 0.0f}), m_upperAxisBuffer({0.0f, 0.0f, 0.0f})
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

void MovingWall::swapDimension(GameState t_state, Vector3 t_activeAxis, Vector3 t_camPos)
{
	m_state = t_state;

	switch (m_state)
	{
	case GameState::TWO_DIMENSION:
		swapAxis(t_activeAxis, t_camPos);
		break;
	case GameState::THREE_DIMENSION:
		m_position += m_axisBuffer;
		m_upperLimit += m_upperAxisBuffer;
		m_lowerLimit += m_lowerAxisBuffer;
		m_axisBuffer = { 0.0f, 0.0f, 0.0f };
		m_upperAxisBuffer = {0.0f, 0.0f, 0.0f};
		m_lowerAxisBuffer = {0.0f, 0.0f, 0.0f};
		updateHitbox();
		break;
	default:
		break;
	}

}

void MovingWall::swapAxis(Vector3 t_activeAxis, Vector3 t_camPos)
{
	m_position += m_axisBuffer;
	m_upperLimit += m_upperAxisBuffer;
	m_lowerLimit += m_lowerAxisBuffer;

	if (t_activeAxis.x == 0.0f) 
	{ 
		m_axisBuffer = { m_position.x , 0.0f, 0.0f }; 
		m_upperAxisBuffer = {m_upperLimit.x, 0.0f, 0.0f};
		m_lowerAxisBuffer = {m_lowerLimit.x, 0.0f, 0.0f};
	}
	if (t_activeAxis.z == 0.0f) 
	{ 
		m_axisBuffer = { 0.0f, 0.0f, m_position.z }; 
		m_upperAxisBuffer = {0.0f, 0.0f, m_upperLimit.z};
		m_lowerAxisBuffer = {0.0f, 0.0f, m_lowerLimit.z};
	}

	m_position *= t_activeAxis;
	m_upperLimit *= t_activeAxis;
	m_lowerLimit *= t_activeAxis;
	updateHitbox();

}