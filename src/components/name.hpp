#pragma once

#include <string>

struct name_t {
    std::string name = "";
    name_t() {}
    name_t(const std::string &n) : name(n) {}
};