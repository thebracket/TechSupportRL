#pragma once

#include <string>
#include <rltk.hpp>

struct position_t {
    std::string xml_identity = "position_t";
    void to_xml(rltk::xml_node * c) {
        rltk::component_to_xml(c,
                               std::make_pair("x", x),
                               std::make_pair("y", y),
                               std::make_pair("level", level)
        );
    }
    void from_xml(rltk::xml_node * c) {
        x = c->val<int>("x");
        y = c->val<int>("y");
        level = c->val<int>("level");
    }

	int x = 0;
	int y = 0;
	int level = 0;

	position_t() {}
	position_t(const int &X, const int &Y, const int &l) : x(X), y(Y), level(l) {}

	bool operator==(position_t &rhs) { return (x==rhs.x && y==rhs.y && level==rhs.level); }
};

