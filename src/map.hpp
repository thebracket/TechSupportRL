#pragma once

#include "position.hpp"
#include <vector>
#include <algorithm>

constexpr int MAP_WIDTH = 80;
constexpr int MAP_HEIGHT = 40;
constexpr int MAP_DEPTH = 10;
constexpr int MAP_TILES_COUNT = MAP_WIDTH * MAP_HEIGHT * MAP_DEPTH;

constexpr int mapidx(const int x, const int y, const int z) {
        return (z * MAP_HEIGHT * MAP_WIDTH) + (y * MAP_WIDTH) + x;
}

inline int mapidx(const position_t &pos) {
        return mapidx(pos.x, pos.y, pos.level);
}

struct map_t {
	std::vector<uint16_t> tile_type;
	std::vector<bool> solid;

	map_t() {
		tile_type.resize(MAP_TILES_COUNT);
		solid.resize(MAP_TILES_COUNT);
		std::fill(tile_type.begin(), tile_type.end(), 0);
		std::fill(solid.begin(), solid.end(), false);
	}	
};
