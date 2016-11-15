#pragma once

#include <rltk.hpp>

struct renderable_t {
    uint8_t glyph = '@';
    rltk::color_t color = rltk::colors::YELLOW;

    renderable_t() {}
    renderable_t(const uint8_t &g, const rltk::color_t &c) : glyph(g), color(c) {}
};