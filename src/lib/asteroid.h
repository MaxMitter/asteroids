#pragma once
#include <ml5/ml5.h>
#include "gb_object.h"
#include "rectangle.h"

class asteroid : public gb_object, MI5_DERIVE(asteroid, gb_object) {
	MI5_INJECT(asteroid)
	using base = gb_object;
public:

	asteroid(wxPoint pos) : base(pos, wxSize{ 10, 10 }) {
		m_shape = std::make_unique<rectangle>(wxRect{ m_position, m_position + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH);
	}

	asteroid(wxPoint pos, int level) : base(pos, wxSize{ 10 * level, 10 * level }), m_level{ level } {
		m_shape = std::make_unique<rectangle>(wxRect{ m_position, m_position + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH);
	}

private:
	int m_level{ 5 };
};