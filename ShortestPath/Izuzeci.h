#ifndef IZUZECI_H
#define IZUZECI_H

#include <exception>
using namespace std;

class Izuzeci : public exception {
public:
	Izuzeci(const char* s) : exception(s) {}
};

#endif