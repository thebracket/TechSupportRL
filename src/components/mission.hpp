#pragma once

#include "available_missions.hpp"

struct mission_t {
    std::string xml_identity = "mission_t";
    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                               std::make_pair("title", title),
                               std::make_pair("description", description),
                               std::make_pair("destination_id", destination_id),
                               std::make_pair("resolution", resolution),
                               std::make_pair("mission_type", mission_type),
                               std::make_pair("x", x),
                               std::make_pair("y", y),
                               std::make_pair("z", z)
        );
    }

    void from_xml(rltk::xml_node * c) {
        title = c->val<std::string>("title");
        description = c->val<std::string>("description");
        destination_id = c->val<std::size_t>("destination_id");
        resolution = c->val<std::string>("resolution");
        mission_type = (mission_type_t )c->val<int>("mission_type");
        x = c->val<int>("x");
        y = c->val<int>("y");
        z = c->val<int>("z");
    }

    mission_t() {}
    mission_t(const available_mission_t &m) {
        title = m.title;
        description = m.description;
        destination_id = m.destination_id;
        mission_type = m.mission_type;
        resolution = m.resolution;
        x = m.x;
        y = m.y;
        z = m.z;
    }

    std::string title = "";
    std::string description = "";
    std::size_t destination_id = 0;
    std::string resolution = "";
    mission_type_t mission_type;
    int x,y,z;
};