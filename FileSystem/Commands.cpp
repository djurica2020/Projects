#include "Commands.h"

#include <iostream>

using namespace std;

Commands::~Commands() {
	command_text_.clear();
}

void Commands::LS(const TreeNode* root, TreeNode* node, fstream& output, queue<TreeNode*>& road, stack<TreeNode*>& last_visited, bool& first_line) {

	TreeNode* curr = node;

	int i = 0;
	for (; i < curr->get_size(); i++) {																				//U funkciju prosledjujemo stack<TreeNode*> last_visited koji belezi poslednji element
		if (root != node) road.push(curr);																			//koji smo obišli, queue<TreeNode*> road koji pamti putanju, konstantar pokazivač na cvor
		last_visited.push(curr);																					//i node koji je takođe na početku funkcije pokazivač na čvor stabla
		if (curr->get_child(i) != nullptr) curr = curr->get_child(i);												//U last_visited upisujemo čvor curr na kom se trenutno nalazimo kako bi se kasnije vratili u njega
		else {
			queue<TreeNode*> temp_road;
			while (road.size() != 0) {																				//Ispisujemo redom sve članove puta, sve dok naš put ima članova
				temp_road.push(road.front());																		//U privremeni put upisujemo članove puta, kako bismo sačuvali put kojim smo došli do tog čvora
				road.pop();
			}
			while (temp_road.size() > 1) {
				road.push(temp_road.front());																		//Iz temp_road put kopiramo u road, osim poslednjeg člana koji smo ispisali, kako bismo imali
				temp_road.pop();																					//obezbeđen put za sledećeg sina
			}
			continue;
		}
		if (curr->get_size() == 0) {																				//Ukoliko naš član curr nema dece, ispisujemo putanju kojom smo došli do njega
			if (first_line == true)	first_line = false;																//Ukoliko je naša izlazna datoteka prazna, na početku preskačemo stavljanje novog reda
			else { output << endl; }
			queue<TreeNode*> temp_road;
			while (road.size() != 0) {																				//Ispisujemo redom sve članove puta, sve dok naš put ima članova
				output << '\\' << road.front()->get_name();
				temp_road.push(road.front());																		//U privremeni put upisujemo članove puta, kako bismo sačuvali put kojim smo došli do tog čvora
				road.pop();
			}
			while (temp_road.size() > 1) {
				road.push(temp_road.front());																		//Iz temp_road put kopiramo u road, osim poslednjeg člana koji smo ispisali, kako bismo imali
				temp_road.pop();																					//obezbeđen put za sledećeg sina
			}
			if (temp_road.size() == 1) temp_road.pop();
			output << '\\' << curr->get_name();																		//kada je naš put ispisan, ispisujemo i član curr 
			curr = last_visited.top();																				//curr postaje poslednji čvor koji smo obišli pozivanjem iz steka
			last_visited.pop();
		}
		else {
			queue<TreeNode*> temp_road;																				//Ukoliko čvor ima svoje sinove, moramo posetiti sve njegove sinove i ispisati putanje svih njih
			output << endl;
			while (road.size() != 0) {
				if (road.front()->get_name().size() != 0) output << '\\' << road.front()->get_name();				//Ispisuje se put sve dok road ima članova
				temp_road.push(road.front());																		//U temp_road se čuvaju članovi kako bi imali sačuvan put prilikom povratka u roditelja
				road.pop();
			}
			while (temp_road.size() != 0) {
				road.push(temp_road.front());
				temp_road.pop();
			}
			output << '\\' << curr->get_name();																		//Kako element curr ima sinove, rekurentno pozivamo funkciju LS koja će proći kroz ceo čvor ispočetka
			LS(root, curr, output, road, last_visited, first_line);
			curr = last_visited.top();
			last_visited.pop();
			while (road.size() != 0) {
				temp_road.push(road.front());
				road.pop();
			}
			while (temp_road.size() > 1) {
				road.push(temp_road.front());
				temp_road.pop();
			}
		}
	}
}

void Commands::CD(TreeNode*& node, string command_text, bool& found) {
	if (command_text.compare("..") == 0) {																			//Ukoliko je zadata funkcija CD .. vraćamo se u roditelja
		node = node->get_parent();
		found = true;
	}
	else {
		for (int i = 0; i < node->get_size(); i++) {																//Prolazimo kroz trenutni čvor node, i upoređujemo nazive njegovih sinova i naziv foldera
			if (node->get_child(i) == nullptr) continue;
			if (node->get_child(i)->get_name().compare(command_text) == 0) {										//datim stringom command_text. Ukoliko postoji ući ćemo u njega
				node = node->get_child(i);
				found = true;
			}
		}
	}
}

void Commands::NEW(TreeNode*& node, string name, string text) {

	if (text.size() == 0) {
		node->set_child_folder(name, TreeNode::Type::FOLDER);																//Ukoliko ne postoji text pravimo čvor tipa folder 
		TreeNode* temp = nullptr;
		for (int i = 0; i < node->get_size(); i++) temp = node->get_child(i);
		temp->set_parent(node);																						//Nakon dodavanja novog čvora vršimo sortiranje celog stabla
	}
	else {
		node->set_child_file(name, text, TreeNode::Type::FILE);															//Ukoliko postoji text, pravimo novi čvor tipa fajl i posle dodavanja vršimo sortiranje
		TreeNode* temp = nullptr;
		for (int i = 0; i < node->get_size(); i++) temp = node->get_child(i);
		temp->set_parent(node);
	}
}

