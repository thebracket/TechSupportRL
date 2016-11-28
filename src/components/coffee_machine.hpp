#pragma once

struct coffee_machine {
    std::string xml_identity = "coffee_machine";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};
