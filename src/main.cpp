#include <iostream>
#include <stack>
#include <memory>
#include <rltk.hpp>
#include "base_mode.hpp"
#include "menu_mode.hpp"

using namespace rltk;

std::stack<std::unique_ptr<base_mode>> mode_stack;

void tick(double duration_ms) {
	auto result = mode_stack.top()->tick(duration_ms);
	if (result == POP) {
		mode_stack.pop();
		if (mode_stack.empty()) {
			get_window()->close();
		}
	}
}

void resize_map(layer_t * l, int w, int h) {
	// Use the whole window
	l->w = w;
	l->h = h;
}

int main() {
    init(config_advanced("../assets", 1020, 768, "Tech Support - The Roguelike", false));
    gui->add_layer(1, 0, 0, 1024, 768, "16x16", resize_map);
    gui->add_layer(2, 0, 0, 1024, 768, "8x16", resize_map);
    mode_stack.emplace(std::make_unique<menu_mode>());
    run(tick);
    return 0;
}
