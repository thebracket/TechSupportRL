#include "movement_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"

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
    subscribe_mbox<entity_wants_to_move_randomly>();
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

    std::queue<entity_wants_to_move_randomly> * rmove_requests = mbox<entity_wants_to_move_randomly>();
    while (!rmove_requests->empty()) {
        entity_wants_to_move_randomly e = rmove_requests->front();
        rmove_requests->pop();

        auto E = entity(e.entity_id);
        if (!E) break;
        auto pos = E->component<position_t>();
        if (!pos) break;

        std::vector<position_t> candidates;
        if (!map->solid[mapidx(pos->x-1, pos->y, pos->level)]) candidates.push_back(position_t(pos->x-1, pos->y, pos->level));
        if (!map->solid[mapidx(pos->x+1, pos->y, pos->level)]) candidates.push_back(position_t(pos->x+1, pos->y, pos->level));
        if (!map->solid[mapidx(pos->x, pos->y-1, pos->level)]) candidates.push_back(position_t(pos->x, pos->y-1, pos->level));
        if (!map->solid[mapidx(pos->x, pos->y+1, pos->level)]) candidates.push_back(position_t(pos->x, pos->y+1, pos->level));
        if (map->tile_type[mapidx(pos->x, pos->y, pos->level)] == tiles::UP) candidates.push_back(position_t(pos->x, pos->y, pos->level+1));
        if (map->tile_type[mapidx(pos->x, pos->y, pos->level)] == tiles::DOWN) candidates.push_back(position_t(pos->x, pos->y, pos->level-1));

        if (!candidates.empty()) {
            const int selection = rng.roll_dice(1, candidates.size()-1);
            pos->x = candidates[selection].x;
            pos->y = candidates[selection].y;
            pos->level = candidates[selection].level;
        }
    }
}