#include "movement_system.hpp"
#include "../components/components.hpp"

using namespace rltk;

void movement_system::configure() {
    system_name = "Movement System";
    subscribe_mbox<player_wants_to_move_msg>();
    subscribe<player_changed_gait>([] (player_changed_gait &p) {
        each<player_t>([] (entity_t &e, player_t &p) {
            if (p.gait == SNEAKING) {
                p.gait = WALKING;
            } else if (p.gait == WALKING) {
                p.gait = RUNNING;
            } else {
                p.gait = SNEAKING;
            }
        });
    });
}

void movement_system::update(const double ms) {
    map_t * map;
	each<map_t>([&map] (entity_t &ignore, map_t &mapref) { map = &mapref; });

    std::queue<player_wants_to_move_msg> * move_requests = mbox<player_wants_to_move_msg>();
    while (!move_requests->empty()) {
        player_wants_to_move_msg e = move_requests->front();
        move_requests->pop();

        each<player_t, position_t>([&e, &map] (entity_t &player_entity, player_t &player, position_t &pos) {
            const int idx = mapidx(pos.x, pos.y, pos.level);

            if (e.direction == DIRUP && map->tile_type[idx] == tiles::UP) ++pos.level;
            if (e.direction == DIRDOWN && map->tile_type[idx] == tiles::DOWN) --pos.level;

            if (e.direction == NORTH && !map->solid[mapidx(pos.x, pos.y-1, pos.level)]) --pos.y;
            if (e.direction == NORTHEAST && !map->solid[mapidx(pos.x+1, pos.y-1, pos.level)]) { --pos.y; ++pos.x; }
            if (e.direction == EAST && !map->solid[mapidx(pos.x+1, pos.y, pos.level)]) ++pos.x;
            if (e.direction == SOUTHEAST && !map->solid[mapidx(pos.x+1, pos.y+1, pos.level)]) { ++pos.y; ++pos.x; }
            if (e.direction == SOUTH && !map->solid[mapidx(pos.x, pos.y+1, pos.level)]) ++pos.y;
            if (e.direction == SOUTHWEST && !map->solid[mapidx(pos.x-1, pos.y+1, pos.level)]) { ++pos.y; --pos.x; }
            if (e.direction == WEST && !map->solid[mapidx(pos.x-1, pos.y, pos.level)]) --pos.x;
            if (e.direction == NORTHWEST && !map->solid[mapidx(pos.x-1, pos.y-1, pos.level)]) { --pos.y; --pos.x; }

            if (idx != mapidx(pos.x,pos.y,pos.level)) emit(player_performed_action{});
        });
    }
}