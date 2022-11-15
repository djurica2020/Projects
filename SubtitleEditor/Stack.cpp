#include "Stack.h"
#include <iostream>
using namespace std;

Stack::Stack() {
	this->head = this->last = this->current = nullptr;
}

Stack::~Stack() {
	stack* old;
	if (this->head != nullptr) {
		for (old = this->head; old; ) {
			this->head = head->next;
			delete old;
			old = head;
		}
	}

}

stack* Stack::loadStack(Elem* head) {

	Elem* tempHead = nullptr, * tempLast = nullptr, * newTemp = new Elem;
	for (newTemp = head; newTemp; newTemp = newTemp->next) {
		Elem* tempCurr = new Elem;
		tempCurr->ordNumb = newTemp->ordNumb;
		tempCurr->begin = newTemp->begin;
		tempCurr->end = newTemp->end;
		tempCurr->msBegin = newTemp->msBegin;
		tempCurr->msEnd = newTemp->msEnd;
		tempCurr->text.append(newTemp->text);
		if (tempHead == nullptr) tempHead = tempCurr;
		else tempLast->next = tempCurr;
		tempLast = tempCurr;
		tempLast->next = nullptr;
		tempCurr = new Elem;
	}

	stack* newStack = new stack;

	newStack->elem = tempHead;



	if (this->head == nullptr) this->head = newStack;
	else this->last->next = newStack;
	this->last = newStack;
	this->last->next = nullptr;

	return this->head;
}

Elem* Stack::returnLastState() {
	for (this->current = this->head; this->current->next != this->last; this->current = this->current->next);
	return current->elem;
}

