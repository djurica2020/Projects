#include "IspisUFajl.h"

void IspisUFajl::prikazi_osnovne_informacije(int stajaliste, Linije* linije, string putanja, Stajalista* stajalista) {
	int i = 0;
	for (i; i < putanja.size();) {
		if (putanja.at(i) != '\\') i++;
		else break;
	}
	string naziv;
	int j = 0;
	while (j < i) {
		naziv.push_back(putanja.at(j));
		j++;
	}
	naziv.push_back('/');
	
	UpisIObrada* upis_ispis = new UpisIObrada();
	upis_ispis->napravi_ime("stajaliste_", naziv, to_string(stajaliste));

	fstream izlaz(naziv, ios::out);

	izlaz << to_string(stajaliste) << ' ';
	for (Stajalista* priv = stajalista->vrati_prvo(); priv; priv = priv->vrati_sledece()) {
		if (priv->vrati_broj() - stajaliste == 0) {
			izlaz << priv->vrati_ime();
			break;
		}
	}
	vector<string> linije_za_ispis;
	for (int i = 0; i < linije->vrati_broj_linija(); i++) {
		Linije* priv = linije->vrati_liniju_na_poziciji(i);
		for (int j = 0; j < linije->vrati_liniju_na_poziciji(i)->vrati_broj_stanica(); j++) {
			if (stajaliste == linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_negativnom_smeru(j) || stajaliste == linije->vrati_liniju_na_poziciji(i)->vrati_stanicu_u_pozitivnom_smeru(j)) {
				linije_za_ispis.push_back(linije->vrati_liniju_na_poziciji(i)->vrati_ime());
				break;
			}
		}
	}

	UpisIObrada* upis_obrada = new UpisIObrada();

	upis_obrada->sortiraj(linije_za_ispis);

	izlaz << " [";
	for (int i = 0; i < linije_za_ispis.size(); i++) {
		if (i < linije_za_ispis.size() - 1) izlaz << linije_za_ispis.at(i) << " ";
		else izlaz << linije_za_ispis.at(i);
	}
	izlaz << "]";

	linije_za_ispis.clear();
}

void IspisUFajl::prikazi_liniju(string ime, Linije* linije, Stajalista* stajalista, string putanja) {
	int i = 0;
	for (i; i < putanja.size();) {
		if (putanja.at(i) != '\\') i++;
		else break;
	}

	string naziv;
	int j = 0;
	while (j < i) {
		naziv.push_back(putanja.at(j));
		j++;
	}
	naziv.push_back('/');
	UpisIObrada* upis_obrada = new UpisIObrada();
	upis_obrada->napravi_ime("linija_", naziv, ime);

	fstream izlaz(naziv, ios::out);


	Linije* priv = nullptr;
	for (int i = 0; i < linije->vrati_broj_linija(); i++) {
		if (ime.compare(linije->vrati_liniju_na_poziciji(i)->vrati_ime()) == 0) {
			priv = linije->vrati_liniju_na_poziciji(i);
			break;
		}
	}

	if (priv != nullptr) {
		izlaz << ime << " ";
		int t;
		t = priv->vrati_stanicu_u_pozitivnom_smeru(0);
		string stajaliste = stajalista->nadji_stajaliste(stajalista, t);
		izlaz << stajaliste << "->";
		t = priv->vrati_stanicu_u_pozitivnom_smeru(priv->vrati_broj_stanica() - 1);
		stajaliste = stajalista->nadji_stajaliste(stajalista, t);
		izlaz << stajaliste << endl;

		for (int i = 0; i < priv->vrati_broj_stanica(); i++) {
			t = priv->vrati_stanicu_u_pozitivnom_smeru(i);
			string stajaliste = stajalista->nadji_stajaliste(stajalista, t);
			izlaz << to_string(priv->vrati_stanicu_u_pozitivnom_smeru(i)) << " " << stajaliste << endl;
		}

		for (int i = 0; i < priv->vrati_broj_stanica(); i++) {
			t = priv->vrati_stanicu_u_negativnom_smeru(i);
			string stajaliste = stajalista->nadji_stajaliste(stajalista, t);
			izlaz << to_string(priv->vrati_stanicu_u_negativnom_smeru(i)) << " " << stajaliste;
			if (i != priv->vrati_broj_stanica() - 1) izlaz << endl;
		}

	}
}

