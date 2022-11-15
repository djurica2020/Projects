#ifndef ISPIS_U_FAJL
#define ISPIS_U_FAJL


#include "Stajalista.h"

using namespace std;

class IspisUFajl {
public:
	void prikazi_osnovne_informacije(int stajaliste, Linije* linije, string putanja, Stajalista* stajalista);
	void prikazi_liniju(string ime, Linije* linije, Stajalista* stajalista, string putanja);
	void prikazi_statisticke_informacije(Linije* linije, string ime, string putanja);
	void prikazi_putanju(string ime, Linije* linije, vector<int> putanja_stajalista, string putanja_fajla);
};

#endif