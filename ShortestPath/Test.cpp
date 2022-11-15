#include "UpisIObrada.h"
#include "Linije.h"
#include "Stajalista.h"
#include "MatricaPovezanosti.h"
#include "IspisUFajl.h"
#include "Izuzeci.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void main() {
	try {
		//Definisanje klase u kojoj su nam osnovne funkcije za upis i ispis
		UpisIObrada* upis_obrada = new UpisIObrada();

		string a;
		cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:" << endl << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl << "0. Kraj rada" << endl << endl;
		while (1) {
			cin >> a;
			if (a.compare("0") == 0) exit(-1);
			else if (a.compare("1") == 0) break;
			else cout << endl << "Izabrana opcija nije ponudjena. Molimo Vas, pokusajte ponovo. Moguci izbori su 0 i 1:" << endl;
		}
		//Putanja do fajla stajalista.txt i prepisivanje fajla u string
		cout << endl << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
		string fajl_stajalista;
		upis_obrada->citaj_liniju(fajl_stajalista);
		fstream ulaz_stajalista(fajl_stajalista, ios::in);
		string stajalista;
		while (1) {
			char c;
			c = ulaz_stajalista.get();
			if (c == EOF) break;
			else stajalista.push_back(c);
		}
		if (stajalista.empty()) throw new Izuzeci("Fajl sa stajalistima nije otvoren");
		//Cuvanje liste svih stajalista i njihovih imena
		Stajalista* lista_stajalista = new Stajalista(stajalista);

		//Putanja do fajla linije.txt i prepisivanje fajla u string
		cout << endl << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl;
		string fajl_linije;
		upis_obrada->citaj_liniju(fajl_linije);
		fstream ulaz_linije(fajl_linije, ios::in);
		string linije;
		while (1) {
			char c;
			c = ulaz_linije.get();
			if (c == EOF) break;
			else linije.push_back(c);
		}
		if (linije.empty()) throw new Izuzeci("Fajl za linijama nije otvoren");
		//Cuvanje informacija o imenima linija i njihovim stajalistima
		Linije* lista_linija = new Linije(linije);

		//Definisanje klase matrice povezanosti grafa
		MatricaPovezanosti* matrica = new MatricaPovezanosti(lista_stajalista->vrati_ukupan_broj_stajalista());

		//Definisanje klase za ispis u fajl
		IspisUFajl* ispis = new IspisUFajl();

		//Definisanje same matrice tipa int** u koju cemo smestiti povezanost
		int** matrica_povezanosti;

		//Definisanje vektora putanje
		vector<int> putanja;

		cout << endl << "1. Prikaz informacija o stajalistu" << endl << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl << "3. Prikaz statistickih informacija o liniji gradskog prevoza" <<
			endl << "4. Pronalazak putanje izmedju dva stajalista" << endl << "0. Kraj rada" << endl << endl;
		int b;
		cin >> b;

		while (b < 0 || b > 4) {
			cout << "Nepodrzan izbor. Moguci izbori su 1, 2, 3, 4 i 0. Molimo Vas, pokusajte ponovo:" << endl;
			cin >> b;
		}

		string naziv, ime;
		switch (b) {
		case 1:
			cout << endl << "Molimo Vas, unesite oznaku stajalista cije informacije zelite da prikazete." << endl;
			int b;
			cin >> b;
			cout << "Kreiran je tekstualni fajl ";
			ispis->prikazi_osnovne_informacije(b, lista_linija, fajl_stajalista, lista_stajalista);
			upis_obrada->napravi_ime("stajaliste_", naziv, to_string(b));
			cout << naziv;
			naziv.clear();
			break;
		case 2:
			cout << endl << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
			cin >> ime;
			cout << "Kreiran je tekstualni fajl ";
			ispis->prikazi_liniju(ime, lista_linija, lista_stajalista, fajl_stajalista);
			upis_obrada->napravi_ime("linija_", naziv, ime);
			cout << naziv;
			naziv.clear();
			break;
		case 3:
			cout << endl << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da prikazete." << endl;
			cin >> ime;
			cout << "Kreiran je tekstualni fajl ";
			ispis->prikazi_statisticke_informacije(lista_linija, ime, fajl_stajalista);
			upis_obrada->napravi_ime("statistika_", naziv, ime);
			cout << naziv;
			naziv.clear();
			break;
		case 4:
			cout << endl << "Molimo Vas, unesite pocetno i krajnje stajaliste rute koju zelite da prikazete." << endl;
			matrica_povezanosti = matrica->popuni_matricu(lista_stajalista, lista_linija);

			int pocetak, kraj;

			cin >> pocetak;
			cin >> kraj;

			ime.append(to_string(pocetak));
			ime.append("_");
			ime.append(to_string(kraj));

			upis_obrada->napravi_ime("putanja_", naziv, ime);

			pocetak = lista_stajalista->prikazi_indeks_stajalista(pocetak);
			kraj = lista_stajalista->prikazi_indeks_stajalista(kraj);

			matrica->nadji_najkrace_rastojanje(matrica_povezanosti, lista_stajalista->vrati_ukupan_broj_stajalista(), pocetak, kraj, lista_stajalista, putanja);

			ispis->prikazi_putanju(ime, lista_linija, putanja, fajl_stajalista);

			cout << "Kreiran je tekstualni fajl ";
			cout << naziv;
			naziv.clear();
			break;
		case 0:
			exit(-1);
			break;
		default:
			break;
		}
		delete upis_obrada;
		upis_obrada = nullptr;
		delete lista_linija;
		lista_linija = nullptr;
		delete lista_stajalista;
		lista_stajalista = nullptr;
		delete ispis;
		ispis = nullptr;
		delete matrica;
		matrica = nullptr;
		matrica_povezanosti = nullptr;
	}
	catch (Izuzeci* e) { cout << e->what(); }
}