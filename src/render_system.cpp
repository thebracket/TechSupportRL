#include "render_system.hpp"
#include "components.hpp"

using namespace rltk;

void render_system::configure() {
	system_name = "Render System";
}

void render_system::update(const double ms) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) quitting = true;

	term(1)->clear();
	term(2)->clear();
}
