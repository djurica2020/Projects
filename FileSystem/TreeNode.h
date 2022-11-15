#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stack>
#include <string>
#include <vector>

using namespace std;

class TreeNode {

public:
	enum Type { FOLDER, FILE };
	TreeNode() : parent_(nullptr), type_(Type::FOLDER) {}
	TreeNode(string name, Type type);
	TreeNode(string name, string text, Type type);
	TreeNode(const TreeNode&) = delete;
	TreeNode(TreeNode&&) = delete;
	~TreeNode();


	string get_name() const;
	
	int get_type();
	
	TreeNode* get_child(int n);

	void set_child_folder(string name, Type type);

	void set_child_file(string name, string text, Type type);

	void set_parent(TreeNode* parent);

	TreeNode* get_parent();

	int get_size();

	string get_text();

	void change_node(TreeNode* temp);

	void sort(TreeNode*& root, stack<TreeNode*>& last_visit);

	void delete_child(TreeNode* node, int i);


private:
	Type type_;
	string name_;
	string text_;
	TreeNode* parent_ = nullptr;
	vector<TreeNode*> children_;
};

#endif