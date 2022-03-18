#ifndef NODE_H
#define NODE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"operation.h"

typedef struct node_t {
	union {
		int type;
		char sign;
	};

	int value;
	struct node_t *parent;
	struct node_t *next;
	struct node_t *child;
} node_t;

node_t *setHead(int operation);

node_t *appendNode(node_t *nose, node_t *node);

node_t *appendChild(node_t *head, node_t *node);

void popNode(node_t *head);

void printList(node_t *head);

#endif
