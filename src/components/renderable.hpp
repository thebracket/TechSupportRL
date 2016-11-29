#pragma once

#include <rltk.hpp>

struct renderable_t {
    std::string xml_identity = "renderable_t";
    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                               std::make_pair("glyph", glyph),
                               std::make_pair("color", color)
        );
    }
    void from_xml(rltk::xml_node * c) {
        glyph = c->val<uint16_t>("glyph");
        color = c->color("color");
    }

    uint16_t glyph = '@';
    rltk::color_t color = rltk::colors::YELLOW;

    renderable_t() {}
    renderable_t(const uint16_t &g, const rltk::color_t &c) : glyph(g), color(c) {}
};