#pragma once

struct nuisance_ai {
    std::string xml_identity = "nuisance_ai";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}

    nuisance_ai() {}
};
