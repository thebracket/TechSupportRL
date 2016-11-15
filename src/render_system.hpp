#pragma once

#include <rltk.hpp>
#include "globals.hpp"

struct render_system : public rltk::base_system {
	void configure() override final;
	void update(const double ms) override final;
};

