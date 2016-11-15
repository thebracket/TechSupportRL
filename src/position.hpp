#pragma once

struct position_t {
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t level = 0;

	position_t() {}
	position_t(const uint8_t &X, const uint8_t &Y, const uint8_t &l) : x(X), y(Y), level(l) {}
};

