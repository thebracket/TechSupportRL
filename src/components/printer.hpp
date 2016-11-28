#pragma once

struct printer_t {
    std::string xml_identity = "printer_t";
    void to_xml(rltk::xml_node * c) {}
    void from_xml(rltk::xml_node * c) {}
};