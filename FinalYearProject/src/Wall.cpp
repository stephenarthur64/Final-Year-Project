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
