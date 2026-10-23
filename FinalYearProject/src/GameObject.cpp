#include "../header/GameObject.h"

GameObject::GameObject() : m_position({0.0f, 2.0f, 0.0f}), m_velocity({0.0f, 0.0f, 0.0f})
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
	DrawCube(m_position, m_width, m_height, m_length, m_colour);
	
	if (m_drawHitbox)
	{
		DrawBoundingBox(m_hitbox, RED);
	}
}

void GameObject::move()
{
	m_position += m_velocity;
	updateHitbox();
	m_velocity = { 0.0f, 0.0f, 0.0f };
}

void GameObject::updateHitbox()
{
	m_hitbox.min = { m_position.x - (m_width / 2.0f), m_position.y - (m_height / 2.0f), m_position.z - (m_length / 2.0f) };
	m_hitbox.max = { m_position.x + (m_width / 2.0f), m_position.y + (m_height / 2.0f), m_position.z + (m_length / 2.0f) };
}

void GameObject::applyForce(Vector3 t_force)
{
	m_velocity += t_force * m_speed;

	m_velocity = Vector3ClampValue(m_velocity, 0.0f, MAX_SPEED);
}

BoundingBox GameObject::getNextHitbox()
{
	BoundingBox tempBox = m_hitbox;

	tempBox.min += m_velocity * m_speed;
	tempBox.max += m_velocity * m_speed;
	return tempBox;
}

void GameObject::swapDimension(GameState t_state, Vector3 t_activeAxis)
{
	m_state = t_state;

	switch (m_state)
	{
	case GameState::TWO_DIMENSION:
		swapAxis(t_activeAxis);
		break;
	case GameState::THREE_DIMENSION:
		m_position += m_axisBuffer;
		m_axisBuffer = { 0.0f, 0.0f, 0.0f };
		updateHitbox();
		break;
	default:
		break;
	}

}

void GameObject::swapAxis(Vector3 t_activeAxis)
{
	m_position += m_axisBuffer;

	if (t_activeAxis.x == 0.0f) { m_axisBuffer = { m_position.x , 0.0f, 0.0f }; }
	if (t_activeAxis.z == 0.0f) { m_axisBuffer = { 0.0f, 0.0f, m_position.z }; }

	m_position *= t_activeAxis;
	updateHitbox();

}
