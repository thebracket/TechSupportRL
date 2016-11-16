#include "keyboard_system.hpp"
#include "../globals.hpp"
#include "../components/components.hpp"

using namespace rltk;

void keyboard_system::configure() {
    system_name = "Keyboard";
    subscribe_mbox<key_pressed_t>();
    subscribe_mbox<tick_message>();
}

void keyboard_system::update(const double ms) {
    bool tick = false;
    std::queue<tick_message> * ticks = mbox<tick_message>();
    while (!ticks->empty()) {
        ticks->pop();
        tick = true;
    }

    bool my_turn = false;
    each<player_t>([&my_turn] (entity_t &e, player_t &p) {
        --p.initiative;
        if (p.initiative < 1) my_turn = true;
    });
    if (!my_turn) {
        return;
    }
    waiting_input = true;

    if (!waiting_input) return;


    std::queue<key_pressed_t> * messages = mbox<key_pressed_t>();
    while (!messages->empty()) {
        key_pressed_t e = messages->front();
        messages->pop();        

        // Quit game
        if (e.event.key.code == sf::Keyboard::Q) quitting = true;

        // Num pad
        if (e.event.key.code == sf::Keyboard::Num8) emit_deferred(player_wants_to_move_msg(NORTH));
        if (e.event.key.code == sf::Keyboard::Num9) emit_deferred(player_wants_to_move_msg(NORTHEAST));
        if (e.event.key.code == sf::Keyboard::Num6) emit_deferred(player_wants_to_move_msg(EAST));
        if (e.event.key.code == sf::Keyboard::Num3) emit_deferred(player_wants_to_move_msg(SOUTHEAST));
        if (e.event.key.code == sf::Keyboard::Num2) emit_deferred(player_wants_to_move_msg(SOUTH));
        if (e.event.key.code == sf::Keyboard::Num1) emit_deferred(player_wants_to_move_msg(SOUTHWEST));
        if (e.event.key.code == sf::Keyboard::Num4) emit_deferred(player_wants_to_move_msg(WEST));
        if (e.event.key.code == sf::Keyboard::Num7) emit_deferred(player_wants_to_move_msg(NORTHWEST));
        if (e.event.key.code == sf::Keyboard::Comma) emit_deferred(player_wants_to_move_msg(DIRUP));
        if (e.event.key.code == sf::Keyboard::Period) emit_deferred(player_wants_to_move_msg(DIRDOWN));

        // Arrow keys
        if (e.event.key.code == sf::Keyboard::Up) emit_deferred(player_wants_to_move_msg(NORTH));
        if (e.event.key.code == sf::Keyboard::Down) emit_deferred(player_wants_to_move_msg(SOUTH));
        if (e.event.key.code == sf::Keyboard::Left) emit_deferred(player_wants_to_move_msg(WEST));
        if (e.event.key.code == sf::Keyboard::Right) emit_deferred(player_wants_to_move_msg(EAST));
        
        // VI Keys
        if (e.event.key.code == sf::Keyboard::K) emit_deferred(player_wants_to_move_msg(NORTH));
        if (e.event.key.code == sf::Keyboard::J) emit_deferred(player_wants_to_move_msg(SOUTH));
        if (e.event.key.code == sf::Keyboard::H) emit_deferred(player_wants_to_move_msg(WEST));
        if (e.event.key.code == sf::Keyboard::L) emit_deferred(player_wants_to_move_msg(EAST));

        // Gait control
        if (e.event.key.code == sf::Keyboard::G) emit_deferred(player_changed_gait{});

        // Drinking
        if (e.event.key.code == sf::Keyboard::D) emit_deferred(drink_coffee{});
    }

}