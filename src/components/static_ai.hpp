#pragma once

struct static_ai {
    std::string xml_identity = "static_ai";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
    static_ai() {}
};
