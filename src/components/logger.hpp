#pragma once

#include <rltk.hpp>
#include "name.hpp"

struct log_line_t {
    log_line_t() {}
    log_line_t(std::vector<rltk::vchar> new_chars) : chars(new_chars) {}

    std::vector<rltk::vchar> chars;
    int age = 0;
};

struct logger_t {
	logger_t() {}
    std::vector<log_line_t> lines;
};

struct LOG {
    std::vector<rltk::vchar> chars;
    rltk::color_t fg = rltk::colors::WHITE;

    LOG * text(const std::string &txt);
    inline LOG * col(const rltk::color_t &col) { fg = col; return this; }
    LOG * name(const std::size_t &entity_id);
};
