#ifndef OPERATION_H
#define OPERATION_H

/*
#define ADDITION 0x100
#define SUBTRACTION 0x200
#define MULTIPLICATION 0x400
#define DIVISION 0x800
*/

enum {
	ADDITION = '+',
	SUBTRACTION = '-',
	MULTIPLICATION = '*',
	DIVISION = '/',
};

enum {
	HIGHER,
	EQUAL,
	LOWER
};

int cmpOperation(char o1, char o2);

#endif

