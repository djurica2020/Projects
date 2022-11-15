#include "MatricaPovezanosti.h"

#define inf 9999


MatricaPovezanosti::MatricaPovezanosti(int dimenzija) : dimenzija_(dimenzija) {
	matrica_ = new int* [dimenzija];

	for (int i = 0; i != dimenzija; i++) {
		matrica_[i] = new int[dimenzija];
	}

	for (int i = 0; i < dimenzija; i++) {
		for (int j = 0; j < dimenzija; j++) {
			matrica_[i][j] = 0;
		}
	}

}

MatricaPovezanosti::~MatricaPovezanosti() {
	for (int i = 0; i < dimenzija_; i++) {
		matrica_[i] = nullptr;
	}
	dimenzija_ = 0;
	matrica_ = nullptr;
}

MatricaPovezanosti::MatricaPovezanosti(const MatricaPovezanosti*& matrica) : dimenzija_(matrica->dimenzija_) {
	
	matrica_ = new int* [dimenzija_];

	for (int i = 0; i != dimenzija_; i++) {
		matrica_[i] = new int[dimenzija_];
	}

	for (int i = 0; i < dimenzija_; i++) {
		for (int j = 0; j < dimenzija_; j++) {
			matrica_[i][j] = 0;
		}
	}

	for (int i = 0; i < dimenzija_; i++) {
		for (int j = 0; j < dimenzija_; j++) {
			matrica_[i][j] = matrica_[i][j];
		}
	}
}

MatricaPovezanosti::MatricaPovezanosti(MatricaPovezanosti*&& matrica) : dimenzija_(matrica->dimenzija_) {
	matrica_ = new int* [dimenzija_];

	for (int i = 0; i != dimenzija_; i++) {
		matrica_[i] = new int[dimenzija_];
	}

	for (int i = 0; i < dimenzija_; i++) {
		for (int j = 0; j < dimenzija_; j++) {
			matrica_[i][j] = 0;
		}
	}

	for (int i = 0; i < dimenzija_; i++) {
		for (int j = 0; j < dimenzija_; j++) {
			matrica_[i][j] = matrica_[i][j];
		}
	}

	matrica->dimenzija_ = 0;
	for (int i = 0; i < dimenzija_; i++) {
		matrica[i] = nullptr;
	}
	matrica->matrica_ = nullptr;
	matrica = nullptr;
}

int** MatricaPovezanosti::popuni_matricu(Stajalista* stajalista, Linije* linije) {

	for (int i = 0; i < linije->vrati_broj_linija(); i++) {
		for (int j = 0; j < linije->vrati_liniju_na_poziciji(i)->vrati_broj_stanica() - 1; j++) {
			matrica_[stajalista->prikazi_indeks_stajalista(linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_pozitivnom_smeru(j))][stajalista->prikazi_indeks_stajalista(linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_pozitivnom_smeru(j + 1))] = 1;
			matrica_[stajalista->prikazi_indeks_stajalista(linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_negativnom_smeru(j))][stajalista->prikazi_indeks_stajalista(linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_negativnom_smeru(j + 1))] = 1;
		}
	}

	int k = 1;

	for (int i = 0; i < stajalista->vrati_ukupan_broj_stajalista(); i++) {
		for (int j = 0; j < stajalista->vrati_ukupan_broj_stajalista(); j++) {
			if (i == j) matrica_[i][j] = inf;
			else if (i != j && matrica_[i][j] != 1) matrica_[i][j] = inf;
			else matrica_[i][j] = k++;
		}
	}

	return matrica_;

}

void MatricaPovezanosti::nadji_najkrace_rastojanje(int** graf, int dimenzija, int pocetak, int kraj, Stajalista* stajalista, vector<int>& putanja) {


	int* udaljenost = new int[dimenzija], * prethodnik = new int[dimenzija];
	int* posecen = new int[dimenzija], brojac, minudaljenost, sledeci_cvor, i, j;


	//prethodnik cuva prethodnike svakog cvora
	//brojac nam daje broj obidjenih cvorova

	for (i = 0; i < dimenzija; i++)
	{
		udaljenost[i] = graf[pocetak][i]; //ovde
		prethodnik[i] = pocetak;
		posecen[i] = 0;
	}
	udaljenost[pocetak] = 0;
	posecen[pocetak] = 1;
	brojac = 1;
	while (brojac < dimenzija - 1)
	{
		minudaljenost = inf;
		//sledeci_cvor jeste cvor na minimalnoj udaljenosti
		for (i = 0; i < dimenzija; i++)
			if (udaljenost[i] < minudaljenost && !posecen[i])
			{
				minudaljenost = udaljenost[i];
				sledeci_cvor = i;
			}
		//proverava se da li postoji kraci put kroz sledeci_cvor
		posecen[sledeci_cvor] = 1;
		for (i = 0; i < dimenzija; i++)
			if (!posecen[i])
				if (minudaljenost + graf[sledeci_cvor][i] < udaljenost[i])     //ovde
				{
					udaljenost[i] = minudaljenost + graf[sledeci_cvor][i]; // ovde
					prethodnik[i] = sledeci_cvor;
				}
		brojac++;
	}

	//Cuvanje putanje u vektor putanja

	for (i = 0; i < dimenzija; i++) {
		if (i == kraj) {
			j = i;
			putanja.push_back(stajalista->pretvori_indeks(j));
			while (j != pocetak) {
				j = prethodnik[j];
				putanja.push_back(stajalista->pretvori_indeks(j));
			}
		}
	}

	for (i = 0, j = putanja.size() - 1; i < j; i++, j--) {
		int priv;
		priv = putanja.at(i);
		putanja.at(i) = putanja.at(j);
		putanja.at(j) = priv;

	}
}