#pragma once

#include <vector>
#include <utility>
#include <string>

struct despair_attack_t {
    despair_attack_t() {}
    despair_attack_t(std::vector<std::pair<std::string, int>> attacks) : attack_types(attacks) {}

    std::vector<std::pair<std::string, int>> attack_types;
};