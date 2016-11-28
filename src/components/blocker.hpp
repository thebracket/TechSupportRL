#pragma once

struct blocker_t{
    std::string xml_identity = "blocker_t";

    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};