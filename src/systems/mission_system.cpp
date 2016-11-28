#include "mission_system.hpp"
#include "../components/components.hpp"
#include <rltk.hpp>
#include "../globals.hpp"
#include <boost/optional.hpp>

using namespace rltk;

void mission_system::configure() {

}

const std::vector<std::pair<std::string, std::string>> computer_missions {
        {"I think I have a virus", "My computer is running really slowly. Every time I try to work, I get pop-ups telling me to punch a monkey."}
};

const std::vector<std::pair<std::string, std::string>> printer_missions {
        {"Printer hates me", "Every time I try to print, I just see the message PC-LOAD-LETTER. I need to print a sales brochure!"}
};

const std::vector<std::pair<std::string, std::string>> server_missions {
        {"Embarrassing email", "I accidentally sent my wedding photos to everyone in the office. Please clear it from the server!"}
};

const std::vector<std::pair<std::string, std::string>> router_missions {
        {"Slow Internet", "Our whole area has slow Internet. Please fix it!"}
};

available_mission_t build_generic_mission(std::vector<std::pair<std::size_t, position_t *>> &targets,
                                          const mission_type_t &type, const std::vector<std::pair<std::string, std::string>> &missions) {
    available_mission_t m;
    m.mission_type = FIX_COMPUTER;
    const int random_target = rng.roll_dice(1, targets.size())-1;
    m.destination_id = targets[random_target].first;
    m.x = targets[random_target].second->x;
    m.y = targets[random_target].second->y;
    m.z = targets[random_target].second->level;
    targets.erase(targets.begin() + random_target);
    int n = rng.roll_dice(1, missions.size())-1;
    m.title = missions[n].first;
    m.description = missions[n].second;
    return m;
}

available_mission_t build_computer_mission(std::vector<std::pair<std::size_t, position_t *>> &targets) {
    auto m = build_generic_mission(targets, FIX_COMPUTER, computer_missions);
    return m;
}

available_mission_t build_printer_mission(std::vector<std::pair<std::size_t, position_t *>> targets) {
    auto m = build_generic_mission(targets, FIX_PRINTER, printer_missions);
    return m;
}

available_mission_t build_server_mission(std::vector<std::pair<std::size_t, position_t *>> targets) {
    auto m = build_generic_mission(targets, FIX_SERVER, server_missions);
    return m;
}

available_mission_t build_router_mission(std::vector<std::pair<std::size_t, position_t *>> targets) {
    auto m = build_generic_mission(targets, FIX_ROUTER, router_missions);
    return m;
}

template <class T>
std::vector<std::pair<std::size_t, position_t *>> get_available_systems(available_missions_t &m) {
    std::vector<std::pair<std::size_t, position_t *>> result;
    each<T, position_t>([&result, &m] (entity_t &e, T &t, position_t &pos) {
        auto finder = m.fixed_systems.find(e.id);
        if (finder == m.fixed_systems.end()) {
            result.push_back(std::make_pair(e.id, &pos));
        }
    });
    return result;
}

boost::optional<available_mission_t> mission_builder(available_missions_t &m) {
    boost::optional<available_mission_t> mission;
    std::vector<std::pair<std::size_t, position_t *>> computers = get_available_systems<computer_t>(m);
    std::vector<std::pair<std::size_t, position_t *>> printers = get_available_systems<printer_t>(m);
    std::vector<std::pair<std::size_t, position_t *>> servers = get_available_systems<server_t>(m);
    std::vector<std::pair<std::size_t, position_t *>> routers = get_available_systems<switch_t>(m);

    int n = rng.roll_dice(1,4);
    switch (n) {
        case 1 : if (computers.size()>0) return build_computer_mission(computers);
        case 2 : if (printers.size()>0) return build_printer_mission(computers);
        case 3 : if (servers.size()>0) return build_server_mission(computers);
        case 4 : if (routers.size()>0) return build_router_mission(computers);
    }

    return mission;
}

void mission_system::update(const double ms) {
    each<available_missions_t>([] (entity_t &e, available_missions_t &m) {
        // Build some missions
        while (m.available_missions.size()<5) {
            auto mission = mission_builder(m);
            if (mission) m.available_missions.emplace_back(mission.get());
        }
    });
}
