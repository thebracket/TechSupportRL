#include "path_finding.hpp"
#include "../components/map.hpp"
#include <rltk.hpp>

using namespace rltk;

namespace path {
    map_t *map;
}

struct navigator_t {
    inline static void test_direction(const position_t &pos, const position_t &dest, std::vector<position_t> &successors) {

        if (dest.x < 0 || dest.x > MAP_WIDTH-1 || dest.y < 0 || dest.y > MAP_HEIGHT || dest.level < 0 || dest.level > MAP_DEPTH) return;

        bool can_go = false;
        const int idx = mapidx(pos);
        const int destidx = mapidx(dest);
        if (pos.level == dest.level) {
            if (!path::map->solid[destidx]) can_go = true;
        } else {
            if (dest.level > pos.level && path::map->tile_type[idx] == tiles::UP) {
                can_go = true;
            } else if (path::map->tile_type[idx] == tiles::DOWN) {
                can_go = true;
            }
        }

        if (can_go) {
            successors.push_back(dest);
        }
    }

    static float get_distance_estimate(position_t &pos, position_t &goal) {
        const float d = distance3d(pos.x, pos.y, pos.level, goal.x, goal.y, goal.level);
        return d;
    }

    static bool is_goal(position_t &pos, position_t &goal) {
        return pos == goal;
    }

    // This is where we calculate where you can go from a given tile. In this case, we check
    // all 8 directions, and if the destination is walkable return it as an option.
    static bool get_successors(position_t pos, std::vector<position_t> &successors) {
        test_direction(pos, position_t{pos.x, pos.y-1, pos.level}, successors);
        test_direction(pos, position_t{pos.x, pos.y+1, pos.level}, successors);
        test_direction(pos, position_t{pos.x+1, pos.y, pos.level}, successors);
        test_direction(pos, position_t{pos.x-1, pos.y, pos.level}, successors);
        test_direction(pos, position_t{pos.x, pos.y, pos.level-1}, successors);
        test_direction(pos, position_t{pos.x, pos.y, pos.level+1}, successors);

        return true;
    }

    // This function lets you set a cost on a tile transition. For now, we'll always use a cost of 1.0.
    static float get_cost(position_t &position, position_t &successor) {
        return 1.0f;
    }

    // This is a simple comparison to determine if two locations are the same. It just passes
    // through to the location_t's equality operator in this instance (we didn't do that automatically)
    // because there are times you might want to behave differently.
    static bool is_same_state(position_t &lhs, position_t &rhs) {
        return lhs == rhs;
    }
};

std::shared_ptr<rltk::navigation_path<position_t>> find_path(const position_t &start, const position_t &end) {
    const bool find_adjacent = true;
    each<map_t>([] (entity_t &ignore, map_t &mapref) { path::map = &mapref; });

    auto result = rltk::find_path<position_t, navigator_t>(start, end);
    if (find_adjacent && result->success == false) {
        std::array<position_t, 6> candidates {
                position_t{end.x-1, end.y, end.level},
                position_t{end.x+1, end.y, end.level},
                position_t{end.x, end.y-1, end.level},
                position_t{end.x, end.y+1, end.level}
        };
        for (int i=0; i<4; ++i) {
            result.reset();
            result = rltk::find_path<position_t, navigator_t>(start, candidates[i]);
            if (result->success) return result;
        }
    }
    return result;
}
