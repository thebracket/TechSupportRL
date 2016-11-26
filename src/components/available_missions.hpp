#pragma once

#include <string>
#include <vector>
#include <set>

enum mission_type_t { FIX_COMPUTER, FIX_PRINTER, FIX_SERVER, FIX_ROUTER };

struct available_mission_t {
    std::string title = "";
    std::string description = "";
    std::size_t destination_id = 0;
    mission_type_t mission_type;
    int x,y,z;
};

struct available_missions_t {
    std::vector<available_mission_t> available_missions;
    std::set<std::size_t> fixed_systems;
};
