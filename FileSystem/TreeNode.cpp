#include "TreeNode.h"

#include<iostream> 

using namespace std;


TreeNode::TreeNode(string name, Type type) : name_(name), type_(type) {}									//Ovaj konstruktor konstruiše čvor koji sadrži samo ime, tj čvor tipa folder

TreeNode::TreeNode(string name, string text, Type type) : name_(name), text_(text), type_(type) {}			//Dodavanjem teksta naš čvor postaje tipa fajl


TreeNode::~TreeNode() {																						//Destruktor švora
	name_.clear();
	parent_ = nullptr;
	text_.clear();
	int i;
	for (i = 0; i < children_.size(); i++) {
		children_.at(i) = nullptr;
	}

}

string TreeNode::get_name() const {																			//Funkcija vraća ime čvora
	return name_;
}

int TreeNode::get_type() {																					//Funkcija vraća tip FOLDER/FILE
	return type_;
}

TreeNode* TreeNode::get_child(int n) {																		//Funkcija vraća dete na poziciji n
	return children_.at(n);
}


void TreeNode::set_child_folder(string name, Type type) {													//Funkcija postavlja sadržaj čvora tipa folder										
	children_.push_back(new TreeNode(name, type));
}

void TreeNode::set_child_file(string name, string text, Type type) {										//Funkcija postavlja sadržaj čvora tipa fajl
	children_.push_back(new TreeNode(name, text, type));

}

void TreeNode::set_parent(TreeNode* parent) {																//Funkcija postavlja roditelja čvora
	parent_ = parent;
}

TreeNode* TreeNode::get_parent() {																			//Funkcija vraća roditelja
	return parent_;
}


int TreeNode::get_size() {																					//Funkcija vraća broj sinova nekog čvora
	return children_.size();
}

string TreeNode::get_text() {																				//Funkcija vraća tekst čvora
	return text_;
}

void TreeNode::change_node(TreeNode* temp) {																//Funkcija koja menja čvor sadržajem čvora temp
	name_ = temp->get_name();
	text_ = temp->get_text();
	type_ = Type(temp->get_type());
	parent_ = temp->get_parent();
	children_.swap(temp->children_);
}


void TreeNode::sort(TreeNode*& node, stack<TreeNode*>& last_visited) {										//Sortiranje stabla

	TreeNode* curr = node;
	int i = 0;
	while (curr) {

		if (curr->get_size() > 1) {
			last_visited.push(curr);
			for (; i < curr->get_size(); i++) {
				curr = curr->get_child(i);
				curr->sort(curr, last_visited);
				curr = last_visited.top();
			}
			last_visited.pop();
		}
		else curr = nullptr;

		if (curr != nullptr && i == curr->get_size()) {
			for (int j = 0; j < curr->get_size(); j++) {
				for (int k = j + 1; k < curr->get_size(); k++) {
					if (curr->get_child(j)->get_name().compare(curr->get_child(k)->get_name()) > 0) {		//Poredimo nazive čvorova, ukoliko nije u rastućem alfabetskom poretku menjamo dva čvora
						TreeNode* temp = new TreeNode();
						temp->change_node(curr->get_child(j));
						curr->get_child(j)->change_node(curr->get_child(k));
						curr->get_child(k)->change_node(temp);
						for (int l = 0; curr->get_size() != 0 && l < curr->get_child(j)->get_size(); l++) {
							if (curr->get_child(j)->get_child(l) != nullptr) curr->get_child(j)->get_child(l)->set_parent(curr->get_child(j));
						}
						for (int l = 0; curr->get_size() != 0 && l < curr->get_child(k)->get_size(); l++) {
							if (curr->get_child(k)->get_child(l) != nullptr) curr->get_child(k)->get_child(l)->set_parent(curr->get_child(k));
						}

					}
				}
			}
			curr = nullptr;
		}
	}

}

void TreeNode::delete_child(TreeNode* node, int i) {
	node->children_.at(i) = nullptr;																		//Funkcija briše sina čvora node na poziciji i
}


