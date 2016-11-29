#include <colors.hpp>
#include "intro_mode.hpp"
#include <rltk.hpp>

using namespace rltk;

void intro_mode::on_init() {
}

void intro_mode::on_exit() {
}

tick_result_t intro_mode::tick(const double ms) {
	term(1)->clear();
	term(2)->clear();

	term(2)->print_center(5, "Welcome to Tech Support - The Roguelike", rltk::colors::YELLOW);

    term(2)->print_center(7, "Welcome to your first day as an intern at WidgetCorp.");
    term(2)->print_center(8, "Your goal is to complete enough tech support tickets");
    term(2)->print_center(9, "that WidgetCorp hires you.");
    term(2)->print_center(11, "Navigate with the cursor keys, numpad or vi keys.");
    term(2)->print_center(12, "When you are adjacent to coffee, press D to drink.");
    term(2)->print_center(13, "Press T to open your tablet and access available missions.");
    term(2)->print_center(14, "With an active mission, press S to show a path to the");
    term(2)->print_center(15, "objective. When you get there, press F to fix it.");
    term(2)->print_center(17, "Avoid your co-workers! They will drain your hope in");
    term(2)->print_center(18, "humanity, eventually causing you to give up. Also -");
    term(2)->print_center(19, "don't run out of caffeine!");
    term(2)->print_center(21, "Press Escape to play", rltk::colors::MAGENTA);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		return POP;
	} else {
		return CONTINUE;
	}
}

