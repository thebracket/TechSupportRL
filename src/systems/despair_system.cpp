#include "despair_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"

using namespace rltk;

void despair_system::configure() {
    system_name = "Despair System";
    subscribe_mbox<inflict_despair>();
}

void despair_system::update(const double ms) {
    std::queue<inflict_despair> * despair_queue = mbox<inflict_despair>();
    while (!despair_queue->empty()) {
        inflict_despair msg = despair_queue->front();
        despair_queue->pop();

        player_t * player;
        each<player_t>([&player] (entity_t &e, player_t &p) { player = &p; });

        emit(log_message{LOG().name(msg.aggressor)->text(" ")->text(msg.message)->col(rltk::colors::BLUE)->text(" You lose hope.")->chars});

        for (int i=0; i<msg.damage; ++i) {
            if (player->despair > 0) --player->despair;
        }
        if (player->despair < 1) {
            quitting = true;
            quit_reason = DESPAIR_FAIL;
        }
    }
}
