#include<iostream>
#include"priority.h"

int priority(char a) {
	if (a == '#') return 0;
	else if (a == '+' || a == '-') return 1;
	else if (a == '*' || a == '/') return 2;
	else return -1;
}