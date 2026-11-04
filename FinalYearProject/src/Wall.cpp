#include "../header/Wall.h"

Wall::Wall(Vector3 t_pos, float t_l, float t_w, float t_h)
{
	m_position = t_pos;
	m_defaultLength = t_l;
	m_defaultWidth = t_w;
	m_defaultHeight = t_h;

	m_length = m_defaultLength;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;

	m_colour = DARKGRAY;
}

Wall::~Wall()
{
	//std::cout << "Deleted\n";
}

void Wall::update()
{
	// Empty for now, here for polymorphism
}

/// @brief Get Lower Y-Offset Hitbox of Wall, ensures object is below the player while avoiding other walls
/// @return Wall Hitbox offset down
BoundingBox Wall::getLowHitbox()
{
	BoundingBox temp;
	temp.max = m_hitbox.max;
	temp.min = m_hitbox.min;

	temp.max.y -= 1.0f;
	temp.min.y -= 1.0f;

	return temp;
}