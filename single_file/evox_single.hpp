#pragma once

#include <algorithm>
#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace evox {

/**
 * @brief The function struct represents a mathematical function.
 * 
 * It contains the name of the function and a function pointer to the implementation.
 */
struct function {
	std::string name; /**< The name of the function. */
	double (*func)(double); /**< The function pointer to the implementation. */
};

/**
 * @brief Initializes the evox library.
 * 
 * This function initializes the evox library and sets up any necessary resources.
 * 
 * @return true if initialization is successful, false otherwise.
 */
bool init();

/**
 * @brief Registers a custom function with the evox library.
 * 
 * This function allows users to register their own custom functions with the evox library.
 * 
 * @param name The name of the function.
 * @param func The function pointer to the implementation.
 */
void register_function(const std::string &name, double (*func)(double));

/**
 * @brief Evaluates a mathematical expression using the evox library.
 * 
 * This function evaluates a mathematical expression using the evox library.
 * 
 * @param expression The mathematical expression to evaluate.
 * @return The result of the evaluation.
 */
double evox(const std::string &expression);

} // namespace evox



namespace evox {
std::vector<function> functions;

int get_precedence(char op) {
	switch (op) {
	case '^':
		return 3;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

double apply_operation(double a, double b, char op) {
	switch (op) {
	case '^':
		return std::pow(a, b);
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '+':
		return a + b;
	case '-':
		return a - b;
	default:
		return 0;
	}
}

void register_function(const std::string &name, double (*func)(double)) {
	functions.push_back({name, func});
}

bool init() {
	register_function("sin", std::sin);
	return true;
}

double evox(const std::string &expression) {
	std::stack<double> numbers;
	std::stack<char> operators;
	bool reading_number = false;
	double current_number = 0;
	double decimal_place = 10; // To handle decimal digits
	int open_parentheses_count = 0;
	for (char c : expression) {
		if (isdigit(c) || c == '.') { // Allow digits and decimal point
			if (c == '.') {
				decimal_place = 0.1;
			} else {
				if (reading_number) {
					current_number += (c - '0') * decimal_place;
					decimal_place *= 0.1;
				} else {
					current_number = current_number * 10 + (c - '0');
				}
			}
			reading_number = true;
		} else if (std::isalpha(c)) {
			std::istringstream iss(expression);
			std::string functionName;
			while (std::isalpha(c)) {
				functionName += c;
				iss >> c;
			}
			// Skip any non-numeric characters
			while (!std::isdigit(c) && c != '-' && c != '+') {
				iss >> c;
			}
			iss.putback(c);
			double argument;
			iss >> argument; // Assume the argument is a single number
			auto it = std::find_if(
				functions.begin(), functions.end(), [&functionName](const function &f) {
					return f.name == functionName;
				});
			if (it != functions.end()) {
				numbers.push(it->func(argument));
			}
		} else {
			if (reading_number) {
				numbers.push(current_number);
				current_number = 0;
				decimal_place = 10; // Reset decimal place
				reading_number = false;
			}
			if (c == '(') {
				operators.push(c);
				open_parentheses_count++;
			} else if (c == ')') {
				if (open_parentheses_count == 0) {
					// throw std::runtime_error("Mismatched parentheses: Too many closing parentheses");
				}
				while (!operators.empty() && operators.top() != '(') {
					char op = operators.top();
					operators.pop();
					double b = numbers.top();
					numbers.pop();
					double a = numbers.top();
					numbers.pop();
					numbers.push(apply_operation(a, b, op));
				}
				if (!operators.empty()) {
					operators.pop();
					open_parentheses_count--;
				} else {
					// TODO: fix this with the Teensy.
					// throw std::runtime_error("Mismatched parentheses: Too many closing parentheses");
					return 0.0;
				}
			} else {
				while (!operators.empty() && get_precedence(operators.top()) >= get_precedence(c)) {
					char op = operators.top();
					operators.pop();
					double b = numbers.top();
					numbers.pop();
					double a = numbers.top();
					numbers.pop();
					numbers.push(apply_operation(a, b, op));
				}
				operators.push(c);
			}
		}
	}
	if (reading_number) {
		numbers.push(current_number);
	}
	if (open_parentheses_count > 0) {
		// Fixme
		// throw std::runtime_error("Mismatched parentheses: Too many opening parentheses");
		return 0.0;
	}
	while (!operators.empty()) {
		char op = operators.top();
		operators.pop();
		double b = numbers.top();
		numbers.pop();
		double a = numbers.top();
		numbers.pop();
		numbers.push(apply_operation(a, b, op));
	}
	if (numbers.size() != 1) {
		// Fixme
		// throw std::runtime_error("Invalid expression");
		return 0.0;
	}
	return numbers.top();
}
} // namespace evox
