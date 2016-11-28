#pragma once

struct switch_t {
    std::string xml_identity = "switch_t";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};
