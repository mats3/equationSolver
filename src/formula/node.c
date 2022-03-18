#include"node.h"

node_t *setHead(int operation) {
	node_t *head = malloc(sizeof(node_t));
	head->type = operation;
	head->value = 0;
	head->next = NULL;
	head->child = NULL;
	head->parent = NULL;
	return head;
}

node_t *appendNode(node_t *nose, node_t *node) {
	while (nose->next != NULL)
		nose = nose->next;

	nose->next = node;
	node->parent = nose->parent;

	return nose;
}

node_t *appendChild(node_t *head, node_t *node) {
	if (head->child == NULL) {
		head->child = node;
		node->parent = head;
		return head;
	}

	head = head->child;
	head = appendNode(head, node);

	return head;
}

void popNode(node_t *head) {
	if (head->child == NULL) { return; }

	if (head->child->next == NULL) { head->child = NULL; return; }

	head = head->child;
	while (head->next->next != NULL)
		head = head->next;

	head->next = NULL;
}

char *getFormatList(node_t *head) {
	if (head == NULL)
		return NULL;

	char *str = calloc(50, sizeof(char));
	char *add = calloc(2, sizeof(char));

	add[0] = '(';
	strcat(str, add);

	add[0] = (char)head->type;
	strcat(str, add);

	head = head->child;
	while (head != NULL) {
		if (head->child != NULL) {
			strcat(str, getFormatList(head));
			head = head->next;
			continue;
		}
		add[0] = head->sign;
		strcat(str, add);
		head = head->next;
	}
	add[0] = ')';
	strcat(str, add);

	return str;
}

void printList(node_t *head) {
	if (head == NULL)
		return;

	putchar('(');
	putchar((char)head->type);
	head = head->child;
	while (head != NULL) {
		if (head->child != NULL) {
			printList(head);
			head = head->next;
			continue;
		}
		putchar(head->sign);
		head = head->next;
	}
	putchar(')');
}
