#include "evox.h"

// Utility function to get the precedence of a character according to PEMDAS.
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

// Tiny utility function to apply operations to operands. This mainly exists so I don't have to paste this logic all over the main function.
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

double evox(const std::string& expression) {
	std::stack<double> numbers;
	std::stack<char> operators;
	bool reading_number = false;
	double current_number = 0;
	for (char c : expression) {
		if (isdigit(c)) {
			if (reading_number) {
				current_number = current_number * 10 + (c - '0');
			} else {
				current_number = c - '0';
				reading_number = true;
			}
		} else {
			if (reading_number) {
				numbers.push(current_number);
				current_number = 0;
				reading_number = false;
			}
			if (c == '(') {
				operators.push(c);
			} else if (c == ')') {
				while (!operators.empty() && operators.top() != '(') {
					char op = operators.top();
					operators.pop();
					double b = numbers.top();
					numbers.pop();
					double a = numbers.top();
					numbers.pop();
					numbers.push(apply_operation(a, b, op));
				}
				operators.pop();
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
	while (!operators.empty()) {
		char op = operators.top();
		operators.pop();
		double b = numbers.top();
		numbers.pop();
		double a = numbers.top();
		numbers.pop();
		numbers.push(apply_operation(a, b, op));
	}
	return numbers.top();
}
