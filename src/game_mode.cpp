#include "game_mode.hpp"
#include "globals.hpp"
#include <rltk.hpp>
#include "render_system.hpp"
#include "components.hpp"

using namespace rltk;

void game_mode::build_game() {
	create_entity()->assign(map_t{});
	create_entity()->assign(position_t{MAP_WIDTH/2, MAP_HEIGHT/2, 1})->assign(player_t{});
}

void game_mode::on_init() {
	quitting = false;

	add_system<render_system>();
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
		return POP;
	} else {
		return CONTINUE;
	}
}