void IspisUFajl::prikazi_statisticke_informacije(Linije* linije, string ime, string putanja) {
	int i = 0;
	for (i; i < putanja.size();) {
		if (putanja.at(i) != '\\') i++;
		else break;
	}

	string naziv;
	int j = 0;
	while (j < i) {
		naziv.push_back(putanja.at(j));
		j++;
	}
	naziv.push_back('/');
	UpisIObrada* upis_obrada = new UpisIObrada();
	upis_obrada->napravi_ime("statistika_", naziv, ime);

	fstream izlaz(naziv, ios::out);

	Linije* priv = nullptr;
	i = 0;
	for (i; i < linije->vrati_broj_linija(); i++) {
		if (linije->vrati_liniju_na_poziciji(i)->vrati_ime().compare(ime) == 0) {
			priv = linije->vrati_liniju_na_poziciji(i);
			break;
		}
	}

	vector<string> linije_sa_zajednickim;
	j = 0;
	for (j; j < linije->vrati_broj_linija(); j++) {
		if (j == i) continue;
		else {
			for (int k = 0; k < priv->vrati_ukupan_broj_stanica(); k++) {
				for (int l = 0; l < linije->vrati_liniju_na_poziciji(j)->vrati_ukupan_broj_stanica(); l++) {
					if (priv->vrati_stanicu_na_poziciji(k) == linije->vrati_liniju_na_poziciji(j)->vrati_stanicu_na_poziciji(l)) {
						linije_sa_zajednickim.push_back(linije->vrati_liniju_na_poziciji(j)->vrati_ime());
					}
				}
			}
		}

	}
	vector<string> zajednicke;
	string linija_maks;
	int maks = 0, maks_tren = 0, m = 0;
	while (m < linije_sa_zajednickim.size()) {
		string tren = linije_sa_zajednickim.at(m);
		zajednicke.push_back(tren);
		if (tren.size() != 0) {
			maks_tren++;
		}
		++m;
		for (m; tren.compare(linije_sa_zajednickim.at(m)) == 0;) {
			maks_tren++;
			m++;
			if (m == linije_sa_zajednickim.size()) break;
		}
		if (maks_tren > maks) {
			maks = maks_tren;
			linija_maks = tren;
		}
		maks_tren = 0;
	}

	upis_obrada->sortiraj(zajednicke);

	izlaz << ime << endl;

	i = 0;
	while (i < zajednicke.size()) {
		if (i != zajednicke.size() - 1) {
			izlaz << zajednicke.at(i) << " ";
		}
		else izlaz << zajednicke.at(i) << endl;
		i++;
	}

	izlaz << linija_maks;
}

void IspisUFajl::prikazi_putanju(string ime, Linije* linije, vector<int> putanja_stanica, string putanja_fajla) {

	int i = 0;
	for (i; i < putanja_fajla.size();) {
		if (putanja_fajla.at(i) != '\\') i++;
		else break;
	}

	string naziv;
	int j = 0;
	while (j < i) {
		naziv.push_back(putanja_fajla.at(j));
		j++;
	}
	naziv.push_back('/');
	UpisIObrada* upis_obrada = new UpisIObrada();
	upis_obrada->napravi_ime("putanja_", naziv, ime);

	fstream izlaz(naziv, ios::out);

	vector<string> stek_linija_1;
	vector<string> stek_linija_2;

	vector<string> niz_linija;

	i = 0, j = 1;

	bool nadjeno;
	for (; j < putanja_stanica.size(); i++, j++) {
		if (stek_linija_2.empty() == true) {
			linije->nadji_zajednicke_linije(putanja_stanica.at(i), putanja_stanica.at(j), stek_linija_1);
			stek_linija_2.swap(stek_linija_1);
			stek_linija_1.clear();
			upis_obrada->sortiraj(stek_linija_2);
		}
		else {
			nadjeno = false;
			linije->nadji_zajednicke_linije(putanja_stanica.at(i), putanja_stanica.at(j), stek_linija_1);
			
			upis_obrada->sortiraj(stek_linija_1);
			
			for (int m = 0; m < stek_linija_1.size(); m++) {
				for (int n = 0; n < stek_linija_2.size(); n++) {
					if (stek_linija_1.at(m).compare(stek_linija_2.at(n)) == 0) {
						if (niz_linija.size() != 0 && niz_linija.at(niz_linija.size() - 1).compare(stek_linija_1.at(m)) != 0) niz_linija.push_back(stek_linija_1.at(m));
						else if (niz_linija.size() == 0) niz_linija.push_back(stek_linija_1.at(m));
						stek_linija_2.swap(stek_linija_1);
						stek_linija_1.clear();
						nadjeno = true;
						break;
					}
				}
				if (nadjeno == true) break;
			}
			if (nadjeno == false) {
				upis_obrada->sortiraj(stek_linija_2);
				niz_linija.push_back(stek_linija_2.at(0));
			}

		}
	}

	int cnt = 0;

	izlaz << "->" << niz_linija.at(cnt) << endl;

	i = 0;

	bool prva_linija = true;

	while (cnt < niz_linija.size() && i < putanja_stanica.size()) {
		if (linije->proveri_stanicu(niz_linija.at(cnt), putanja_stanica.at(i)) == true) {
			if (prva_linija == true) {
				izlaz << putanja_stanica.at(i);
				prva_linija = false;
			}
			else izlaz << " " << putanja_stanica.at(i);
			i++;
		}
		else {
			i--;
			izlaz << endl << niz_linija.at(cnt++) << "->" << niz_linija.at(cnt) << endl;
			prva_linija = true;
		}
	}
}
