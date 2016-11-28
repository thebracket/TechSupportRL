#pragma once

enum tick_result_t { CONTINUE, POP, PUSH_NEW_GAME, POP_NO_CAFFEINE, POP_NO_HOPE, PUSH_TABLET  };

struct base_mode {
	virtual void on_init()=0;
	virtual void on_exit()=0;
	virtual tick_result_t tick(const double ms)=0;
};
