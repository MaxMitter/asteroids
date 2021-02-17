#pragma once
#include <ml5/ml5.h>
#include "gb_object.h"
#include "ellipse.h"

class player : public gb_object, MI5_DERIVE(player, gb_object) {
	MI5_INJECT(player)
	using base = gb_object;
	public:
		player(wxPoint pos) : base(pos, wxPoint{ 10, 10 }) {
			//ellipse ell{ wxRect{ m_position, m_position + m_size }, *wxBLACK_PEN, *wxGREEN_BRUSH };
			m_shape = std::make_unique<ellipse>(wxRect{ m_position, m_position + m_size }, *wxBLACK_PEN, *wxWHITE_BRUSH);
		}

	private:
};