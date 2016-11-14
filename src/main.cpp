#include <iostream>
#include <rltk.hpp>

using namespace rltk;

void tick(double duration_ms) {
	console->clear();
    console->print(1,1, "Hello World");
}

int main() {
    init(config_simple("../assets", 80, 50, "RLTK Hello World", "8x8"));
    run(tick);
    return 0;
}