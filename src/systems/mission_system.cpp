#include "mission_system.hpp"
#include "../components/components.hpp"
#include <rltk.hpp>
#include "../globals.hpp"
#include <boost/optional.hpp>

using namespace rltk;

void mission_system::configure() {
    subscribe_mbox<player_fix_it>();
}

const std::vector<std::tuple<std::string, std::string, std::string>> computer_missions {
        {"I think I have a virus",
                "My computer is running really slowly. Every time I try to work, I get pop-ups telling me to punch a monkey.",
                "You run the company anti-virus, and clean up the computer."
        },
        {"I punched the monkey!",
                "I punched the monkey, and now there are pop-ups everywhere.",
                "You clean up the computer, and educate the user on idiocy."
        },
        {"I can't find my files",
                "I saved everything on my desktop, but it's full. I can't find anything!",
                "You gently introduce the user to the concept of folders."
        },
        {"PC sounds like washing machine",
                "Whenever I try to work, my PC shakes like a washing machine.",
                "You replace the PC fan."
        },
        {"My files are gone",
                "I stapled my floppy disk to the wall, and it won't load!",
                "You give the user the bad news that you really can't help them."
        },
        {"My icons are running away!",
                "When I try to click an icon, it runs away from my cursor!",
                "You run the company anti-virus, and clean up the computer."
        },
        {"Porn Everywhere!",
                "I opened an attachment, and now all I can see is porn",
                "You run the company anti-virus, and educate the user on attachment safety."
        },
        {"I can't send pictures",
                "I took screenshots, saved them in Word. Saved that as a PDF. Now it won't send.",
                "You carefully extract the images and send them one at a time due to size."
        },
        {"Microsoft have hacked me!",
                "So Microsoft Support called me, I gave them $50 and they locked me out of my PC.",
                "You explain that this is a common scam and that they are idiots."
        },
        {"No start menu",
                "This new computer sucks! No start menu, no big blue E!",
                "You gently explain that they now have a Mac."
        },
        {"Kybrd Dsnt Wrk",
                    "My vwls r nt wrkng nymre. Hlp.",
                    "You replace the keyboard."
        },
        {"Everything is squiggly!",
                "All my menus and icons have been replaced with hieroglyphics.",
                "You switch the default language back to English."
        }
};

const std::vector<std::tuple<std::string, std::string, std::string>> printer_missions {
        {"Printer hates me",
                "Every time I try to print, I just see the message PC-LOAD-LETTER. I need to print a sales brochure!",
                "You add paper to the printer."
        },
        {"Printer jam!",
                "I tried to print hearts on my panties, and now they are melted into the printer.",
                "You scrape molten nylon panties from the printer."
        },
        {"Printer says 'offline'",
                "Every time I try to print, I just get a red X!",
                "You turn the printer on."
        },
        {"My brochure is green!",
                "Everything I print is turning green!",
                "You add toner to the printer."
        },
        {"My pictures won't print",
                "I keep sending a picture to the printer, and nothing comes out!",
                "You clear the print queue, and adjust printer memory settings to allow for HUGE cat pictures."
        },
        {"It won't stop!",
                "I printed a report. It just keeps on printing.",
                "You clear the print queue."
        }
};

const std::vector<std::tuple<std::string, std::string, std::string>> server_missions {
        {"Embarrassing email",
                "I accidentally sent my wedding photos to everyone in the office. Please clear it from the server!",
                "You run a mailbox cleanup script, removing the embarrassing email from the mail queue."
        },
        {"Mailbox is full",
                "I can't receive any email, my mailbox is full.",
                "You clean out 100 Gb of spam."
        },
        {"Missing file",
                "I saved my TPS reports, and now I can't find them on the server!",
                "You eventually figure out which TPS Reports.doc is the right one, and hand it to the user."
        },
        {"Server making clicking noises",
                "The server is making a click noise. I think it's trying to tell me something.",
                "You replace a drive in the RAID array."
        },
        {"Server sounds like a jet taking off",
                "I think there is something wrong with the server. It's roaring like a jet on final approach.",
                "You fix the server's case fan."
        }
};

const std::vector<std::tuple<std::string, std::string, std::string>> router_missions {
        {"Slow Internet",
                "Our whole area has slow Internet. Please fix it!",
                "You fix an MTU mismatch that got in there somehow."
        },
        {"Outage!",
                "Our floor is having troubles accessing the Internet.",
                "You plug the router back in."
        },
        {"Internet but no servers!",
                "An intern added a wifi router, and now we have Internet but no server access",
                "You fix the wiring on the router, which had LAN and WAN confused."
        },
        {"Everything redirects to China",
                "Every website we open is going to a Chinese site!",
                "You flash the router with a not-hacked firmware, and change the default password."
        }
};

available_mission_t build_generic_mission(std::vector<std::pair<std::size_t, position_t *>> &targets,
                                          const mission_type_t &type, const std::vector<std::tuple<std::string, std::string, std::string>> &missions) {
    available_mission_t m;
    m.mission_type = FIX_COMPUTER;
    const int random_target = rng.roll_dice(1, targets.size())-1;
    m.destination_id = targets[random_target].first;
    m.x = targets[random_target].second->x;
    m.y = targets[random_target].second->y;
    m.z = targets[random_target].second->level;
    targets.erase(targets.begin() + random_target);
    int n = rng.roll_dice(1, missions.size())-1;
    m.title = std::get<0>(missions[n]);
    m.description = std::get<1>(missions[n]);
    m.resolution = std::get<2>(missions[n]);
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
    player_t * player = nullptr;
    each<player_t>([&player] (entity_t &e, player_t &p) { player = &p; });
    assert(player != nullptr);

    std::vector<std::pair<std::size_t, position_t *>> result;
    each<T, position_t>([&result, &m, &player] (entity_t &e, T &t, position_t &pos) {
        auto finder = m.fixed_systems.find(e.id);
        if (finder == m.fixed_systems.end() && pos.level < player->level+3 && pos.level > player->level) {
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
        case 2 : if (printers.size()>0) return build_printer_mission(printers);
        case 3 : if (servers.size()>0) return build_server_mission(servers);
        case 4 : if (routers.size()>0) return build_router_mission(routers);
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

    std::queue<player_fix_it> * fixes = mbox<player_fix_it>();
    while (!fixes->empty()) {
        fixes->pop();

        each<player_t, mission_t, position_t>([] (entity_t &e, player_t &p, mission_t &m, position_t &pos) {
            if (m.z == pos.level && distance2d(pos.x, pos.y, m.x, m.y) < 1.5F) {
                // Complete the mission!
                emit(log_message{LOG().text(m.resolution)->chars});
                ++p.cost_savings;
                if (p.cost_savings > 5) {
                    p.caffeine = 101;
                    p.despair = 10;
                    ++p.level;
                    if (p.level > 4) {
                        quitting = true;
                        quit_reason = WINGAME;
                        p.cost_savings = 0;
                    } else {
                        emit_deferred(log_message{LOG().col(rltk::colors::GREEN)->text("You have been promoted! You are one step closer to being paid for this.")->chars});
                    }
                }

                // Flag it so it won't become available again
                each<available_missions_t>([&m] (entity_t &e, available_missions_t &missions) {
                   missions.fixed_systems.insert(m.destination_id);
                });

                delete_component<mission_t>(e.id);
            }
        });
    }
}
