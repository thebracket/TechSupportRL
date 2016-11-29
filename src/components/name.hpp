#pragma once

#include <string>

struct name_t {
    std::string xml_identity = "name_t";
    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c, std::make_pair("name", name) );
    }
    void from_xml(rltk::xml_node * c) {
        name = c->val<std::string>("name");
    }

    std::string name = "";
    name_t() {}
    name_t(const std::string &n) : name(n) {}
};