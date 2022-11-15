#ifndef STAJALISTA_H
#define STAJALISTA_H

#include "Linije.h"

#include <string>
#include<stack>

using namespace std;

class Stajalista {

public:
	Stajalista();
	Stajalista(string stajalista);
	~Stajalista();
	Stajalista(const Stajalista*& stajalista);
	Stajalista(Stajalista*&& stajalista);

	int vrati_ukupan_broj_stajalista();
	int vrati_broj();
	int prikazi_indeks_stajalista(int broj);
	int pretvori_indeks(int indeks);
	int nadji_zajednicku_liniju(int prvo, int drugo);
	string nadji_stajaliste(Stajalista* stajalista, int broj);
	string vrati_ime();
	Stajalista* vrati_prvo();
	Stajalista* vrati_sledece();
	vector<int> napravi_listu_stajalista(Stajalista* prvo, Stajalista* poslednje);
	

private:
	int broj_;
	int indeks_;
	int broj_stajalista_;
	string ime_;
	Stajalista* prvo_, * sledece_, * poslednje_;
	vector<int> sva_stajalista_;
	
};

#endif