#pragma once
#include <ml5/ml5.h>
#include "../rectangle.h"
#include "../text.h"

typedef struct button {
	std::unique_ptr<rectangle> rect;
	std::unique_ptr<text> text;
} button;

class menu : public ml5::object, MI5_DERIVE(menu, ml5::object) {
	MI5_INJECT(menu)
		using context_t = ml5::paint_event::context_t;
	public:
		menu(wxSize size = wxSize{ 100, 100 }) : m_context_size{ size } {
			
		}

		void set_font(wxFont font) {
			m_font = font;
		}

		void set_context_size(wxSize size) {
			m_context_size = size;
		}

		void set_font_size(int f_size) {
			m_font_size = f_size;
		}

		virtual void init_buttons() = 0;

		void clear_buttons() {
			m_buttons.clear();
		}

		void draw_menu(context_t& context) {
			for (auto& button : m_buttons) {
				button->rect->draw(context);
				button->text->draw(context);
			}
		}

	protected:
		ml5::vector<std::unique_ptr<button>> m_buttons{};
		wxSize m_context_size{ 0, 0 };
		int m_font_size{ 10 };
		wxFont m_font{m_font_size, wxMODERN, wxNORMAL, wxNORMAL, false, "monospace"};
};