#ifndef  UPIS_I_OBRADA_H
#define UPIS_I_OBRADA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UpisIObrada {
public:
	void citaj_liniju(string& procitano);
	void napravi_ime(string tip, string& naziv, string a);
	void sortiraj(vector<string> &stringovi);
};

#endif 
