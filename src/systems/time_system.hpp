#pragma once

#include <rltk.hpp>

struct time_system : public rltk::base_system {
    virtual void configure() override final;
    virtual void update(const double ms) override final;
private:
    double time_accumulator = 0.0;
};
