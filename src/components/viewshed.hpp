#pragma once

#include <boost/container/flat_set.hpp>

struct viewshed_t {
    uint8_t range = 4;
    bool good_guy = false;
    boost::container::flat_set<int> visible_tiles;

    viewshed_t() {}
    viewshed_t(const uint8_t rng) : range(rng) {};
    viewshed_t(const uint8_t rng, const bool goodguy) : range(rng), good_guy(goodguy) {}
};
