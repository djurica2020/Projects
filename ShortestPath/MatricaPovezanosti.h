#ifndef MATRICA_POVEZANOSTI
#define MATRICA_POVEZANOSTI

#include "Stajalista.h"

#include <stack>

using namespace std;

class MatricaPovezanosti {
public:
	MatricaPovezanosti(int dimenzija);
	~MatricaPovezanosti();
	MatricaPovezanosti(const MatricaPovezanosti*& matrica);
	MatricaPovezanosti(MatricaPovezanosti*&& matrica);
	int** popuni_matricu(Stajalista* stajalista, Linije* linije);
	void nadji_najkrace_rastojanje(int** graf, int dimenzija, int pocetak, int kraj, Stajalista* stajalista, vector<int>& putanja);

private:
	int** matrica_, dimenzija_;
};

#endif