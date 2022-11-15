#include "Commands.h"
#include "Exceptions.h"
#include "FileSystem.h"


FileSystem::FileSystem() : tree_(nullptr), command_(nullptr) {}

FileSystem::~FileSystem() {
	delete tree_;
	delete command_;
}

void FileSystem::loadHierarchy(const string& fs_filepath, const string& log_filepath) {
	fstream output(log_filepath, ios::out);
	tree_ = new Tree(fs_filepath, log_filepath, output);				//Pravljenje novog stabla
	output_.append(log_filepath);										//U string output_ upisuje se naziv izlaznog fajla
}

void FileSystem::execute(const string& filepath) {

	Tree* tree = tree_;
	TreeNode* root = tree->get_root();
	fstream input(filepath, ios::in);
	char c;
	string read;
	bool first_line = true;
	fstream output_file(output_, ios::out);
	try {
		while (input.peek() != EOF) {										//Iz tekstualne datoteke zadate putanjom filepath čitaj karaktere
			try {
				c = input.get();
				read.push_back(c);

				if (read == "LS") throw new CommandLs();					//Ukoliko se u stringu read nađe neka od ključnih reči funkcija, baci izuzetke
				if (read == "CD") throw new CommandCd();
				if (read == "NEW") throw new CommandNew();
				if (read == "DEL") throw new CommandDel();
				if (read == "EXE") throw new CommandExe();
			}
			catch (CommandLs*) {
				stack<TreeNode*> last_visited;
				queue<TreeNode*> road;
				command_->LS(root, root, output_file, road, last_visited, first_line);
				read.clear();
			}
			catch (CommandCd*) {
				bool found = false;
				read.clear();
				c = input.get();
				while (1) {													//U read smešta ime foldera kom treba pristupiti
					c = input.get();
					if (c == '\n') break;
					read.push_back(c);
				}
				command_->CD(root, read, found);							//U komandu CD se prosleđuju trenutni čvor root, ime foldera read, i bool found koji je indikator da li je folder name pronađen
				if (found == false) throw new ErrorCd;
				read.clear();
			}
			catch (CommandNew*) {
				read.clear();
				c = input.get();
				while (1) {
					c = input.get();										//U read smešta ime foldera/fajla koji treba napraviti
					if (c == ' ') break;
					if (c == '\n') break;
					read.push_back(c);
				}
				string text;												//Ukoliko naiđemo na razmak, pravimo novi fajl pa u string text upisujemo text tog fajla
				if (c == ' ') {
					while (1) {
						c = input.get();
						if (c == '\n') break;
						text.push_back(c);
					}
				}

				command_->NEW(root, read, text);
				stack<TreeNode*> last_visited;
				TreeNode* temp = tree->get_root();
				tree_->get_root()->sort(temp, last_visited);
				read.clear();
				text.clear();
			}
			catch (CommandDel*) {
				bool found = false;											//Slična logika kao i za CD, bool found nam predstavlja indikator da li postoji fajl/folder koji prosleđujemo funkcijom DEL
				read.clear();
				c = input.get();
				while (1) {
					c = input.get();
					if (c == '\n') break;
					read.push_back(c);										//U read se smešta ime foldera/fajla koji treba obrisati
				}
				stack<TreeNode*> last_visited;
				command_->DEL(root, read, last_visited, found);
				if (found == false) throw new ErrorDel;
				read.clear();
			}
			catch (CommandExe*) {
				bool found = false;											//Ista logika za found i read kao u prethodnom delu za DEL
				read.clear();
				c = input.get();
				while (1) {
					c = input.get();
					if (c == '\n') break;
					read.push_back(c);
				}
				command_->EXE(root, read, output_file, first_line, found);
				if (found == false) throw new ErrorExe;
				read.clear();
			}
		}
	}

	catch (ErrorCd* e) {													//Hvatanje grešaka i ispis u output fajlove
		output_file << e->what();
	}
	catch (ErrorDel* e) {
		output_file << e->what();		
	}
	catch (ErrorExe* e) {
		output_file << e->what();
	}
}