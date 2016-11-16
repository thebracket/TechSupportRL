#include "time_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"

using namespace rltk;

const double frame_time_ms = 33.0;

void time_system::configure() {
    system_name = "Time System";
    subscribe_mbox<player_performed_action>();
}

void time_system::update(const double ms) {
    if (first_turn) {
        first_turn = false;
        emit(player_performed_action{});
    }

    if (!waiting_input) {
        time_accumulator += ms;
        if (time_accumulator > frame_time_ms) {
            emit(tick_message{});
            time_accumulator = 0.0;
        }
    }

    std::queue<player_performed_action> * actions = mbox<player_performed_action>();
    while (!actions->empty()) {
        actions->pop();
        each<player_t>([] (entity_t &e, player_t &p) {
            switch (p.gait) {
                case SNEAKING : p.initiative = rng.roll_dice(1,10)+3; break;
                case WALKING : p.initiative = rng.roll_dice(1,8)+2; break;
                case RUNNING : p.initiative = rng.roll_dice(1,6)+1; break;
            }
        } );
    }
}