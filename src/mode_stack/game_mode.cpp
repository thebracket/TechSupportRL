#include "game_mode.hpp"
#include "../globals.hpp"
#include <rltk.hpp>
#include "../systems/systems.hpp"
#include "../components/components.hpp"

using namespace rltk;

void build_stairs(map_t &map) {
	// The middle gets an elevator
	const int mid_x = MAP_WIDTH/2;
	const int mid_y = MAP_HEIGHT/2;
	map.tile_type[mapidx(mid_x, mid_y, 0)] = tiles::UP;
	bool even = true;
	for (int l=1; l<MAP_DEPTH-2; ++l) {
		if (even) {
			map.tile_type[mapidx(mid_x, mid_y, l)] = tiles::UP;
			map.tile_type[mapidx(mid_x+1, mid_y, l)] = tiles::DOWN;
		} else {
			map.tile_type[mapidx(mid_x, mid_y, l)] = tiles::DOWN;
			map.tile_type[mapidx(mid_x+1, mid_y, l)] = tiles::UP;			
		}
		even = !even;
	}
	if (even) {
		map.tile_type[mapidx(mid_x+1, mid_y, MAP_DEPTH-1)] = tiles::DOWN;
	} else {
		map.tile_type[mapidx(mid_x, mid_y, MAP_DEPTH-1)] = tiles::DOWN;		
	}
}

void build_lobby(map_t &map) {
	// The lobby level - add grass
	for (int i=1; i<5; ++i) {
		for (int j=0; j<MAP_WIDTH; ++j) {
			if (j > (MAP_WIDTH/2)-2 && j < (MAP_WIDTH/2)+2) {
				map.tile_type[mapidx(j, i, 3)] = tiles::PATH;
				map.tile_type[mapidx(j, MAP_HEIGHT-1-i, 3)] = tiles::PATH;
			} else {
				map.tile_type[mapidx(j, i, 3)] = tiles::GRASS;
				map.tile_type[mapidx(j, MAP_HEIGHT-1-i, 3)] = tiles::GRASS;
			}
			map.tile_type[mapidx(j, 0, 3)] = tiles::FREEDOM;
			map.tile_type[mapidx(j, MAP_HEIGHT-1, 3)] = tiles::FREEDOM;
		}
		for (int j=0; j<MAP_HEIGHT; ++j) {
			map.tile_type[mapidx(i, j, 3)] = tiles::GRASS;
			map.tile_type[mapidx(MAP_WIDTH-1-i, j, 3)] = tiles::GRASS;
			map.tile_type[mapidx(0, j, 3)] = tiles::FREEDOM;
			map.tile_type[mapidx(MAP_WIDTH-1, j, 3)] = tiles::FREEDOM;
		}
	}
	// Add glass doors and walls
	for (int x=5; x<MAP_WIDTH-5; ++x) {
		map.tile_type[mapidx(x, 5, 3)] = tiles::WALL;
		map.tile_type[mapidx(x, MAP_HEIGHT-6, 3)] = tiles::WALL;
	}
	for (int y=5; y<MAP_HEIGHT-5; ++y) {
		map.tile_type[mapidx(5, y, 3)] = tiles::WALL;
		map.tile_type[mapidx(MAP_WIDTH-6, y, 3)] = tiles::WALL;
	}
	map.tile_type[mapidx((MAP_WIDTH/2)-1, 5, 3)] = tiles::GLASS_DOOR;
	map.tile_type[mapidx((MAP_WIDTH/2), 5, 3)] = tiles::GLASS_DOOR;
	map.tile_type[mapidx((MAP_WIDTH/2)+1, 5, 3)] = tiles::GLASS_DOOR;
	map.tile_type[mapidx((MAP_WIDTH/2)-1, MAP_HEIGHT-6, 3)] = tiles::GLASS_DOOR;
	map.tile_type[mapidx((MAP_WIDTH/2), MAP_HEIGHT-6, 3)] = tiles::GLASS_DOOR;
	map.tile_type[mapidx((MAP_WIDTH/2)+1, MAP_HEIGHT-6, 3)] = tiles::GLASS_DOOR;
}

void game_mode::build_game() {
	map_t map{};

	// Set the map to all floors
	std::fill(map.tile_type.begin(), map.tile_type.end(), tiles::FLOOR);
	std::fill(map.solid.begin(), map.solid.end(), false);

	// Set the exterior walls on each level
	for (int level = 0; level < MAP_DEPTH; ++level) {
		for (int y=0; y<MAP_HEIGHT; ++y) {
			for (int x=0; x<MAP_WIDTH; ++x) {
				map.tile_type[mapidx(x,0,level)] = tiles::WALL;
				map.tile_type[mapidx(x,MAP_HEIGHT-1,level)] = tiles::WALL;
				map.tile_type[mapidx(0,y,level)] = tiles::WALL;
				map.tile_type[mapidx(MAP_WIDTH-1,y,level)] = tiles::WALL;
			}
		}
	}

	build_stairs(map);
	build_lobby(map);

	// Walkability
	map.calculate_walkability();

	create_entity()->assign(std::move(map));
	create_entity()->assign(position_t{MAP_WIDTH/2, MAP_HEIGHT-3, 3})->assign(player_t{})->assign(renderable_t{});
}

void game_mode::on_init() {
	quitting = false;

	add_system<render_system>();
	add_system<hud_system>();
	add_system<keyboard_system>();
	add_system<movement_system>();
	add_system<caffeine_system>();
	ecs_configure();
	build_game();
}

void game_mode::on_exit() {
	// ECS stop
	delete_all_entities();
}

tick_result_t game_mode::tick(const double ms) {
	ecs_tick(ms);

	if (quitting) {
		switch (quit_reason) {
		case QUIT : return POP;
		case CAFFEINE_FAIL : return POP_NO_CAFFEINE;
		}
	} else {
		return CONTINUE;
	}
}

