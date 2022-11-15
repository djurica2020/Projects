#ifndef STACK_H	
#define STACK_H

#include "Time.h"
#include <string>
using namespace std;

struct Elem {
	int ordNumb = 0;
	string text;
	Time begin, end;
	Elem* next;
	int words;
	int msBegin, msEnd;
};

struct stack {
	Elem* elem;
	stack* next;
};

class Stack {

public:
	Stack();
	~Stack();
	stack* loadStack(Elem* head);
	Elem* returnLastState();
	stack* head, * last, * current;
};





#endif