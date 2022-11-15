#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "Tree.h"
#include "Commands.h"

#include<fstream>
#include <stack>
#include<string>

using namespace std;


class FileSystem {

public:
	FileSystem();
	~FileSystem();
	void loadHierarchy(const string& fs_filepath, const string& log_filepath);
	void execute(const string& filepath);


private:
	Tree* tree_;
	Commands* command_;
	string output_;
};
#endif