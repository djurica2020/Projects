#include "Stajalista.h"

#include <fstream>
#include <iostream>
using namespace std;

Stajalista::Stajalista() : prvo_(nullptr), sledece_(nullptr), poslednje_(nullptr), broj_(0), broj_stajalista_(0), indeks_(0), ime_("") {}

Stajalista::Stajalista(string stajalista) : prvo_(nullptr), sledece_(nullptr), poslednje_(nullptr), broj_(0), broj_stajalista_(0), indeks_(0), ime_("") {
	char c;
	int i = 0;
	while (i < stajalista.size()) {
		Stajalista* nov = new Stajalista();
		c = stajalista.at(i);
		while (c != ' ') {
			nov->broj_ = nov->broj_ * 10 + (c - '0');
			i++;
			c = stajalista.at(i);
		}
		i++;
		c = stajalista.at(i);
		while (c != '\n') {
			nov->ime_.push_back(c);
			i++;
			if (i == stajalista.size()) break;
			c = stajalista.at(i);
		}
		if (prvo_ == nullptr) prvo_ = nov;
		else poslednje_->sledece_ = nov;
		poslednje_ = nov;
		broj_stajalista_++;
		i++;
	}

	sva_stajalista_ = napravi_listu_stajalista(prvo_, poslednje_);
}

Stajalista::~Stajalista() {
	for (Stajalista* priv = prvo_; priv;) {
		priv->broj_ = priv->broj_stajalista_ = priv->indeks_ = 0;
		priv->ime_.clear();
		priv->sva_stajalista_.clear();
		priv->prvo_ = nullptr;
		Stajalista* tren = priv;
		priv = priv->sledece_;
		tren = nullptr;
	}
	broj_ = broj_stajalista_ = indeks_ = 0;
	ime_.clear();
	sva_stajalista_.clear();

}

Stajalista::Stajalista(const Stajalista*& stajalista) {
}

Stajalista::Stajalista(Stajalista*&& stajalista) {
}

int Stajalista::vrati_ukupan_broj_stajalista() {
	return sva_stajalista_.size();
}

int Stajalista::vrati_broj() {
	return broj_;
}

string Stajalista::nadji_stajaliste(Stajalista* stajalista, int broj) {
	for (Stajalista* priv = stajalista->prvo_; priv; priv = priv->sledece_) {
		if (broj == priv->broj_) return priv->ime_;
	}
}

string Stajalista::vrati_ime() {
	return ime_;
}

Stajalista* Stajalista::vrati_prvo() {
	return prvo_;
}

Stajalista* Stajalista::vrati_sledece() {
	return sledece_;
}

vector<int> Stajalista::napravi_listu_stajalista(Stajalista* prvo, Stajalista* poslednje) {
	vector<int> niz;
	for (Stajalista* priv = prvo; priv; priv = priv->sledece_) {
		niz.push_back(priv->broj_);
	}
	
	for (int i = 0; i < niz.size(); i++) {
		for (int j = i + 1; j < niz.size(); j++) {
			if (niz.at(i) > niz.at(j)) {
				int c;
				c = niz.at(i);
				niz.at(i) = niz.at(j);
				niz.at(j) = c;
			}
 		}
	}

	for (Stajalista* priv = prvo; priv; priv = priv->sledece_) {
		int i = 0;
		for (; i < niz.size(); i++) {\
			if (priv->broj_ == niz.at(i)) {
				priv->indeks_ = i;
				break;
			}
		}
	}
	return niz;
}

int Stajalista::prikazi_indeks_stajalista(int broj) {
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		if (sva_stajalista_.at(i) == broj) return i;
	}
}

int Stajalista::pretvori_indeks(int indeks) {
	for (Stajalista* priv = prvo_; priv; priv = priv->sledece_) {
		if (priv->indeks_ == indeks) return priv->broj_;
	}
}

int Stajalista::nadji_zajednicku_liniju(int prvo, int drugo) {
	
	stack<int> linije;
	
	return 0;

}
