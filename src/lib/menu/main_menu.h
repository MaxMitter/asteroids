#pragma once
#include "menu.h"

class main_menu : public menu, MI5_DERIVE(main_menu, menu) {
	MI5_INJECT(main_menu)
		using context_t = ml5::paint_event::context_t;
public:
	void init_buttons() override {
		clear_buttons();
		wxRect center_rect{};
		wxPoint t_l{ int(m_context_size.GetWidth() / 2) - int(m_context_size.GetWidth() * 0.1),
					int(m_context_size.GetHeight() / 2) - int(m_context_size.GetHeight() * 0.05) };
		wxPoint b_r{ int(m_context_size.GetWidth() / 2) + int(m_context_size.GetWidth() * 0.1),
					int(m_context_size.GetHeight() / 2) + int(m_context_size.GetHeight() * 0.05) };
		center_rect.SetTopLeft(t_l);
		center_rect.SetBottomRight(b_r);
		auto start = std::make_unique<button>();

		wxRect start_btn{};
		start_btn.SetTopLeft(t_l - wxPoint{ 0, 20 });
		start_btn.SetBottomRight(b_r - wxPoint{ 0, 20 });
		start->rect = std::make_unique<rectangle>(start_btn, *wxWHITE_PEN, *wxTRANSPARENT_BRUSH);
		start->text = std::make_unique<text>(start_btn, "Start Game");

		auto quit = std::make_unique<button>();
		wxRect quit_btn{};
		quit_btn.SetTopLeft(t_l + wxPoint{ 0, 20 });
		quit_btn.SetBottomRight(b_r + wxPoint{ 0, 20 });
		quit->rect = std::make_unique<rectangle>(quit_btn, *wxWHITE_PEN, *wxTRANSPARENT_BRUSH);
		quit->text = std::make_unique<text>(quit_btn, "Quit Game");

		m_buttons.add(std::move(start));
		m_buttons.add(std::move(quit));
		//std::cout << start_btn.GetTopLeft() << "|" << start_btn.GetBottomRight() << std::endl;
	}
};