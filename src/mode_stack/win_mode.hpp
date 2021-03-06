#pragma once

#include "base_mode.hpp"
#include <iostream>

struct win_mode : public base_mode {
    virtual void on_init() override final;
    virtual void on_exit() override final;

    virtual tick_result_t tick(const double ms) override final;
};
