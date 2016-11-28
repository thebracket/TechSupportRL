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
constexpr uint16_t WATER = 8;

}

constexpr int mapidx(const int x, const int y, const int z) {
        return (z * MAP_HEIGHT * MAP_WIDTH) + (y * MAP_WIDTH) + x;
}

inline int mapidx(const position_t &pos) {
        return mapidx(pos.x, pos.y, pos.level);
}

const std::vector<std::string> layer_names = {
		"Research & Development Caverns",
		"Facilities & Security Dungeon",
		"The IT Cave",
		"Surprisingly Nice Lobby",
		"Call-Center of Despair",
		"S&M",
		"Privacy Avoiding Open-Plan Workspace",
		"Junior Management",
		"Upper Management",
		"Temple of the CEO"
};

struct map_t {
    std::string xml_identity = "map_t";
    void to_xml(rltk::xml_node * c) {
        const std::string save_filename = "savegame.map";
        if (boost::filesystem::exists(save_filename)) boost::filesystem::remove(save_filename);
        std::unique_ptr<std::ofstream> lbfile = std::make_unique<std::ofstream>(save_filename, std::ios::out | std::ios::binary);
        // Save file
        rltk::serialize(*lbfile, tile_type);
        rltk::serialize(*lbfile, solid);
        rltk::serialize(*lbfile, visible);
        rltk::serialize(*lbfile, visible_baddie);
        rltk::serialize(*lbfile, has_coffee);
    }

    void from_xml(rltk::xml_node * c) {
        std::cout << "Loading a map\n";
        const std::string save_filename = "savegame.map";
        std::unique_ptr<std::ifstream> lbfile = std::make_unique<std::ifstream>(save_filename, std::ios::in | std::ios::binary);
        // Load file
        rltk::deserialize(*lbfile, tile_type);
        rltk::deserialize(*lbfile, solid);
        rltk::deserialize(*lbfile, visible);
        rltk::deserialize(*lbfile, visible_baddie);
        rltk::deserialize(*lbfile, has_coffee);
        if (boost::filesystem::exists(save_filename)) boost::filesystem::remove(save_filename);
    }

	std::vector<uint16_t> tile_type;
	std::vector<bool> solid;
	std::vector<bool> visible;
	std::vector<bool> visible_baddie;
	std::vector<bool> has_coffee;

	map_t() {
		tile_type.resize(MAP_TILES_COUNT);
		solid.resize(MAP_TILES_COUNT);
		visible.resize(MAP_TILES_COUNT);
		visible_baddie.resize(MAP_TILES_COUNT);
		has_coffee.resize(MAP_TILES_COUNT);
		std::fill(tile_type.begin(), tile_type.end(), 0);
		std::fill(solid.begin(), solid.end(), false);
		std::fill(visible.begin(), visible.end(), false);
		std::fill(visible_baddie.begin(), visible_baddie.end(), false);
		std::fill(has_coffee.begin(), has_coffee.end(), false);
	}

	void calculate_walkability() {
		std::fill(solid.begin(), solid.end(), false);
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

struct navigator_helper {
	static int get_x(const position_t &loc) { return loc.x; }
	static int get_y(const position_t &loc) { return loc.y; }
	static position_t get_xy(const int &x, const int &y) {
		return position_t{x,y,0}; 
	}
};
