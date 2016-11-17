#include "ai_system.hpp"
#include "../components/components.hpp"
#include "../globals.hpp"

using namespace rltk;

void ai_system::configure() {
    system_name = "AI System";
    subscribe_mbox<tick_message>();
}

void ai_system::update(const double ms) {
    if (waiting_input) return;

    std::queue<tick_message> * ticks = mbox<tick_message>();
    while (!ticks->empty()) {
        ticks->pop();

        position_t * player_pos;
        each<player_t, position_t>([&player_pos] (entity_t &e, player_t &p, position_t &pos) { player_pos = &pos; });
        const int idx = mapidx(player_pos->x, player_pos->y, player_pos->level);

        each<static_ai, viewshed_t, despair_attack_t>([&player_pos, &idx] (entity_t &e, static_ai &ai, viewshed_t &view, despair_attack_t &attack) {
            if (ai.initiative < 1) {
                for (const int &loc : view.visible_tiles) {
                    if (loc == idx) {
                        // Attack!
                        int id = rng.roll_dice(1, attack.attack_types.size())-1;
                        if (attack.attack_types.size()==1) id = 0;
                        const std::string message = attack.attack_types[id].first;
                        const int damage = attack.attack_types[id].second;
                        emit(inflict_despair{message, damage, e.id});
                    }
                }
                ai.initiative = rng.roll_dice(1,4);
            } else {
                ai.initiative--;
            }
        });

        each<nuisance_ai, viewshed_t, despair_attack_t>([&player_pos, &idx] (entity_t &e, nuisance_ai &ai, viewshed_t &view, despair_attack_t &attack) {
            if (ai.initiative < 1) {
                bool attacked = false;
                for (const int &loc : view.visible_tiles) {
                    if (loc == idx) {
                        // Attack!
                        int id = rng.roll_dice(1, attack.attack_types.size())-1;
                        if (attack.attack_types.size()==1) id = 0;
                        const std::string message = attack.attack_types[id].first;
                        const int damage = attack.attack_types[id].second;
                        emit(inflict_despair{message, damage, e.id});
                        attacked = true;
                    }
                }

                if (!attacked) {
                    if (rng.roll_dice(1,10)<5) emit_deferred(entity_wants_to_move_randomly{e.id});
                }
                ai.initiative = rng.roll_dice(1,4);
            } else {
                ai.initiative--;
            }
        });
    }
}
