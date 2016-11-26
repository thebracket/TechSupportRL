#pragma once

#include <rltk.hpp>
#include "path_finding.hpp"

struct render_system : public rltk::base_system {
	virtual void configure() override final;
	virtual void update(const double ms) override final;
private:
	uint32_t ticker=0;
    std::shared_ptr<rltk::navigation_path<position_t>> path_to_mission;
};

