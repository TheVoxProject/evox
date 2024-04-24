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
	std::string name;		/**< The name of the function. */
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