void Commands::DEL(TreeNode*& node, string read, stack<TreeNode*>& last_visited, bool& found) {
	TreeNode* curr = node;
	for (int i = 0; i < curr->get_size(); i++) {																	//Obilazimo sinove trenutnog čvora u kom se nalazimo. Ukoliko neko dete ima isto ime kao 
		if (curr->get_child(i) == nullptr) {
			continue;
		}
		else if (curr->get_child(i)->get_name().compare(read) == 0) {													//string read brišemo dati čvor
			last_visited.push(curr);
			curr = curr->get_child(i);																					
			curr->delete_child(curr->get_parent(), i);
			delete curr;
			found = true;
			curr = last_visited.top();
			last_visited.pop();
		}
	}
}

void Commands::EXE(TreeNode*& node, string read, fstream& output, bool& first_line, bool& found) {
	TreeNode* curr = node;
	stack<TreeNode*> last_visited;
	for (int i = 0; i < node->get_size(); i++) {
		if (node->get_child(i) != nullptr && node->get_child(i)->get_name().compare(read) == 0) {					//Kao i u funkciji DEL obilazimo sinove trenutnog čvora. Ukoliko neko od dece ima isto ime
			last_visited.push(curr);																				//kao string read, curr prebacujemo na taj čvor koji je tipa fajl.exe.
			curr = curr->get_child(i);
			found = true;
			string temp;
			char c;
			int j = 0;
			while (j < curr->get_text().size()) {
				try {																								//Prolazimo kroz text samog fajla i u string temp upisujemo pročitano. Čitanjem neke od ključnih
																													//reči za pozive funkcija ulazimo u postupak za pozivanje funkcija kao i pri čitanju iz datoteka commands
					c = curr->get_text().at(j);
					temp.push_back(c);

					if (temp == "LS") throw new CommandLs();
					if (temp == "CD") throw new CommandCd();
					if (temp == "NEW") throw new CommandNew();
					if (temp == "DEL") throw new CommandDel();
					if (temp == "EXE") throw new CommandExe();
					j++;
				}

				catch (CommandLs*) {																				//Postupak kreiranja komandi sličan je već prethodno objašnjenom postupku kroz sve ove funkcije
					queue<TreeNode*> road;
					stack<TreeNode*> last_visited;																	//Ukoliko naiđemo na neku grešku bacamo izuzetke
					LS(node, node, output, road, last_visited, first_line);
					temp.clear();
					j += 3;
				}
				catch (CommandCd*) {
					bool found = false;
					string name;
					j += 2;
					while (j < curr->get_text().size()) {
						c = curr->get_text().at(j);
						if (c == '\n') break;
						if (c == '\\') {
							j++;
							c = curr->get_text().at(j);
							if (c == 'n') break;
							else {
								name[j - 1] = '\\';
								name[j] = c;
							}
						}
						name.push_back(c);
						++j;
					}
					CD(node, name, found);
					if (found == false) throw new ErrorExe;
					temp.clear();
					++j;

				}
				catch (CommandNew*) {
					++j;
					string name, text;

					while (1) {
						++j;
						c = curr->get_text().at(j);
						if (c == ' ') break;
						if (c == '\n') break;
						if (c == '\\') {
							j++;
							c = curr->get_text().at(j);
							if (c == 'n') break;
							else {
								name[j - 1] = '\\';
								name[j] = c;
							}
						}
						name.push_back(c);

					}
					if (c == ' ') {
						while (1) {
							++j;
							c = curr->get_text().at(j);
							if (c == '\n') break;
							if (c == '\\') {
								j++;
								c = curr->get_text().at(j);
								if (c == 'n') break;
								else {
									name[j - 1] = '\\';
									name[j] = c;
									j++;
								}
							}
							text.push_back(c);
						}
					}
					NEW(node, name, text);
					node->sort(node, last_visited);
					temp.clear();
					j++;
				}
				catch (CommandDel*) {
					bool found = false;
					string name;
					j += 2;
					while (1) {
						c = curr->get_text().at(j);
						if (c == '\n') break;
						if (c == '\\') {
							j++;
							c = curr->get_text().at(j);
							if (c == 'n') break;
							else {
								name[j - 1] = '\\';
								name[j] = c;
								j++;
							}
						}
						name.push_back(c);
						j++;
					}
					stack<TreeNode*> last_visited;
					DEL(node, name, last_visited, found);
					if (found == false) throw new ErrorExe;
					temp.clear();
					j++;
				}
				catch (CommandExe*) {
					bool found = false;
					string name;
					j += 2;
					while (1) {
						c = curr->get_name().at(j);
						if (c == '\n') break;
						name.push_back(c);
						j++;
					}
					EXE(node, name, output, first_line, found);
					if (found == false) throw new ErrorExe;
					temp.clear();
				}

			}
		}
	}
}
