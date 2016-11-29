#include <colors.hpp>
#include "win_mode.hpp"
#include <rltk.hpp>

using namespace rltk;

void win_mode::on_init() {
}

void win_mode::on_exit() {
}

tick_result_t win_mode::tick(const double ms) {
    term(1)->clear();
    term(2)->clear();

    term(2)->print_center(5, "You're Hired!", rltk::colors::YELLOW);
    term(2)->print_center(7, "Congratulation! You have completed enough tickets to");
    term(2)->print_center(8, "earn a permanent position in WidgetCorp.");
    term(2)->print_center(9, "You celebrate your victory by going home and");
    term(2)->print_center(10, "getting a good night's sleep.");

    term(2)->print_center(7, "Welcome to your first day as an intern at WidgetCorp.");
    term(2)->print_center(21, "Press Enter to quit", rltk::colors::MAGENTA);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        return POP;
    } else {
        return CONTINUE;
    }
}

