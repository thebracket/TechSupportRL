#pragma once

struct computer_t {
    std::string xml_identity = "computer_t";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};