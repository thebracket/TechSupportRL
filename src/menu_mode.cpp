#include "menu_mode.hpp"
#include <rltk.hpp>
#include <boost/filesystem.hpp>

using namespace rltk;

bool menu_mode::save_exists() const {
	return boost::filesystem::exists("savegame.dat");
}

tick_result_t menu_mode::tick(const double ms) {
	if (first_run) {
		first_run = false;
		save_exists_cache = save_exists();
		if (save_exists_cache) {
			selection = 0;
		} else {
			selection = 1;
		}
	}

	if (key_delay < 1.0 && is_window_focused()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			--selection;
			if (!save_exists_cache && selection == 0) --selection;
			if (selection < 0) selection = options.size()-1;
			key_delay = KEY_PAUSE;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			++selection;
			if (selection > options.size()-1) selection = 0;
			if (!save_exists_cache && selection == 0) ++selection;
			key_delay = KEY_PAUSE;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (selection == 2) return POP;
		}
	} else {
		key_delay -= ms;
	}

	term(2)->clear();
	term(1)->clear();

	term(2)->print_center(5, "Tech Support - The Roguelike", rltk::colors::YELLOW);
	term(2)->print_center(8, "A Bracket Production");

	int y = (term(2)->term_height/2) - (options.size() / 2);
	int i = 0;
	for (const auto &opt : options) {
		if (i == selection) {
			term(2)->print_center(y, opt, rltk::colors::BLACK, rltk::colors::YELLOW);
		} else if (i > 0) {
			term(2)->print_center(y, opt);
		} else {
			term(2)->print_center(y, opt, rltk::colors::GREY);
		}
		++y;
		++i;
	}
	return CONTINUE;
}

