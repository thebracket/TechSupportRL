#include "caffeine_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"
#include <rltk.hpp>

using namespace rltk;

void caffeine_system::configure() {
    system_name = "Caffeine System";
    subscribe_mbox<player_performed_action>();
}

void caffeine_system::update(const double ms) {
    std::queue<player_performed_action> * actions = mbox<player_performed_action>();
    while (!actions->empty()) {
        actions->pop();

        each<player_t>([] (entity_t &e, player_t &p) {
            if (p.caffeine > 0) {
                --p.caffeine;
            } else {
                quitting = true;
                quit_reason = CAFFEINE_FAIL;
            }
        });
    }
}