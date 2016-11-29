#pragma once

#include <rltk.hpp>

enum direction_t { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, DIRUP, DIRDOWN };

struct player_wants_to_move_msg : rltk::base_message_t {
    player_wants_to_move_msg() {}
    player_wants_to_move_msg(const direction_t &dir) : direction(dir) {}

    direction_t direction;
};

struct entity_wants_to_move_randomly : rltk::base_message_t {
    entity_wants_to_move_randomly() {}
    entity_wants_to_move_randomly(const std::size_t id) : entity_id(id) {}
    std::size_t entity_id;
};

struct entity_wants_to_approach_player : rltk::base_message_t {
    entity_wants_to_approach_player() {}
    entity_wants_to_approach_player(const std::size_t mover) : mover_id(mover) {}
    std::size_t mover_id;
};

struct player_performed_action : rltk::base_message_t {
};

struct tick_message : rltk::base_message_t {};
struct slow_tick_message : rltk::base_message_t {};

struct player_changed_gait : rltk::base_message_t {};

struct drink_coffee : rltk::base_message_t {};

struct player_fix_it : rltk::base_message_t {};

struct log_message : public rltk::base_message_t {
    log_message() {}
    log_message(std::vector<rltk::vchar> &line) : chars(line) {}
    std::vector<rltk::vchar> chars;
};

struct inflict_despair : public rltk::base_message_t {
    inflict_despair() {}
    inflict_despair(const std::string n, const int amount, const std::size_t id) : message(n), damage(amount), aggressor(id) {}

    std::string message;
    int damage;
    std::size_t aggressor;
};
