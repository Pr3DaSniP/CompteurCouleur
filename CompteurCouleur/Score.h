#pragma once

#include <string>

using std::string;
using std::to_string;

class Score {
private:
	int d_value;
public:
	Score(int value);
	void incremente(int step = 1);
	int value();
	string toString();
};