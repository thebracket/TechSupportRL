#pragma once

#include <rltk.hpp>

struct movement_system : public rltk::base_system {
    virtual void configure() override final;
    virtual void update(const double ms) override final;
};
