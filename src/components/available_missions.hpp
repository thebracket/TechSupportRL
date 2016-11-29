#pragma once

#include <string>
#include <vector>
#include <boost/container/flat_set.hpp>
#include <rltk.hpp>

enum mission_type_t { FIX_COMPUTER, FIX_PRINTER, FIX_SERVER, FIX_ROUTER };

struct available_mission_t {
    available_mission_t() {}

    std::string title = "";
    std::string description = "";
    std::string resolution = "";
    std::size_t destination_id = 0;
    mission_type_t mission_type;
    int x,y,z;

    void to_xml(rltk::xml_node * c) {
        component_to_xml(c,
                         std::make_pair("title", title),
                         std::make_pair("description", description),
                         std::make_pair("resolution", resolution),
                         std::make_pair("destinationId", destination_id),
                         std::make_pair("missionType", mission_type),
                         std::make_pair("x", x),
                         std::make_pair("y", y),
                         std::make_pair("z", z)
        );
    }

    void from_xml(rltk::xml_node * c) {
        title = c->val<std::string>("title");
        description = c->val<std::string>("description");
        resolution = c->val<std::string>("resolution");
        destination_id = c->val<std::size_t>("destinationId");
        mission_type = (mission_type_t)c->val<int>("missionType");
        x = c->val<int>("x");
        y = c->val<int>("y");
        z = c->val<int>("z");
    }
};

struct available_missions_t {
    available_missions_t() {}

    std::vector<available_mission_t> available_missions;
    boost::container::flat_set<std::size_t> fixed_systems;

    std::string xml_identity = "available_missions_t";

    void to_xml(rltk::xml_node * c) {
        component_to_xml(c,
                         std::make_pair("availableMissions", available_missions),
                         std::make_pair("fixed_systems", fixed_systems)
        );
    }

    void from_xml(rltk::xml_node * c) {
        available_missions.clear();
        fixed_systems.clear();
        c->iterate_child("availableMissions", [this] (rltk::xml_node *ch) {
            available_mission_t m;
            m.from_xml(ch);
            available_missions.push_back(m);
        });
        //c->iterate_child("fixed_systems")
    }
};
