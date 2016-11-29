#pragma once

#include <vector>
#include <utility>
#include <string>

struct despair_attack_t {
    std::string xml_identity = "despair_attack_t";

    despair_attack_t() {}
    despair_attack_t(std::vector<std::pair<std::string, int>> attacks) : attack_types(attacks) {}

    std::vector<std::pair<std::string, int>> attack_types;

    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                         std::make_pair("attackTypes", attack_types)
        );
    }

    void from_xml(rltk::xml_node * c) {
        attack_types.clear();
        c->iterate_child("attackTypes", [this] (rltk::xml_node * ch) {
            std::string msg = ch->find("attackTypes_first")->val<std::string>("attackTypes");
            std::cout << msg << "\n";
            int damage = ch->find("attackTypes_second")->val<int>("attackTypes");
            attack_types.push_back(std::make_pair(msg, damage));
        });
    }

};