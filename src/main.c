#include"formula/node.h"
#include"formula/formula.h"

#include<stdio.h>

int main(int argc, char **argv) {
	char *input = "a-b*c+d/e";
	printf("Input:  %s:\n", input);
	printf("Output: ");
	node_t *head = createEquation(input);
	printList(head);
	putchar('\n');

	return 0;
}
