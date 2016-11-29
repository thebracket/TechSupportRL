#pragma once

struct server_t {
    std::string xml_identity = "server_t";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};