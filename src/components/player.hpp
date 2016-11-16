#pragma once

enum gait_t { SNEAKING, WALKING, RUNNING };

struct player_t {
	uint8_t health = 10;
	uint8_t despair = 0;
	uint8_t cost_savings = 0;
	uint8_t level = 0;
	uint8_t caffeine = 100;
	int initiative = 0;
	gait_t gait = WALKING;

	player_t() {}
};
