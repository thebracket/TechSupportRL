#include "log_system.hpp"
#include <rltk.hpp>
#include "../components/components.hpp"

using namespace rltk;

constexpr int MAX_LOG_AGE = 200;
constexpr int MAX_LOG_LINES = 9;

void log_system::configure() {
    system_name = "Logging system";
    subscribe_mbox<log_message>();
}

void log_system::update(const double ms) {
    logger_t * logger;
    each<logger_t>([&logger] (entity_t &e, logger_t &l) { logger = &l; });

    std::queue<log_message> * log = mbox<log_message>();
    while (!log->empty()) {
        log_message msg = log->front();
        log->pop();

        logger->lines.insert(logger->lines.begin(), log_line_t{msg.chars});
    }

    // Cull older log entries
    logger->lines.erase(std::remove_if(logger->lines.begin(), logger->lines.end(), [] (auto &l) { return l.age>MAX_LOG_AGE; }), logger->lines.end());

    // Rendering
    const int max_x = term(2)->term_width-2;
    const int max_y = term(2)->term_height-2;
    int Y = max_y;
    int i=0;
    for (const auto &line : logger->lines) {
        if (i < MAX_LOG_LINES) {
            int X = 2;

            for (const rltk::vchar &c : line.chars) {
                term(2)->set_char(X, Y, c);
                ++X;
                if (X > (max_x -1)) {
                    X = 6;
                    --Y;
                }
            }
            --Y;

        } else {
            break;
        }
        ++i;
    }
}