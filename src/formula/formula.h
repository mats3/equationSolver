#ifndef FORMULA_H
#define FORMULA_H

#include"operation.h"
#include"node.h"

node_t *createEquation(char *formula);

node_t solveEquation(char sign);

#endif
