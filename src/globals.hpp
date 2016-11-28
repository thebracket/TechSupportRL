#pragma once

#include <rltk.hpp>

enum quit_reason_t {QUIT, CAFFEINE_FAIL, DESPAIR_FAIL, TABLET, WINGAME, SAVEQUIT};

extern bool quitting;
extern bool waiting_input;
extern quit_reason_t quit_reason;
extern rltk::random_number_generator rng;
extern bool show_path;
