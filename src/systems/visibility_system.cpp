#include "visibility_system.hpp"
#include "../components/components.hpp"

#include <rltk.hpp>

using namespace rltk;

void visibility_system::configure() {
    system_name = "Visibility System";
    subscribe_mbox<player_performed_action>();
}

void visibility_system::update(const double ms) {
    map_t * map;
    each<map_t>([&map] (entity_t &e, map_t &m) {
        map = &m;
    });

    // Did the player move? If so, then their viewshed needs updating
    std::queue<player_performed_action> * actions = mbox<player_performed_action>();
    while (!actions->empty()) {
        actions->pop();
        each<player_t, position_t, viewshed_t>([&map] (entity_t &e, player_t &p, position_t &pos, viewshed_t &view) {
            view.visible_tiles.clear();

            visibility_sweep_2d<position_t, navigator_helper>(pos, view.range, [&pos, &view] (position_t reveal) {
                if (reveal.x < 0 || reveal.x > MAP_WIDTH-1 || reveal.y < 0 || reveal.y > MAP_HEIGHT-1) return;

				const int idx = mapidx(reveal.x, reveal.y, pos.level);
                view.visible_tiles.insert(idx);
            }, [&map, &pos] (position_t check) {
                
				if (check.x < 0) check.x = 0;
                if (check.x > MAP_WIDTH-1) check.x = MAP_WIDTH-1;
                if (check.y < 0) check.y = 0;
                if (check.y > MAP_HEIGHT-1) check.y = MAP_HEIGHT-1;
                return map->solid[mapidx(check.x, check.y, pos.level)]==false;
			});
        });
    }

    // Color in the map
    std::fill(map->visible.begin(), map->visible.end(), false);
    each<viewshed_t>([&map] (entity_t &e, viewshed_t &v) {
        if (v.good_guy) {
            for (auto it=v.visible_tiles.begin(); it!=v.visible_tiles.end(); ++it) {
                map->visible[*it] = true;
            }
        } else {
            for (auto it=v.visible_tiles.begin(); it!=v.visible_tiles.end(); ++it) {
                map->visible_baddie[*it] = true;
            }
        }
    });
}
