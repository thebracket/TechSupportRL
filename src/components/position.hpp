#pragma once

struct position_t {
	int x = 0;
	int y = 0;
	int level = 0;

	position_t() {}
	position_t(const int &X, const int &Y, const int &l) : x(X), y(Y), level(l) {}

	bool operator==(position_t &rhs) { return (x==rhs.x && y==rhs.y && level==rhs.level); }
};

