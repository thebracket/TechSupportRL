#include "time_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"

using namespace rltk;

const double frame_time_ms = 33.0;
const double slow_frame_time_ms = 100.0;

void time_system::configure() {
    system_name = "Time System";
    subscribe_mbox<player_performed_action>();
}

void time_system::update(const double ms) {
    if (first_turn) {
        first_turn = false;
        emit_deferred(player_performed_action{});
    }

    time_accumulator += ms;
    if (time_accumulator > frame_time_ms) {
        emit_deferred(tick_message{});
        time_accumulator = 0.0;
    }
    slow_accumulator += ms;
    if (slow_accumulator > slow_frame_time_ms) {
        emit_deferred(slow_tick_message{});
        slow_accumulator = 0.0;
    }
}