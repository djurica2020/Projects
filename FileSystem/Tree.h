#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;


class Tree {
public:
	Tree();
	Tree(string fs_filepath, string log_filepath, fstream& output);
	Tree(const Tree&) = delete;
	Tree(Tree&&) = delete;
	~Tree();

	TreeNode* get_root();

	void add_folder(string name, TreeNode*& curr_node);
	void add_file(string name, string text, TreeNode* curr_node);
	void check_folder(string name, TreeNode*& curr_node);


private:
	TreeNode* root_;
};

#endif