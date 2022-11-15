#include "Exceptions.h"
#include "Tree.h"

#include <iostream>

using namespace std;

Tree::Tree() {
	root_ = nullptr;
}

Tree::Tree(string fs_filepath, string log_filepath, fstream& output) {

	fstream input(fs_filepath, ios::in);
	char c = ' ';
	string read;
	TreeNode* curr_node = nullptr;
	while (input.peek() != EOF) {
		try {
			try {
				c = input.get();
				if (read.size() != 0 && c == '\n') throw new NewFolder();				//Čitanje karaktera iz ulaznog tekstualnog fajla. Ukoliko naiđemo na znak za novi red, a da pri tom nismo naišli na razmak ili kosu crtu pravimo novi folder
				else if (read.size() != 0 && c == ' ') throw new NewFile();				//Ukoliko naiđemo na razmak, pravimo novi fajl, bacamo izuzetak i hvatanjem ulazimo u funkciju za pravljenje novog fajla
				else if (read.size() != 0 && c == '\\')  throw new CheckFolder();		//Ukoliko čitanjem naiđemo na kosu crtu, proverićemo da li imamo napravljen folder
				read.push_back(c);														//U string read smeštamo ime našeg fajla/foldera koji čitamo iz ulazne datoteke

			}
			catch (NewFolder*) {
				int a = read.find("\\");
				if (a >= 0) {															//Svaki novi folder mora ispred svog naziva sadržati kosu crtu, ukoliko je nema folder je neregularno upisan
					read.erase(a, 1);
					add_folder(read, curr_node);
					read.clear();
				}
				else {
					throw Error("Error: fs_filepath error");
				}

			}
			catch (CheckFolder*) {
				int a = read.find("\\");												//Kosu crtu iz naziva foldera prilikom provere da li je već unet, brišemo kako bismo mogli da uporedimo stringove u funkciji
				if (a >= 0) read.erase(a, 1);

				check_folder(read, curr_node);
				read.clear();
				if (c == '\\') read.push_back(c);



			}
			catch (NewFile*) {
				string text;															//U string text smeštamo tekst našeg fajla
				int a = read.find("\\");
				if (a >= 0) read.erase(a, 1);
				a = read.find(".exe");
				int b = read.find(".txt");
				if (a >= 0 || b >= 0) {
					while (1) {
						c = input.get();
						if (c == '\n') break;
						else if (c == EOF) break;
						else text.push_back(c);
					}
					if (read.find(".exe") > 0 || read.find(".txt"));					//folder u sebi mora sadržati ekstenziju koja je pre toga zadata u samom tekstu zadatka. Ukoliko ima drugačiju ekstenziju, fajl nije podržan
					add_file(read, text, curr_node);
				}
				else {
					curr_node = nullptr;
					throw Error("Error: File type\n");
					continue;
				}
				read.clear();
				curr_node = nullptr;
			}

		}

		catch (Error& e) {
			while (c != '\n') c = input.get();
			read.clear();
			cout << e.what();
		}
	}
	stack<TreeNode*> last_visited;
	root_->sort(root_, last_visited);
}


Tree::~Tree() {

	stack<TreeNode*> last_visited;
	TreeNode* curr = root_;
	int i = 0, j = 0;
	while (last_visited.size() != 0 || root_ != nullptr) {								//Brisanje stabla izvršeno je na sledeći način: Ukoliko čvor ima sina, pokazivač curr prebaci na tog sina. Ponovi postupak i za njega. Ukoliko nema sina obriši sve njegove parametre i stavi ga na nullptr
		if (curr->get_size() != 0 && j != curr->get_size()) {
			i = 0;
			while (i < curr->get_size() && curr->get_child(i) == nullptr) {
				i++;
			}
			if (i != curr->get_size()) {
				last_visited.push(curr);
				curr = curr->get_child(i);
				j = 0;
				while (j < curr->get_size() && curr->get_child(j) == nullptr) {			//Broj j nam pokazuje koliko neki čvor ima sinova koji su nullptr. Ukoliko je broj sinova na nullptr jednak broju sinova stabla, curr uzima element iz steka
					j++;
				}
			}
			else {
				if (last_visited.size() == 0) break;
				curr = last_visited.top();
				last_visited.pop();
			}
			continue;
		}

		else {
			delete curr;
			curr = last_visited.top();
			last_visited.pop();
			curr->delete_child(curr, i);
			j = 0;
		}

	}
	delete root_;
	root_ = nullptr;
}

TreeNode* Tree::get_root() {
	return root_;
}

void Tree::add_folder(string name, TreeNode*& curr_node) {
	if (!root_) root_ = new TreeNode();																					//Ukoliko ne postoji koren stabla, napravi ga
	if (curr_node == nullptr) {																							//curr_node je pokazivač na poslednji čvor koji je proveren da li 
		root_->set_child_folder(name, TreeNode::Type::FOLDER);																	//postoji u funkciji check_folder. Ukoliko postoji novi čvor dodajemo na njega, 
																														//a ako ne novi čvor se dodaje na glavni čvor stabla
		for (int i = 0; i < root_->get_size(); i++) {
			if (root_->get_child(i)->get_parent() == NULL) root_->get_child(i)->set_parent(root_);						//Postavljanje roditeljskog čvora novom čvoru stabla
		}
	}
	else {
		curr_node->set_child_folder(name, TreeNode::Type::FOLDER);
		for (int i = 0; i < curr_node->get_size(); i++) {
			if (curr_node->get_child(i)->get_parent() == NULL) curr_node->get_child(i)->set_parent(curr_node);
		}
	}

	curr_node = nullptr;
}

void Tree::add_file(string name, string text, TreeNode* curr_node) {
	if (!root_) root_ = new TreeNode();																					//Ista logika kao i za add_folder
	if (curr_node == nullptr) {
		root_->set_child_file(name, text, TreeNode::Type::FILE);
		for (int i = 0; i < root_->get_size(); i++) {
			if (root_->get_child(i)->get_parent() == NULL) root_->get_child(i)->set_parent(root_);
		}
	}
	else {
		curr_node->set_child_file(name, text, TreeNode::Type::FILE);
		for (int i = 0; i < curr_node->get_size(); i++) {
			if (curr_node->get_child(i)->get_parent() == NULL) curr_node->get_child(i)->set_parent(curr_node);
		}
	}
}

void Tree::check_folder(string name, TreeNode*& curr_node) {

	bool found = false;
	if (curr_node == nullptr) {																							//Ukoliko je curr_node == nullptr obidji sinove korena stabla
		for (int i = 0; i < root_->get_size(); i++) {																	//Sve dok čvor ima sinove, oblazi ih. Ako je ime sina isto kao string name, curr stavi na sina
			if (root_->get_child(i)->get_name().compare(name) == 0 && root_->get_type() == TreeNode::Type::FOLDER) {
				curr_node = root_->get_child(i);
				found = true;
				if (found) return;
			}
		}
	}
	else {
		for (int i = 0; i < curr_node->get_size(); i++) {																//Ako je curr_node != nullptr obidji sinove pokazivača curr. Ako ima sina sa imenom name, stavi curr na njega
			if (curr_node->get_child(i)->get_name().compare(name) == 0 && curr_node->get_type() == TreeNode::Type::FOLDER) {
				curr_node = curr_node->get_child(i);
				found = true;
				if (found) return;
			}
		}
	}
	if (found == false) {																								//found je true ako je folder već napravljen. Ako je false ispiši grešku
		throw Error("Error: fs_filepath error\n");
	}

}



