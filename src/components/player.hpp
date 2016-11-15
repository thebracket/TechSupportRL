#pragma once

struct player_t {
	uint8_t health = 10;
	uint8_t despair = 0;
	uint8_t cost_savings = 0;
	uint8_t level = 0;
	uint8_t caffeine = 100;

	player_t() {}
};
