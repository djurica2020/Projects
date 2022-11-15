#ifndef COMMANDS_H
#define COMMANDS_H

#include"Exceptions.h"
#include"Tree.h"

#include<queue>
#include<stack>
#include<string>

using namespace std;

class Commands {

public:
	Commands() : command_text_(NULL) {};
	~Commands();

	void LS(const TreeNode* root, TreeNode* node, fstream& output, queue<TreeNode*>& road, stack<TreeNode*>& last_visited, bool& first_line);
	void CD(TreeNode*& node, string command_text, bool& found);
	void NEW(TreeNode*& node, string name, string text);
	void DEL(TreeNode*& node, string read, stack<TreeNode*>& last_visited, bool& found);
	void EXE(TreeNode*& node, string read, fstream& output, bool& first_line, bool& found);

private:
	string command_text_;

};

#endif