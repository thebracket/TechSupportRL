#pragma once

#include "available_missions.hpp"

struct mission_t {
    mission_t() {}
    mission_t(const available_mission_t &m) {
        title = m.title;
        description = m.description;
        destination_id = m.destination_id;
        mission_type = m.mission_type;
        x = m.x;
        y = m.y;
        z = m.z;
    }

    std::string title = "";
    std::string description = "";
    std::size_t destination_id = 0;
    mission_type_t mission_type;
    int x,y,z;
};