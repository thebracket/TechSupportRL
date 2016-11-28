#include <iostream>
#include <stack>
#include <memory>
#include <rltk.hpp>
#include "mode_stack/base_mode.hpp"
#include "mode_stack/menu_mode.hpp"
#include "mode_stack/intro_mode.hpp"
#include "mode_stack/game_mode.hpp"
#include "mode_stack/dead_mode.hpp"
#include "mode_stack/tablet_mode.hpp"

using namespace rltk;

std::stack<std::unique_ptr<base_mode>> mode_stack;

void tick(double duration_ms) {
	auto result = mode_stack.top()->tick(duration_ms);
	if (result == POP) {
		mode_stack.top()->on_exit();
		mode_stack.pop();
		if (mode_stack.empty()) {
			get_window()->close();
		} else {
			mode_stack.top()->on_init();
		}
	} else if (result == PUSH_NEW_GAME) {
		mode_stack.emplace(std::make_unique<game_mode>());
		mode_stack.emplace(std::make_unique<intro_mode>());
		mode_stack.top()->on_init();
    } else if (result == PUSH_LOAD_GAME) {
        mode_stack.emplace(std::make_unique<game_mode>("savegame.dat"));
        mode_stack.top()->on_init();
	} else if (result == POP_NO_CAFFEINE) {
		mode_stack.top()->on_exit();
		mode_stack.pop();
		mode_stack.emplace(std::make_unique<dead_mode>());
	} else if (result == POP_NO_HOPE) {
		mode_stack.top()->on_exit();
		mode_stack.pop();
		mode_stack.emplace(std::make_unique<dead_mode>());
	} else if (result == PUSH_TABLET) {
		mode_stack.emplace(std::make_unique<tablet_mode>());
	}
}

void resize_map(layer_t * l, int w, int h) {
	// Use the whole window
	l->w = w;
	l->h = h;
}

int main() {
    init(config_advanced("assets", 1020, 768, "Tech Support - The Roguelike", false));
    gui->add_layer(1, 0, 0, 1024, 768, "16x16", resize_map, true);
    gui->add_layer(2, 0, 0, 1024, 768, "8x16", resize_map);
    mode_stack.emplace(std::make_unique<menu_mode>());
    mode_stack.top()->on_init();
    run(tick);
    return 0;
}
