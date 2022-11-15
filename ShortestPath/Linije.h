#ifndef LINIJE_H
#define LINIJE_H

#include "UpisIObrada.h"

#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Linije {
public:
	Linije(string ime, vector<int> pozitivan, vector<int> negativan, vector<int> sve_stanice);
	Linije(const string& linije);
	~Linije();
	Linije(const Linije*& linije);
	Linije(Linije*&& linije);

	string vrati_ime() const;
	Linije* vrati_liniju_na_poziciji(int n) const;
	int vrati_stanicu_u_pozitivnom_smeru(int n) const;
	int vrati_stanicu_u_negativnom_smeru(int n) const;
	int vrati_broj_linija() const;
	int vrati_broj_stanica() const;
	int vrati_ukupan_broj_stanica() const;
	int vrati_stanicu_na_poziciji(int n) const;
	void nadji_zajednicke_linije(int prvo, int drugo, vector<string> &posecene) const;
	bool proveri_stanicu(string linija, int stanica) const;

private:
	string naziv_linije_;
	vector<Linije*> niz_linija_;
	vector<int> pravac_pozitivan_;
	vector<int> pravac_negativan_;
	vector<int> sve_stanice_;

};

#endif