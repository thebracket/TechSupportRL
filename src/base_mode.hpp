#pragma once

enum tick_result_t { CONTINUE, POP  };

struct base_mode {
	virtual tick_result_t tick(const double ms)=0;
};
