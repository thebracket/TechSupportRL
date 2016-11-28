#pragma once

#include <boost/container/flat_set.hpp>

struct viewshed_t {
    std::string xml_identity = "viewshed_t";
    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                               std::make_pair("range", range),
                               std::make_pair("goodGuy", good_guy),
                               std::make_pair("visible_tiles", visible_tiles)
        );
    }
    void from_xml(rltk::xml_node * c) {
        range = c->val<uint8_t>("range");
        good_guy = c->val<bool>("goodGuy");
        visible_tiles.clear();
        c->find("visible_tiles")->iterate_child("key", [this] (rltk::xml_node *ch) {
            int tile = ch->val<int>("k");
            visible_tiles.insert(tile);
        });
    }

    uint8_t range = 4;
    bool good_guy = false;
    boost::container::flat_set<int> visible_tiles;

    viewshed_t() {}
    viewshed_t(const uint8_t rng) : range(rng) {};
    viewshed_t(const uint8_t rng, const bool goodguy) : range(rng), good_guy(goodguy) {}
};
