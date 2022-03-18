#include"formula.h"

void replaceChild(node_t *head, node_t *replacedNode) {
	replacedNode->next = head->child;
	head->child = replacedNode;
}

node_t *createEquation(char *formula) {
	node_t dummy;
	node_t *head = &dummy;
	node_t *currentNode = NULL;
	node_t *currentHead = NULL;
	node_t *newHead = NULL;

	head = setHead(formula[1]);
	currentNode = malloc(sizeof(node_t));
	currentNode->sign = formula[0];
	appendChild(head, currentNode);
	currentHead = head;

	int i = 2;
	while (formula[i + 1] != '\0') {
		currentNode = malloc(sizeof(node_t));
		currentNode->sign = formula[i];

		int state = cmpOperation(formula[i + 1], currentHead->type);

		switch (state) {
			case LOWER:
				newHead = setHead(formula[i + 1]);
				appendChild(currentHead, newHead);
				currentHead = newHead;
				appendChild(currentHead, currentNode);
				break;
			case HIGHER:
				appendChild(currentHead, currentNode);

				while (1) {
					if (currentHead->parent == NULL) {
						newHead = setHead(formula[i + 1]);
						appendChild(newHead, head);
						head = newHead;
						currentHead = newHead;
						break;
					}
					state = cmpOperation(currentHead->parent->type, formula[i + 1]);
					if (state == HIGHER) {
						newHead = setHead(formula[i + 1]);
						popNode(currentHead->parent);
						appendChild(currentHead->parent, newHead);
						appendChild(newHead, currentHead);
						currentHead = newHead;
						break;
					}
					if (state == EQUAL) {
						currentHead = currentHead->parent;
						break;
					}
					currentHead = currentHead->parent;
				}
				break;
			case EQUAL:
				appendChild(currentHead, currentNode);
				break;
		}

		i += 2;
	}

	currentNode = malloc(sizeof(node_t));
	currentNode->sign = formula[i];
	appendChild(currentHead, currentNode);

	return head;
}

/*
node_t *generateList(char *formula) {
	node_t *head = NULL;
	node_t *currentHead = NULL;
	node_t *currentNode = NULL;
	node_t *newHead = NULL;
	node_t *ptr = NULL;

	head = setHead(formula[1]);
	currentNode = malloc(sizeof(node_t));
	currentNode->sign = formula[0];
	appendChild(head, currentNode);
	currentHead = head;
	ptr = head;

	int i = 2;
	while (formula[i + 1] != '\0') {
		currentNode = malloc(sizeof(node_t));
		currentNode->sign = formula[i];

		int state = cmpOperation(formula[i + 1], currentHead->type);

		switch (state) {
			case EQUAL: appendChild(currentHead, currentNode); break;
			case LOWER:
				newHead = setHead(formula[i + 1]);
				appendChild(currentHead, newHead);
				appendChild(newHead, currentNode);

				ptr = currentHead;

				currentHead = newHead;
				break;
			case HIGHER:
				state = cmpOperation(formula[i + 1], head->type);
				if (state == HIGHER) {
					appendChild(currentHead, currentNode);
					newHead = setHead(formula[i + 1]);
					appendChild(newHead, head);
					head = newHead;
					currentHead = newHead;
				}
				if (state == LOWER) {
					appendChild(currentHead, currentNode);
					newHead = setHead(formula[i + 1]);
					popNode(ptr);
					appendChild(ptr, newHead);
					appendChild(newHead, currentHead);
					currentHead = newHead;
				}
				if (state == EQUAL) {
					appendChild(currentHead, currentNode);
					currentHead = head;
				}
				break;
			default: break;
		}

		i += 2;
	}

	// last
	currentNode = malloc(sizeof(node_t));
	currentNode->sign = formula[i];
	appendChild(currentHead, currentNode);

	return head;
}
*/

/*
node_t *generateList(char *formula) {
	node_t *head = NULL;
	node_t *parentNose = NULL;
	node_t *nose = NULL;
	node_t *node = NULL;
	node_t *tmp = NULL;
	char lastOperation = -1;

	int state;

	// first 
	head = setHead(formula[1]);
	lastOperation = formula[1];
	node = malloc(sizeof(node_t));
	node->sign = formula[0];
	appendChild(head, node);
	nose = head;
	parentNose = nose;

	int i = 2;
	while (formula[i + 1] != '\0') {
		node = malloc(sizeof(node_t));
		node->sign = formula[i];

		state = cmpOperation(formula[i + 1], lastOperation);

		switch (state) {
			case EQUAL: appendChild(nose, node); break;
			case LOWER:
				parentNose = nose;
				tmp = setHead(formula[i + 1]);
				appendChild(nose, tmp);
				appendChild(tmp, node);
				nose = tmp;
				break;

			case HIGHER:
				state = cmpOperation(formula[i + 1], parentNose->operationType);
				if (nose == parentNose) {
					appendChild(nose, node);
					head = setHead(formula[i + 1]);
					appendChild(head, nose);
					nose = head;
					parentNose = head;
				} else if (state == LOWER) {
					appendChild(nose, node);
					if (parentNose 

					popNode(parentNose);
					tmp = setHead(formula[i + 1]);
					appendChild(tmp, nose);
					appendChild(parentNose, tmp);
					nose = tmp;
				} else {
					appendChild(nose, node);
					nose = parentNose;
				}

				break;
		}

		lastOperation = formula[i + 1];
		i += 2;
	}

	// last
	node = malloc(sizeof(node_t));
	node->sign = formula[i];
	appendChild(nose, node);

	return head;
}
*/

/*
node_t *generateList(char *formula) {
	int operationLevel = -1;
	char headOperation = '/';
	int splitPos = 0;
	int i = 1;

	while (formula[i] != '\0') { 
		int level = getLevel(formula[i]);
		if (level > operationLevel) {
			splitPos = i; operationLevel = level; headOperation = formula[i];
		}
		i += 2;
	}

	// tail
	node_t *tail, *nose;
	char *tmp = (char *)&formula[splitPos + 1];
	if (tmp[1] == '\0') {
		node_t *node = malloc(sizeof(node_t));
		node->sign = tmp[0];
		node->next = NULL;
		node->child = NULL;

		tail = node;
	} else { tail = generateList(tmp); }

	// nose
	tmp = calloc(splitPos, sizeof(char));
	for (int i = 0; i < splitPos; i++) {
		tmp[i] = formula[i];
	}
	tmp[splitPos] = '\0';
	if (tmp[1] == '\0') {
		node_t *node = malloc(sizeof(node_t));
		node->sign = tmp[0];
		node->next = NULL;
		node->child = NULL;

		nose = node;
	} else { nose = generateList(tmp); }

	node_t *head = setHead(headOperation);
	appendChild(head, nose);
	appendChild(head, tail);

	return head;
}
*/
