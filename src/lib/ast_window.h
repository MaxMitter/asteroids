#pragma once
#include <ml5/ml5.h>
#include <cstdlib>
#include "player.h"
#include "asteroid.h"
#include "menu/main_menu.h"

#define TICK_INTERVAL 10

class ast_window : public ml5::window, MI5_DERIVE(ast_window, ml5::window) {
	MI5_INJECT(ast_window)
		using context_t = ml5::paint_event::context_t;
	
	public:
		void on_init() override {
			set_prop_background_brush(*wxBLACK_BRUSH);
			m_player = std::make_unique<player>(wxPoint{ get_width() / 2, get_height() / 2 });
			start_timer(std::chrono::milliseconds{ TICK_INTERVAL });
			main_menu_active = true;
		}

		void on_mouse_left_down(ml5::mouse_event const& event) override {
			//std::cout << "Test: " << event.get_position() << std::endl;
			auto temp = std::make_unique<asteroid>(event.get_position(), rand() % 5 + 1);
			m_asteroids.add(std::move(temp));
			//std::cout << "Test end"<< std::endl;
		}

		void on_key(ml5::key_event const& event) override {
			std::cout << event.get_key_code() << std::endl;
			if (event.get_key_code() == 119) {
				m_player->set_direction(direction::north);
				m_player->set_speed(m_player->get_speed() + 5);
			} else if (event.get_key_code() == 115) {
				m_player->set_speed(m_player->get_speed() - 5);
			}
		}

		void on_paint(ml5::paint_event const& event) override {
			//std::cout << "on_paint\n";
			
			context_t& context = event.get_context();

			if (main_menu_active) {
				m_main_menu.set_context_size(this->get_size());
				std::cout << this->get_size() << std::endl;
				m_main_menu.init_buttons();
				m_main_menu.draw_menu(context);
			} else {
				m_player->draw(context);

				for (auto& asteroid : m_asteroids) {
					asteroid->draw(context);
				}
			}			
		}

		void on_timer(ml5::timer_event const& event) override {
			stop_timer();
			
			m_player->move();

			for (auto& asteroid : m_asteroids) {
				asteroid->move();
			}

			refresh();
			start_timer(std::chrono::milliseconds{ TICK_INTERVAL });
		}

	private:

		std::unique_ptr<player> m_player{};
		ml5::vector<std::unique_ptr<asteroid>> m_asteroids{};
		bool main_menu_active{ false };
		main_menu m_main_menu{};
};