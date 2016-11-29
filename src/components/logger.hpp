#pragma once

#include <rltk.hpp>
#include "name.hpp"

struct log_line_t {
    log_line_t() {}
    log_line_t(std::vector<rltk::vchar> new_chars) : chars(new_chars) {}

    std::vector<rltk::vchar> chars;
    int age = 0;

    void to_xml(rltk::xml_node * c) {
        //rltk::component_to_xml(c, chars);
        //rltk::component_to_xml(c, age);
    }

    void from_xml(rltk::xml_node * c) {}
};

struct logger_t {
    std::string xml_identity = "logger_t";
	logger_t() {}
    std::vector<log_line_t> lines;

    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c, std::make_pair("lines", lines));
    }

    void from_xml(rltk::xml_node * c) {}
};

struct LOG {
    std::vector<rltk::vchar> chars;
    rltk::color_t fg = rltk::colors::WHITE;

    LOG * text(const std::string &txt);
    inline LOG * col(const rltk::color_t &col) { fg = col; return this; }
    LOG * name(const std::size_t &entity_id);
};
