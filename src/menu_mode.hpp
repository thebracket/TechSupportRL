#pragma once
#include "base_mode.hpp"
#include <string>
#include <vector>

struct menu_mode : public base_mode {
	virtual tick_result_t tick(const double ms) override final;
private:
	bool save_exists() const;
	bool save_exists_cache = false;
	bool first_run = true;
	const std::vector<std::string> options { "Continue where you left off", "Start a new game", "Quit back to real-life" };
	int selection = 0;
	double key_delay = 5.0;
	const double KEY_PAUSE = 50.0;
};
