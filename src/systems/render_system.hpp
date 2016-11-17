#pragma once

#include <rltk.hpp>

struct render_system : public rltk::base_system {
	virtual void configure() override final;
	virtual void update(const double ms) override final;
private:
	uint32_t ticker=0;
};

