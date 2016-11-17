#include "caffeine_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"
#include <rltk.hpp>

using namespace rltk;

void decrement_caffeine(player_t &p) {
    if (p.caffeine > 0) --p.caffeine;
    if (p.caffeine < 1) {
        quitting = true;
        quit_reason = CAFFEINE_FAIL;
    }
}

void caffeine_system::configure() {
    system_name = "Caffeine System";
    subscribe_mbox<player_performed_action>();
    subscribe_mbox<tick_message>();
    subscribe_mbox<drink_coffee>();
}

void caffeine_system::update(const double ms) {
    std::queue<player_performed_action> * actions = mbox<player_performed_action>();
    while (!actions->empty()) {
        actions->pop();

        each<player_t>([] (entity_t &e, player_t &p) {
            if (p.gait == SNEAKING) {
                decrement_caffeine(p);
                decrement_caffeine(p);
            } else {
                decrement_caffeine(p);
            }
        });
    }

    map_t * map;
    each<map_t>([&map] (entity_t &e, map_t &m) { map = &m; });

    std::queue<tick_message> * ticks = mbox<tick_message>();
    while (!ticks->empty()) {
        ticks->pop();

        std::fill(map->has_coffee.begin(), map->has_coffee.end(), false);
        each<coffee_machine, position_t>([&map] (entity_t &e, coffee_machine &c, position_t &pos) {
            map->has_coffee[mapidx(pos.x, pos.y, pos.level)] = true;
            map->has_coffee[mapidx(pos.x-1, pos.y, pos.level)] = true;
            map->has_coffee[mapidx(pos.x+1, pos.y, pos.level)] = true;
            map->has_coffee[mapidx(pos.x, pos.y-1, pos.level)] = true;
            map->has_coffee[mapidx(pos.x, pos.y+1, pos.level)] = true;
        });
    }

    std::queue<drink_coffee> * drinkorders = mbox<drink_coffee>();
    while (!drinkorders->empty()) {
        drinkorders->pop();

        each<player_t, position_t>([&map] (entity_t &e, player_t &p, position_t &pos) {
            const int idx = mapidx(pos.x, pos.y, pos.level);
            if (map->has_coffee[idx]) {
                emit(log_message{LOG{}.text("You enjoy a cup of coffee.")->chars});
                p.caffeine = 101;
                emit(player_performed_action{});
            }
        });
    }
}