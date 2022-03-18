#include"operation.h"

int cmpOperation(char o1, char o2) {
	int diff = o1 - o2;
	if (!diff) { return EQUAL; }
	if (diff == -2 ||
		diff == 1 ||
		diff == -4 ||
		diff == 3 ||
		diff == -5) { return HIGHER; }

	return LOWER;
}
