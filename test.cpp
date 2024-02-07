#include <iostream>
#include <string>
#include "evox.h"

int main(int argc, const char **argv) {
	std::string expression;
	std::cout << "Enter expression:";
	getline(std::cin, expression);
	std::cout << evox(expression) << std::endl;
	return 0;
}
