#pragma once
#include <ml5/ml5.h>
#include "shape.h"

enum class direction {
	north,
	north_east,
	east,
	south_east,
	south,
	south_west,
	west,
	north_west
};

wxPoint get_point_from_dir(direction dir) {
	switch (dir) {
		case direction::north: 
			return wxPoint{ 0, -1 };
			break;
		case direction::north_east:
			return wxPoint{ 1, -1 };
			break;
		case direction::east:
			return wxPoint{ 1, 0 };
			break;
		case direction::south_east:
			return wxPoint{ 1, 1 };
			break;
		case direction::south:
			return wxPoint{ 0, 1 };
			break;
		case direction::south_west:
			return wxPoint{ -1, 1 };
			break;
		case direction::west:
			return wxPoint{ -1, 0 };
			break;
		case direction::north_west:
			return wxPoint{ -1, -1 };
			break;
	}
}

class gb_object : public ml5::object, MI5_DERIVE(gb_object, ml5::object) {
	MI5_INJECT(gb_object)
	using context_t = ml5::paint_event::context_t;
public:
	void set_position(wxPoint new_pos) {
		m_position = new_pos;
	}

	void set_speed(int speed) {
		m_speed = speed;
	}

	void set_direction(direction dir) {
		m_dir = dir;
	}

	void move(wxPoint delta) {
		m_position += delta;
	}

	void move() {
		m_position += (m_speed * get_point_from_dir(m_dir));
		m_shape->move(m_speed * get_point_from_dir(m_dir));
	}

	wxPoint get_position() {
		return m_position;
	}

	int get_speed() {
		return m_speed;
	}

	void draw(context_t& context) {
		m_shape->draw(context);
	}

protected:

	gb_object(wxPoint pos, wxSize size)
		: m_position{pos}
		, m_size{size}
	{}

	wxPoint m_position{};
	wxSize m_size{};
	std::unique_ptr<shape> m_shape{};

	int m_speed{ 0 };
	direction m_dir{};
};