#include "Linije.h"

Linije::Linije(string ime, vector<int> pozitivan, vector<int> negativan, vector<int> sve_stanice) : naziv_linije_(ime), pravac_pozitivan_(pozitivan), pravac_negativan_(negativan), sve_stanice_(sve_stanice) {}

Linije::Linije(const string& linije) {
	char c;
	int i = 0;
	c = linije.at(i);
	string ime;
	while (i < linije.size()) {
		while (c != ' ') {
			ime.push_back(c);
			i++;
			c = linije.at(i);
		}
		i++;
		c = linije.at(i);
		vector<int> pozitivan;
		int priv = 0;
		while (1) {
			priv = priv * 10 + (c - '0');
			i++;
			c = linije.at(i);
			if (c == ' ' || c == '#') {
				pozitivan.push_back(priv);
				i++;
				if (c == '#') break;
				c = linije.at(i);
				priv = 0;
				continue;
			}
		}
		c = linije.at(i);
		vector<int> negativan;
		priv = 0;
		while (1) {
			if (i == linije.size()) break;
			priv = priv * 10 + (c - '0');
			i++;
			if (i != linije.size()) c = linije.at(i);
			if (c == ' ' || c == '\n' || i == linije.size()) {
				negativan.push_back(priv);
				if (i != linije.size()) i++;
				if (c == '\n') break;
				if (i != linije.size()) c = linije.at(i);
				priv = 0;
				continue;
			}
		}
		vector<int> sve_stanice;
		for (int i = 0; i < pozitivan.size(); i++) {
			sve_stanice.push_back(pozitivan.at(i));
		}
		for (int i = 0; i < negativan.size(); i++) {
			sve_stanice.push_back(negativan.at(i));
		}
		Linije* nova = new Linije(ime, pozitivan, negativan, sve_stanice);
		niz_linija_.push_back(nova);
		ime.clear();
		if (i != linije.size()) c = linije.at(i);
	}
}

Linije::~Linije() {
	naziv_linije_.clear();
	pravac_pozitivan_.clear();
	pravac_negativan_.clear();
	sve_stanice_.clear();
}

Linije::Linije(const Linije*& linije) {
	naziv_linije_.assign(linije->naziv_linije_);
	for (int i = 0; i < linije->niz_linija_.size(); i++) {
		niz_linija_.push_back(linije->niz_linija_.at(i));
	}
	for (int i = 0; i < linije->pravac_pozitivan_.size(); i++) {
		pravac_pozitivan_.push_back(linije->pravac_pozitivan_.at(i));
	}
	for (int i = 0; i < linije->pravac_negativan_.size(); i++) {
		pravac_negativan_.push_back(linije->pravac_negativan_.at(i));
	}
	for (int i = 0; i < linije->sve_stanice_.size(); i++) {
		sve_stanice_.push_back(linije->sve_stanice_.at(i));
	}

}

Linije::Linije(Linije*&& linije) {
	naziv_linije_.assign(linije->naziv_linije_);
	for (int i = 0; i < linije->niz_linija_.size(); i++) {
		niz_linija_.push_back(linije->niz_linija_.at(i));
	}
	for (int i = 0; i < linije->pravac_pozitivan_.size(); i++) {
		pravac_pozitivan_.push_back(linije->pravac_pozitivan_.at(i));
	}
	for (int i = 0; i < linije->pravac_negativan_.size(); i++) {
		pravac_negativan_.push_back(linije->pravac_negativan_.at(i));
	}
	for (int i = 0; i < linije->sve_stanice_.size(); i++) {
		sve_stanice_.push_back(linije->sve_stanice_.at(i));
	}
	linije->naziv_linije_.clear();
	linije->niz_linija_.clear();
	linije->pravac_pozitivan_.clear();
	linije->pravac_negativan_.clear();
	linije->sve_stanice_.clear();
}

string Linije::vrati_ime() const {
	return naziv_linije_;
}

Linije* Linije::vrati_liniju_na_poziciji(int n) const {
	return niz_linija_.at(n);
}

int Linije::vrati_stanicu_u_pozitivnom_smeru(int n) const {
	return pravac_pozitivan_.at(n);
}

int Linije::vrati_stanicu_u_negativnom_smeru(int n) const {
	return pravac_negativan_.at(n);
}

int Linije::vrati_broj_linija() const {
	return niz_linija_.size();
}

int Linije::vrati_broj_stanica() const {
	return pravac_pozitivan_.size();
}

int Linije::vrati_ukupan_broj_stanica() const {
	return this->sve_stanice_.size();
}

int Linije::vrati_stanicu_na_poziciji(int n) const {
	return this->sve_stanice_.at(n);
}

void Linije::nadji_zajednicke_linije(int prvo, int drugo, vector<string>& posecene) const {

	bool prekini;

	for (int i = 0; i < niz_linija_.size(); i++) {
		prekini = false;
		for (int k = 0; k < niz_linija_.at(i)->sve_stanice_.size(); k++) {
			if (prvo == niz_linija_.at(i)->sve_stanice_.at(k)) {
				for (int l = 0; l < niz_linija_.at(i)->sve_stanice_.size(); l++) {
					if (drugo == niz_linija_.at(i)->sve_stanice_.at(l)) {
						posecene.push_back(niz_linija_.at(i)->naziv_linije_);
						prekini = true;
					}
					if (prekini == true) break;
				}
			}
			if (prekini == true) break;
		}
	}
}

bool Linije::proveri_stanicu(string linija, int stanica) const {
	for (int i = 0; i < niz_linija_.size(); i++) {
		if (linija.compare(niz_linija_.at(i)->naziv_linije_) == 0) {
			for (int j = 0; j < niz_linija_.at(i)->sve_stanice_.size(); j++) {
				if (niz_linija_.at(i)->sve_stanice_.at(j) == stanica) return true;
			}
		}
	}
	return false;
}
