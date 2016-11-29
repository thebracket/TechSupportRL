#include "render_system.hpp"
#include "../components/components.hpp"
#include <boost/container/flat_map.hpp>
#include <vector>
#include "../globals.hpp"

using namespace rltk;

void render_system::configure() {
	system_name = "Render System";
	subscribe<slow_tick_message>([this] (slow_tick_message msg) {
		++ticker;
	});
    subscribe<player_performed_action>([this] (player_performed_action &msg) {
       if (this->path_to_mission) this->path_to_mission.reset();
        show_path = false;
    });
}

void render_system::update(const double ms) {
	term(1)->clear();

	// Build the renderables list
	boost::container::flat_map<int, std::vector<vchar>> renderables;
	each<position_t, renderable_t>([&renderables] (entity_t &e, position_t &pos, renderable_t &r) {
		const int idx = mapidx(pos.x, pos.y, pos.level);
		auto finder = renderables.find(idx);
		if (finder == renderables.end()) {
			renderables[idx] = std::vector<vchar>{ vchar{r.glyph, r.color, rltk::colors::BLACK} };
		} else {
			renderables[idx].push_back( vchar{r.glyph, r.color, rltk::colors::BLACK} );
		}
	});

	// Locate the player and therefore the camera
	int player_x, player_y, player_z;
	each<player_t, position_t>([&player_x, &player_y, &player_z] (entity_t &e, player_t &p, position_t &pos) {
		player_x = pos.x;
		player_y = pos.y;
		player_z = pos.level;
	});

    // Highlight the mission target
    bool has_mission = false;
    each<mission_t>([&renderables, &has_mission, this, &player_x, &player_y, &player_z] (entity_t &e, mission_t &m) {
        has_mission = true;
        const int idx = mapidx(m.x, m.y, m.z);
        auto finder = renderables.find(idx);
        if (finder == renderables.end()) {
            renderables[idx] = std::vector<vchar>{ vchar{'*', rltk::colors::YELLOW, rltk::colors::RED} };
        } else {
            renderables[idx].push_back( vchar{'*', rltk::colors::YELLOW, rltk::colors::RED} );
        }

        if (show_path) {
            if (!path_to_mission) {
                path_to_mission = find_path(position_t{player_x, player_y, player_z}, position_t{m.x, m.y, m.z});
            } else {
                if (path_to_mission->success) {
                    for (const position_t &step : path_to_mission->steps) {
                        const int idx = mapidx(step.x, step.y, step.level);
                        auto finder = renderables.find(idx);
                        if (finder == renderables.end()) {
                            renderables[idx] = std::vector<vchar>{vchar{'*', rltk::colors::YELLOW, rltk::colors::BLACK}};
                        } else {
                            renderables[idx].push_back(vchar{'*', rltk::colors::YELLOW, rltk::colors::BLACK});
                        }
                    }
                }
            }
        }
    });
    if (!has_mission && path_to_mission) path_to_mission.reset();

	// Render the map
	map_t * map;
	each<map_t>([&map] (entity_t &ignore, map_t &mapref) { map = &mapref; });
	const int width = term(1)->term_width - 10; // starts at 13
	const int height = term(1)->term_height - 12;
	const int offset_y = (height/2) - player_y + 10;
	const int offset_x = (width/2) - player_x + 10;

	for (int y=0; y<height; ++y) {
		const int world_y = y - offset_y;
		for (int x=13; x<width+10; ++x) {
			const int world_x = x - offset_x;

			if (world_x > -1 && world_x < MAP_WIDTH && world_y > -1 && world_y < MAP_HEIGHT) {
				const int idx = mapidx(world_x, world_y, player_z);

				color_t col = rltk::colors::WHITE;
				color_t bg = rltk::colors::BLACK;
				uint16_t glyph = '.';

				auto finder = renderables.find(idx);
				if (finder != renderables.end()) {
					const std::size_t rotator = ticker % finder->second.size();
					col = finder->second[rotator].foreground;
					bg = finder->second[rotator].background;
					glyph = finder->second[rotator].glyph;
				} else {
					col = rltk::colors::WHITE;
					bg = rltk::colors::BLACK;
					glyph = '.';

					switch (map->tile_type[idx]) {
						case tiles::FLOOR : { col = rltk::colors::WHITE; glyph = 256; } break;
                        case tiles::FLOOR_RED : { col = rltk::colors::RED; glyph = 256; } break;
						case tiles::WALL : { col = rltk::colors::WHITE; glyph = 258; } break;
						case tiles::UP : { col = rltk::colors::WHITE; glyph = 259; } break;
						case tiles::DOWN : { col = rltk::colors::WHITE; glyph = 260; } break;
						case tiles::GRASS : { col = rltk::colors::WHITE; glyph = 261; } break;
						case tiles::FREEDOM : { col = rltk::colors::WHITE; glyph = 261; } break;
						case tiles::PATH : { col = rltk::colors::WHITE; glyph = 262; } break;
						case tiles::GLASS_DOOR : { col = rltk::colors::WHITE; glyph = 257; } break;
						case tiles::WATER : { col = rltk::colors::WHITE; glyph = 263; } break;
					}
                    if (map->visible_baddie[idx]) {
                        col = rltk::colors::Pink;
                    }

				}
				if (!map->visible[idx]) {
					col = darken(50, col);
				}

				term(1)->set_char(x, y, vchar{glyph, col, bg});
			}
		}
	}

	// Render renderables
}
