#pragma once

enum quit_reason_t {QUIT, CAFFEINE_FAIL};

extern bool quitting;
extern bool waiting_input;
extern quit_reason_t quit_reason;
