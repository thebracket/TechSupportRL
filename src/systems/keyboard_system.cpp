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

    std::queue<key_pressed_t> * messages = mbox<key_pressed_t>();
    while (!messages->empty()) {
        key_pressed_t e = messages->front();
        messages->pop();        

        // Quit game
        if (e.event.key.code == sf::Keyboard::Q) {
            quitting = true;
            quit_reason = SAVEQUIT;
        }

        // Num pad
        if (e.event.key.code == sf::Keyboard::Numpad8) emit_deferred(player_wants_to_move_msg(NORTH));
        if (e.event.key.code == sf::Keyboard::Numpad9) emit_deferred(player_wants_to_move_msg(NORTHEAST));
        if (e.event.key.code == sf::Keyboard::Numpad6) emit_deferred(player_wants_to_move_msg(EAST));
        if (e.event.key.code == sf::Keyboard::Numpad3) emit_deferred(player_wants_to_move_msg(SOUTHEAST));
        if (e.event.key.code == sf::Keyboard::Numpad2) emit_deferred(player_wants_to_move_msg(SOUTH));
        if (e.event.key.code == sf::Keyboard::Numpad1) emit_deferred(player_wants_to_move_msg(SOUTHWEST));
        if (e.event.key.code == sf::Keyboard::Numpad4) emit_deferred(player_wants_to_move_msg(WEST));
        if (e.event.key.code == sf::Keyboard::Numpad7) emit_deferred(player_wants_to_move_msg(NORTHWEST));
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

        // Open your tablet for quests and similar
        if (e.event.key.code == sf::Keyboard::T) { quitting = true; quit_reason = TABLET; }
        if (e.event.key.code == sf::Keyboard::S) { show_path = true; }
        if (e.event.key.code == sf::Keyboard::F) { emit_deferred(player_fix_it{}); }
    }

}