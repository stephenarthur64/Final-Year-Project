#include "../header/Wall.h"

Wall::Wall(Vector3 t_pos, float t_l, float t_w, float t_h)
{
	m_position = t_pos;
	m_length = t_l;
	m_width = t_w;
	m_height = t_h;
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