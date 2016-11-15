#include "dead_mode.hpp"
#include "../globals.hpp"

#include <rltk.hpp>

using namespace rltk;

void dead_mode::on_init() {
}

void dead_mode::on_exit() {
}

tick_result_t dead_mode::tick(const double ms) {
	term(1)->clear();
	term(2)->clear();

	term(2)->print_center(5, "You have failed!");

	if (quit_reason == CAFFEINE_FAIL) {
		term(2)->print_center(7, "The last of the caffeine has left your bloodstream.");
		term(2)->print_center(8, "You realize that the futility of your corporate");
		term(2)->print_center(9, "serfdom will never get better, and succumb to");
		term(2)->print_center(10, "a life of drudgery.");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		return POP;
	} else {
		return CONTINUE;
	}
}
