#pragma once

#include <algorithm>
#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace evox {
struct function {
	std::string name;
	double (*func)(double);
};

bool init();
void register_function(const std::string &name, double (*func)(double));
double evox(const std::string &expression);
} // namespace evox
