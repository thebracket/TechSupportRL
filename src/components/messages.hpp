#pragma once

#include <rltk.hpp>

enum direction_t { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, DIRUP, DIRDOWN };

struct player_wants_to_move_msg : rltk::base_message_t {
    player_wants_to_move_msg() {}
    player_wants_to_move_msg(const direction_t &dir) : direction(dir) {}

    direction_t direction;
};

struct player_performed_action : rltk::base_message_t {
};

