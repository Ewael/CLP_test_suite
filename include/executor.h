#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"

/**
 * @brief Basic executor structure
 */
struct executor {
    struct parser *parser;
};

/**
 * @brief Create a new executor
 *
 * @return NULL on error, the executor otherwise
 */
struct executor *ex_init(struct parser *parser);

/**
 * @brief Free the memory associated with an executor
 */
void ex_destroy(struct executor *ex);

/**
 * @brief Run the executor, executing all the commands inside
 */
int ex_run(struct executor *ex);

#endif // EXECUTOR_H
