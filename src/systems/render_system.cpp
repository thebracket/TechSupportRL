#include "render_system.hpp"
#include "../components/components.hpp"
#include <boost/container/flat_map.hpp>
#include <vector>

using namespace rltk;

void render_system::configure() {
	system_name = "Render System";
	subscribe<slow_tick_message>([this] (slow_tick_message msg) {
		++ticker;
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
				uint8_t glyph = '.';

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
						case tiles::FLOOR : { col = rltk::colors::GREY; glyph = '.'; } break;
						case tiles::WALL : { col = rltk::colors::GREY; glyph = 219; } break;
						case tiles::UP : { col = rltk::colors::WHITE; glyph = '<'; } break;
						case tiles::DOWN : { col = rltk::colors::WHITE; glyph = '>'; } break;
						case tiles::GRASS : { col = rltk::colors::DARK_GREEN; glyph = '.'; } break;
						case tiles::FREEDOM : { col = rltk::colors::LIGHT_GREEN; glyph = '^'; } break;
						case tiles::PATH : { col = rltk::colors::GREY; glyph = '^'; } break;
						case tiles::GLASS_DOOR : { col = rltk::colors::CYAN; glyph = 197; } break;
						case tiles::WATER : { col = rltk::colors::BLUE; glyph = '~'; } break;
					}					
					
				}
				if (!map->visible[idx]) {
					col = darken(50, col);
				}
				if (map->visible_baddie[idx]) {
					bg = rltk::colors::DarkBlue;
				}

				term(1)->set_char(x, y, vchar{glyph, col, bg});
			}
		}
	}

	// Render renderables
}
