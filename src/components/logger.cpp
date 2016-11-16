#include "logger.hpp"

using namespace rltk;

LOG * LOG::text(const std::string &txt) {
    for (std::size_t i=0; i<txt.size(); ++i) {
        chars.push_back(rltk::vchar{ txt[i], fg, rltk::colors::BLACK });
    }
    return this;
}

inline boost::optional<name_t &> get_name_component(const std::size_t &entity_id) {
    auto e = entity(entity_id);
    if (e) {
        auto name = e->component<name_t>();
        if (name) {
            return name;
        }
    }
    return boost::optional<name_t &>();
}

LOG * LOG::name(const std::size_t &entity_id) {
    col(rltk::colors::MAGENTA);
    text(get_name_component(entity_id)->name);
    col(rltk::colors::WHITE);
    return this;
}
