#include "hud_system.hpp"
#include "../components/components.hpp"

using namespace rltk;

constexpr int GUI_HEALTH = 1;
constexpr int GUI_CAFFEINE = 2;
constexpr int GUI_DESPAIR = 3;
constexpr int GUI_SAVINGS = 4;
constexpr int GUI_LEVEL = 5;
constexpr int GUI_GAIT = 6;
constexpr int GUI_DRINK = 7;

void hud_system::configure() {
    system_name = "HUD System";
    layer(2)->add_hbar(GUI_HEALTH, 1, 2, 24, 0, 10, 10, rltk::colors::DARK_RED, rltk::colors::LIGHT_RED, 
            rltk::colors::DARKEST_GREY, rltk::colors::LIGHT_GREY, rltk::colors::WHITE, "Health ");
    layer(2)->add_hbar(GUI_CAFFEINE, 1, 3, 24, 0, 100, 100, rltk::colors::RED, rltk::colors::GREEN, 
            rltk::colors::DARKEST_GREY, rltk::colors::LIGHT_GREY, rltk::colors::WHITE, "Caffeine ");

    layer(2)->add_hbar(GUI_DESPAIR, 1, 4, 24, 0, 10, 10, rltk::colors::BLUE, rltk::colors::GREEN, 
            rltk::colors::DARKEST_GREY, rltk::colors::LIGHT_GREY, rltk::colors::WHITE, "Hope ");

    layer(2)->add_hbar(GUI_SAVINGS, 1, 5, 24, 0, 10, 10, rltk::colors::DARK_GREEN, rltk::colors::LIGHT_GREEN, 
            rltk::colors::DARKEST_GREY, rltk::colors::LIGHT_GREY, rltk::colors::WHITE, "$ Saved ");
    layer(2)->add_static_text(GUI_GAIT, 1, 6, "Placeholder", rltk::colors::WHITE, rltk::colors::BLACK);
    layer(2)->add_static_text(GUI_DRINK, 1, 7, "", rltk::colors::WHITE, rltk::colors::BLACK);

    layer(2)->add_static_text(GUI_LEVEL, 1, 9, "Placeholder", rltk::colors::WHITE, rltk::colors::BLACK);
}

void hud_system::update(const double ms) {
    term(2)->clear();
    term(2)->box(0, 0, 25, term(2)->term_height-12, rltk::colors::DARK_GREY);
    term(2)->box(0, term(2)->term_height-11, term(2)->term_width-1, 10, rltk::colors::DARK_GREY);
    
    each<player_t, position_t>([] (entity_t &e, player_t &p, position_t &pos) {
        layer(2)->control<gui_hbar_t>(GUI_HEALTH)->value = p.health;
        layer(2)->control<gui_hbar_t>(GUI_CAFFEINE)->value = p.caffeine;
        layer(2)->control<gui_hbar_t>(GUI_DESPAIR)->value = p.despair;
        layer(2)->control<gui_hbar_t>(GUI_SAVINGS)->value = p.cost_savings;

        switch (p.level) {
            case 0 : layer(2)->control<gui_static_text_t>(GUI_LEVEL)->text = "(0) Fresh-Faced Intern"; break;
        }

        switch (p.gait) {
            case SNEAKING : layer(2)->control<gui_static_text_t>(GUI_GAIT)->text = "(G) - Sneaking"; break;
            case WALKING : layer(2)->control<gui_static_text_t>(GUI_GAIT)->text = "(G) - Walking"; break;
        }

        each<map_t>([&pos] (entity_t &ent, map_t &map) {
            term(2)->print_center(0, map.layer_names[pos.level]);
            each<player_t, position_t>([&map] (entity_t &ignore, player_t &player, position_t &pos) {
                const int idx = mapidx(pos.x, pos.y, pos.level);
                if (map.has_coffee[idx]) {
                    layer(2)->control<gui_static_text_t>(GUI_DRINK)->text = "(D) Drink Coffee";
                } else {
                    layer(2)->control<gui_static_text_t>(GUI_DRINK)->text = "No Coffee Here";
                }
            });
        });
    });
}