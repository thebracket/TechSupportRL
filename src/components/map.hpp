#pragma once

#include "position.hpp"
#include <vector>
#include <algorithm>

constexpr int MAP_WIDTH = 80;
constexpr int MAP_HEIGHT = 40;
constexpr int MAP_DEPTH = 10;
constexpr int MAP_TILES_COUNT = MAP_WIDTH * MAP_HEIGHT * MAP_DEPTH;

namespace tiles {

constexpr uint16_t FLOOR = 0;
constexpr uint16_t WALL = 1;
constexpr uint16_t UP = 2;
constexpr uint16_t DOWN = 3;
constexpr uint16_t GRASS = 4;
constexpr uint16_t PATH = 5;
constexpr uint16_t FREEDOM = 6;
constexpr uint16_t GLASS_DOOR = 7;

}

constexpr int mapidx(const int x, const int y, const int z) {
        return (z * MAP_HEIGHT * MAP_WIDTH) + (y * MAP_WIDTH) + x;
}

inline int mapidx(const position_t &pos) {
        return mapidx(pos.x, pos.y, pos.level);
}

struct map_t {
	std::vector<uint16_t> tile_type;
	std::vector<bool> solid;

	std::vector<std::string> layer_names = {
		"Research & Development Caverns",
		"Facilities & Security",
		"The IT Cave",
		"Surprisingly Nice Lobby",
		"Call-Center of Despair",
		"S&M",
		"Privacy Avoiding Open-Plan Workspace",
		"Junior Management",
		"Upper Management",
		"Temple of the CEO"
	};

	map_t() {
		tile_type.resize(MAP_TILES_COUNT);
		solid.resize(MAP_TILES_COUNT);
		std::fill(tile_type.begin(), tile_type.end(), 0);
		std::fill(solid.begin(), solid.end(), false);
	}

	void calculate_walkability() {
		for (std::size_t i=0; i<MAP_TILES_COUNT; ++i) {
			bool is_solid = true;
			if (tile_type[i] == tiles::FLOOR) is_solid = false;
			if (tile_type[i] == tiles::UP) is_solid = false;
			if (tile_type[i] == tiles::DOWN) is_solid = false;
			if (tile_type[i] == tiles::GRASS) is_solid = false;
			if (tile_type[i] == tiles::PATH) is_solid = false;
			if (tile_type[i] == tiles::GLASS_DOOR) is_solid = false;
			solid[i] = is_solid; 
		}
	}	
};