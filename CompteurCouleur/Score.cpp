#include "Score.h"

Score::Score(int value)
	: d_value{ value } 
{}

void Score::incremente(int step) {
	d_value += step;
}

int Score::value() {
	return d_value;
}

string Score::toString() {
	return to_string(d_value);
}