#pragma once

#include "base_mode.hpp"
#include <iostream>
#include <string>

struct game_mode : public base_mode {

    game_mode() {}
    game_mode(const std::string &fn) {
        loading = true;
        filename = fn;
    }

	virtual void on_init() override final;
	virtual void on_exit() override final;

	virtual tick_result_t tick(const double ms) override final;

private:
    std::string filename = "";
	bool loading = false;
	void build_game();

};
