#include "game_mode.hpp"
#include "../globals.hpp"
#include <rltk.hpp>
#include "../systems/systems.hpp"
#include "../components/components.hpp"
#include "../components/loader.hpp"

using namespace rltk;

void build_stairs(map_t &map) {
	// The middle gets an elevator
	const int mid_x = MAP_WIDTH/2;
	const int mid_y = MAP_HEIGHT/2 - 2;
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

void spawn_receptionist(const int &x, const int &y, const int &z) {
	const int roll = rng.roll_dice(1,4);

	switch (roll) {
		case 1 : {
			create_entity()->assign(renderable_t{270, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Cranky Receptionist"})
				->assign(static_ai{})
				->assign(viewshed_t{2})
				->assign(despair_attack_t{{
					{ "says \"I'll be with you in a minute.\"", 1 },
					{ "says \"Don't worry, WidgetCorp will find a use for you.\"", 1 },
					{ "says \"I'm sure I'll find you in the database eventually.\"", 1 },
					{ "says \"Welcome to WidgetCorp. Please wait.\"", 1 },
					{ "says \"Maybe you can tell me why my cat pictures are loading so slowly?\"", 1 }
				}});
		} break;
		case 2 : {
			create_entity()->assign(renderable_t{271, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Bored Receptionist"})
				->assign(static_ai{})
				->assign(viewshed_t{2})
				->assign(despair_attack_t{{
					{ "says \"Do you work here? I didn't recognize you, but we get through so many people.\"", 1 },
					{ "says \"One sec, I'll help you as soon as I finish this level.\"", 1 },
					{ "says \"I'm sure I'll find you in the database eventually.\"", 1 },
					{ "says \"Welcome to WidgetCorp. I'm sure one of the others can help you\"", 1 },
					{ "says \"Maybe you can tell me why my cat pictures are loading so slowly?\"", 1 }
				}});
		} break;
		case 3 : {
			create_entity()->assign(renderable_t{272, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Flirty Receptionist"})
				->assign(static_ai{})
				->assign(viewshed_t{2})
				->assign(despair_attack_t{{
					{ "says \"When you're older, you should give me your number.\"", 1 },
					{ "says \"Why is this dating site loading so slowly?\"", 1 },
					{ "says \"Did you block my Facebook again?\"", 1 },
					{ "says \"Hey handsome. Look me up some time, if they ever let you out of here!\"", 1 }
				}});
		} break;
		case 4 : {
			create_entity()->assign(renderable_t{273, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Ancient Receptionist"})
				->assign(static_ai{})
				->assign(viewshed_t{2})
				->assign(despair_attack_t{{
					{ "says \"You remind me of my grandson. He worked in IT here, once. He moved onto a real job.\"", 1 },
					{ "randomly tells you a very long tale of woe involving multiple family members and a kitten.", 1 },
					{ "says \"Did you block my Facebook again?\"", 1 },
					{ "says \"Back in my day, we had customers!\"", 1 }
				}});
		} break;
	}
}

void spawn_npc(const uint8_t &type, const int &x, const int &y, const int &level) {
	switch (type) {
		case 'r' : {
			spawn_receptionist(x,y,level);
		} break;
		case 'g' : {
			create_entity()->assign(renderable_t{265, rltk::colors::WHITE})
				->assign(position_t{x,y,level})
				->assign(name_t{"Unnaturally Happy Greeter"})
				->assign(static_ai{})
				->assign(viewshed_t{2})
				->assign(despair_attack_t{{
					{ "chirps \"Welcome to WidgetCorp. I hope you enjoy your shopping experience!\"", 1 }
				}});
		} break;
		case 'v' : {
			create_entity()->assign(renderable_t{266, rltk::colors::WHITE})
				->assign(position_t{x,y,level})
				->assign(name_t{"Widget Vendor"})
				->assign(nuisance_ai{})
				->assign(viewshed_t{6})
				->assign(despair_attack_t{{
					{ "tries to sell you some Widgets.", 1 },
					{ "goes on a long spiel about the virtue of their latest project.", 1 },
					{ "doesn't seem to know what they are selling, but are trying really hard to sell it anyway.'", 1 },
				}});
		} break;
		case 'c' : {
			create_entity()->assign(renderable_t{267, rltk::colors::WHITE})
				->assign(position_t{x,y,level})
				->assign(name_t{"Annoyed Customer"})
				->assign(nuisance_ai{})
				->assign(viewshed_t{6})
				->assign(despair_attack_t{{
					{ "says \"I've been here an hour, you know!\"", 1 },
					{ "says \"You probably can't help me. Nobody can help me.\"", 1 },
					{ "says \"Your products are awful! Find me a manager!\"", 1 }
				}});
		} break;
		case 'G' : {
			create_entity()->assign(renderable_t{268, rltk::colors::WHITE})
				->assign(position_t{x,y,level})
				->assign(name_t{"Bearded UNIX Guru"})
				->assign(static_ai{})
				->assign(viewshed_t{5})
				->assign(despair_attack_t{{
					{ "says \"We wouldn't have these problems if we ran GNU/Linux.\"", 1 },
					{ "says \"Take it from me, kid. This Windows thing is a passing fad.\"", 1 },
					{ "says \"An iPad? You need to replace that with something open source!\"", 1 },
					{ "says \"I blame sunspots.\"", 1 },
					{ "says \"When you get a chance, replace all the routers with Vyatta.\"", 1 },
					{ "says \"Now Mel, he was a REAL programmer. We need more Mels.\"", 1 }
				}});
		} break;
		case 't' : {
			create_entity()->assign(renderable_t{269, rltk::colors::WHITE})
				->assign(position_t{x,y,level})
				->assign(name_t{"Tired IT Tech"})
				->assign(static_ai{})
				->assign(viewshed_t{3})
				->assign(despair_attack_t{{
					{ "says \"Have you tried turning it off and then back on again?\"", 1 }
				}});
		} break;
		case ' ' : {} break;
		default : {
			std::cout << "Unknown REX entity: " << +type << "\n";
		}
	}
}

void add_coffee_machine(const int &x, const int &y, const int &z, map_t &map) {
	const int idx = mapidx(x,y,z);
	map.tile_type[idx] = tiles::FLOOR;
	create_entity()->assign(renderable_t{264, rltk::colors::WHITE})
		->assign(position_t{x,y,z})
		->assign(name_t{"Coffee Machine"})
		->assign(coffee_machine{})
		->assign(blocker_t{});
}

void set_map_tile(const vchar &c, const int &x, const int &y, const int &z, map_t &map) {
	const int idx = mapidx(x,y,z);
	switch (c.glyph) {
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
			create_entity()->assign(renderable_t{274, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Office Chair"});
		} break;
		case 203 : {
			// Table
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{275, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Office Table"})
				->assign(blocker_t{});
		} break;
		case 127 : {
			// Toilet
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{276, rltk::colors::WHITE})
			->assign(position_t{x,y,z})
			->assign(name_t{"Toilet"});
		} break;
		case 202 : {
			// Sink
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{277, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Sink"})
				->assign(blocker_t{});
		} break;
		case 167 : {
			// Coffee Station
			add_coffee_machine(x,y,z,map);
		} break;
		case 255 : {
			// Computer
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{278, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Work Computer"})
				->assign(computer_t{})
				->assign(blocker_t{});
		} break;
		case 254 : {
			// Server
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{279, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Windows Server"})
				->assign(server_t{})
				->assign(blocker_t{});
		} break;
		case 175 : {
			// Switch
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{280, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Expensive Router"})
				->assign(switch_t{})
				->assign(blocker_t{});
		} break;
		case 158 : {
			// Printer
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{281, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Printer"})
				->assign(printer_t{})
				->assign(blocker_t{});
		} break;
		case 'P' : {
			// Printer Supplies
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{282, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Printer Supplies"})
				->assign(blocker_t{});
		} break;
		case 'C' : {
			// Computer Supplies
			map.tile_type[idx] = tiles::FLOOR;
			create_entity()->assign(renderable_t{283, rltk::colors::WHITE})
				->assign(position_t{x,y,z})
				->assign(name_t{"Computer Parts"})
				->assign(blocker_t{});
		} break;
		default  : {
			map.tile_type[idx] = tiles::WALL;
			std::cout << "Unknown REX char: " << +c.glyph << "\n"; 
		} break;
	}
}

void build_lobby(map_t &map) {
	xp::rex_sprite lobby("assets/lobby.xp");
	for (int y=0; y<MAP_HEIGHT; ++y) {
		for (int x=0; x<MAP_WIDTH; ++x) {
			const vchar * c = lobby.get_tile(0,x,y);
			const int idx = mapidx(x,y,3);

			// Tiles
			set_map_tile(*c, x, y, 3, map);

			// Spawners
			const vchar * spawner = lobby.get_tile(1,x,y);
			spawn_npc(spawner->glyph, x, y, 3);
		}
	}
}

void fill_all_except_stair_circle(map_t &map, const int &level) {
	for (int y=0; y<MAP_HEIGHT; ++y) {
		for (int x=0; x<MAP_WIDTH; ++x) {
			const float distance = distance2d(x,y, MAP_WIDTH/2, MAP_HEIGHT/2);
			if (distance > 5.0F) map.tile_type[mapidx(x,y,level)] = tiles::WALL;
		}
	}
}

void build_rnd_caverns(map_t &map) {
	xp::rex_sprite lobby("assets/researchlab.xp");
	for (int y=0; y<MAP_HEIGHT; ++y) {
		for (int x=0; x<MAP_WIDTH; ++x) {
			const vchar * c = lobby.get_tile(0,x,y);
			const int idx = mapidx(x,y,0);

			// Tiles
			set_map_tile(*c, x, y, 0, map);

			// Spawners
			const vchar * spawner = lobby.get_tile(1,x,y);
			spawn_npc(spawner->glyph, x, y, 0);
		}
	}
}

void build_facilities_caverns(map_t &map) {
	// Start by filling in the whole thing except a circle around the stairs
	fill_all_except_stair_circle(map, 1);
	add_coffee_machine(MAP_WIDTH/2, MAP_HEIGHT/2, 1, map);
}

void build_it_caverns(map_t &map) {
	xp::rex_sprite lobby("assets/itcave.xp");
	for (int y=0; y<MAP_HEIGHT; ++y) {
		for (int x=0; x<MAP_WIDTH; ++x) {
			const vchar * c = lobby.get_tile(0,x,y);
			const int idx = mapidx(x,y,2);

			// Tiles
			set_map_tile(*c, x, y, 2, map);

			// Spawners
			const vchar * spawner = lobby.get_tile(1,x,y);
			spawn_npc(spawner->glyph, x, y, 2);
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
	build_rnd_caverns(map);
	build_facilities_caverns(map);
	build_it_caverns(map);
	build_lobby(map);

	// Walkability
	map.calculate_walkability();

	create_entity()->assign(std::move(map));
	create_entity()->assign(position_t{MAP_WIDTH/2, MAP_HEIGHT-3, 3})
		->assign(player_t{})
		->assign(renderable_t{})
		->assign(viewshed_t{8, true})
		->assign(logger_t{})
        ->assign(available_missions_t{});
}

bool has_initialized = false;

void game_mode::on_init() {
    if (!has_initialized) {
        quitting = false;

        add_system<time_system>();
        add_system<mission_system>();
        add_system<blocking_system>();
        add_system<keyboard_system>();
        add_system<ai_system>();
        add_system<movement_system>();
        add_system<caffeine_system>();
        add_system<despair_system>();
        add_system<visibility_system>();
        add_system<render_system>();
        add_system<hud_system>();
        add_system<log_system>();
        ecs_configure();

        if (!loading) {
            build_game();
        } else {
            std::unique_ptr<std::ifstream> lbfile = std::make_unique<std::ifstream>(filename, std::ios::in | std::ios::binary);
            ecs_load(std::move(lbfile), component_loader_xml);
            if (boost::filesystem::exists(filename)) boost::filesystem::remove(filename);
        }

        has_initialized = true;
    }
}

void game_mode::on_exit() {
	// ECS stop
	delete_all_entities();
    delete_all_systems();
    ecs_garbage_collect();
    has_initialized = false;
}

tick_result_t game_mode::tick(const double ms) {
	ecs_tick(ms);
	ecs_garbage_collect();

	if (quitting) {
		switch (quit_reason) {
		case QUIT : return POP;
		case CAFFEINE_FAIL : return POP_NO_CAFFEINE;
		case DESPAIR_FAIL : return POP_NO_HOPE;
		case TABLET : { quitting = false; return PUSH_TABLET; }
        case SAVEQUIT : {
            const std::string save_filename = "savegame.dat";
            if (boost::filesystem::exists(save_filename)) boost::filesystem::remove(save_filename);
            std::unique_ptr<std::ofstream> lbfile = std::make_unique<std::ofstream>(save_filename, std::ios::out | std::ios::binary);
            ecs_save(std::move(lbfile));
            return POP;
        }
        case WINGAME : {
            const std::string save_filename = "savegame.dat";
            if (boost::filesystem::exists(save_filename)) boost::filesystem::remove(save_filename);
            return POP_WIN_GAME;
        }
		}
	} else {
		return CONTINUE;
	}
}

