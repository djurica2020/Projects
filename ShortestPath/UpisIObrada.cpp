#include "UpisIObrada.h"

void UpisIObrada::citaj_liniju(string& procitano) {
	char c = cin.get();
	if (c != '\n') procitano.push_back(c);
	while (1) {
		c = cin.get();
		if (c == '\n') break;
		else procitano.push_back(c);
	}
}

void UpisIObrada::napravi_ime(string tip, string& naziv, string a) {
	naziv.append(tip);
	naziv.append(a);
	naziv.append(".txt");
}

void UpisIObrada::sortiraj(vector<string> &stringovi) {
	for (int m = 0; m < stringovi.size(); m++) {
		for (int n = m + 1; n < stringovi.size(); n++) {
			if (stringovi.at(m).compare(stringovi.at(n)) > 0) {
				string priv = stringovi.at(m);
				stringovi.at(m) = stringovi.at(n);
				stringovi.at(n) = priv;
			}
		}
	}
}

