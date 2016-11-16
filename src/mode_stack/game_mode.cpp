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
	xp::rex_sprite lobby("assets/lobby.xp");
	for (int y=0; y<MAP_HEIGHT; ++y) {
		for (int x=0; x<MAP_WIDTH; ++x) {
			const vchar * c = lobby.get_tile(0,x,y);
			const int idx = mapidx(x,y,3);

			switch (c->glyph) {
				case '.' : map.tile_type[idx] = tiles::FLOOR; break;
				case '^' : map.tile_type[idx] = tiles::FREEDOM; break;
				case '"' : map.tile_type[idx] = tiles::GRASS; break;
				case '~' : map.tile_type[idx] = tiles::PATH; break;
				case '<' : map.tile_type[idx] = tiles::UP; break;
				case '>' : map.tile_type[idx] = tiles::DOWN; break;
				case 219 : map.tile_type[idx] = tiles::WALL; break;
				case 176 : map.tile_type[idx] = tiles::WATER; break;
				case 197 : map.tile_type[idx] = tiles::GLASS_DOOR; break;
				case 214 : {
					// Chair
					map.tile_type[idx] = tiles::FLOOR;
					create_entity()->assign(renderable_t{194, rltk::colors::LightSkyBlue})->assign(position_t{x,y,3})->assign(name_t{"Office Chair"});
				} break;
				case 203 : {
					// Table
					map.tile_type[idx] = tiles::FLOOR;
					create_entity()->assign(renderable_t{203, rltk::colors::Brown})->assign(position_t{x,y,3})->assign(name_t{"Office Table"});
				} break;
				case 127 : {
					// Toilet
					map.tile_type[idx] = tiles::FLOOR;
					create_entity()->assign(renderable_t{239, rltk::colors::Blue})->assign(position_t{x,y,3})->assign(name_t{"Toilet"});
				} break;
				case 202 : {
					// Sink
					map.tile_type[idx] = tiles::FLOOR;
					create_entity()->assign(renderable_t{233, rltk::colors::Blue})->assign(position_t{x,y,3})->assign(name_t{"Sink"});
				} break;
				case 167 : {
					// Coffee Station
					map.tile_type[idx] = tiles::FLOOR;
					create_entity()->assign(renderable_t{232, rltk::colors::YELLOW})->assign(position_t{x,y,3})->assign(name_t{"Coffee Machine"})->assign(coffee_machine{});
				} break;
				default  : {
					map.tile_type[idx] = tiles::WALL;
					std::cout << "Unknown REX char: " << +c->glyph << "\n"; 
				} break;
			}
		}
	}
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
	create_entity()->assign(position_t{MAP_WIDTH/2, MAP_HEIGHT-3, 3})
		->assign(player_t{})
		->assign(renderable_t{})
		->assign(viewshed_t{8, true});
}

void game_mode::on_init() {
	quitting = false;

	add_system<time_system>();
	add_system<keyboard_system>();
	add_system<movement_system>();
	add_system<caffeine_system>();
	add_system<visibility_system>();
	add_system<render_system>();
	add_system<hud_system>();
	ecs_configure();
	build_game();
}

void game_mode::on_exit() {
	// ECS stop
	delete_all_entities();
}

tick_result_t game_mode::tick(const double ms) {
	ecs_tick(ms);
	ecs_garbage_collect();

	if (quitting) {
		switch (quit_reason) {
		case QUIT : return POP;
		case CAFFEINE_FAIL : return POP_NO_CAFFEINE;
		}
	} else {
		return CONTINUE;
	}
}

