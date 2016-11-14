#include <iostream>
#include <rltk.hpp>

using namespace rltk;

void tick(double duration_ms) {
	term(2)->clear();
    term(2)->print(1,1, "Hello World");
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
    run(tick);
    return 0;
}