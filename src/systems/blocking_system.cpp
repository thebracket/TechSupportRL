#include "blocking_system.hpp"
#include "../components/components.hpp"

using namespace rltk;

void blocking_system::configure() {
    system_name = "Blocking system";
    subscribe_mbox<tick_message>();
}

void blocking_system::update(const double ms) {
    std::queue<tick_message> * ticks = mbox<tick_message>();
    while (!ticks->empty()) {
        ticks->pop();

        map_t * map;
        each<map_t>([&map] (entity_t &e, map_t &m) { map = &m; });
        map->calculate_walkability();
        each<blocker_t, position_t>([&map] (entity_t &e, blocker_t &b, position_t &pos) {
            const int idx = mapidx(pos.x, pos.y, pos.level);
            map->solid[idx] = true;
        });
    }
}