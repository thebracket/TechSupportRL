#pragma once

enum gait_t { SNEAKING, WALKING };

struct player_t {
	std::string xml_identity = "player_t";

    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                               std::make_pair("health", health),
                               std::make_pair("despair", despair),
                               std::make_pair("cost_savings", cost_savings),
                               std::make_pair("level", level),
                               std::make_pair("caffeine", caffeine),
                               std::make_pair("gait", gait)
        );
    }

	void from_xml(rltk::xml_node * c) {
        health = c->val<uint8_t>("health");
        despair = c->val<uint8_t>("despair");
        cost_savings = c->val<uint8_t>("cost_savings");
        level = c->val<uint8_t>("level");
        caffeine = c->val<uint8_t>("caffeine");
        gait = (gait_t)c->val<int>("gait");
    }

	uint8_t health = 10;
	uint8_t despair = 10;
	uint8_t cost_savings = 0;
	uint8_t level = 0;
	uint8_t caffeine = 101;
	gait_t gait = WALKING;

	player_t() {}
};
