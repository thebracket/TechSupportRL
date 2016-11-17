#pragma once

enum gait_t { SNEAKING, WALKING };

struct player_t {
	uint8_t health = 10;
	uint8_t despair = 10;
	uint8_t cost_savings = 0;
	uint8_t level = 0;
	uint8_t caffeine = 101;
	gait_t gait = WALKING;

	player_t() {}
};
