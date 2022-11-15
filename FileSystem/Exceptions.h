#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using namespace std;

class NewFolder : public exception {
public:
	NewFolder() : exception() {}
};

class CheckFolder : public exception {
public:
	CheckFolder() : exception() {}
};

class NewFile : public exception {
public:
	NewFile() : exception() {}
};

class CommandLs : public exception {
public:
	CommandLs() : exception() {}
};

class CommandCd: public exception {
public:
	CommandCd() : exception() {}
};

class CommandNew : public exception {
public:
	CommandNew() : exception() {}
};

class CommandDel : public exception {
public:
	CommandDel() : exception() {}
};

class CommandExe : public exception {
public:
	CommandExe() : exception() {}
};

class Error : public exception {
public:
	Error(const char* msg) : exception(msg) {}
};

class ErrorCd : public exception {
public:
	ErrorCd() : exception("Error: CD") {}
};

class ErrorDel : public exception {
public:
	ErrorDel() : exception("Error: DEL") {}
};

class ErrorExe : public exception {
public:
	ErrorExe() : exception("Error: EXE") {}
};

#endif
