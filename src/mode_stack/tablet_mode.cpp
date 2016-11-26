//
// Created by Herbert Wolverson on 11/25/16.
//

#include "tablet_mode.hpp"
#include "../components/mission.hpp"
#include "../components/components.hpp"
#include <rltk.hpp>

using namespace rltk;

void tablet_mode::on_init() {
}

void tablet_mode::on_exit() {
}

void select_mission(const available_mission_t &m, const std::size_t &player_id) {
    entity(player_id)->assign(mission_t{m});
    entity(player_id)->component<available_missions_t>()->available_missions.clear();
}

tick_result_t tablet_mode::tick(const double ms) {
    term(1)->clear();
    term(2)->clear();

    term(2)->print_center(5, "Welcome to WidgetCore OS 1.0", rltk::colors::YELLOW);
    term(2)->print_center(6, "Press ESCAPE to exit back to your job.");

    bool has_mission = false;
    mission_t * current_mission = nullptr;
    each<mission_t>([&current_mission, &has_mission] (entity_t &e, mission_t &m) {
        has_mission = true;
        current_mission = &m;
    });

    if (!has_mission) {
        term(2)->print_center(8, "Available Trouble Tickets", rltk::colors::YELLOW);
        term(2)->print_center(9, "Press the digit next to a trouble ticket to accept it");
        int n=1;
        int y=11;

        each<available_missions_t>([&n, &y] (entity_t &e, available_missions_t &m) {
           for (const available_mission_t &M : m.available_missions) {
               term(2)->print(25, y, std::string("[") + std::to_string(n) + std::string("]"), rltk::colors::YELLOW);
               term(2)->print(29, y, M.title, rltk::colors::MAGENTA);
               term(2)->print(29, y+1, std::string("Location: ")+layer_names[M.z]);

               if (n == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) select_mission(M, e.id);
               if (n == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) select_mission(M, e.id);
               if (n == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) select_mission(M, e.id);
               if (n == 4 && sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) select_mission(M, e.id);
               if (n == 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) select_mission(M, e.id);

               y+=3;
               ++n;
           }
        });

    } else {
        term(2)->print_center(8, "Currently Assigned Trouble Ticket", rltk::colors::YELLOW);
        term(2)->print_center(13, current_mission->title, rltk::colors::MAGENTA);
        term(2)->print_center(14, current_mission->description);
        term(2)->print_center(15, std::string("Location: " + layer_names[current_mission->z]));
        term(2)->print_center(16, "[A] Abandon Ticket - warning, this will damage your career.", rltk::colors::RED);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            each<mission_t>([&current_mission, &has_mission] (entity_t &e, mission_t &m) {
                delete_component<mission_t>(e.id);
                emit(inflict_despair{"You give up on the trouble ticket, unable to help.", 1, e.id});
            });
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return POP;
    } else {
        return CONTINUE;
    }
}

