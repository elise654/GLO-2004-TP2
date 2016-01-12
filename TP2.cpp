//============================================================================
// Name        : TP2.cpp
// Author      : Mario
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <fstream>

#include "Annuaire.h"

using namespace std;

int main() {

	ifstream fichier;
	fichier.open("test.txt");
	Annuaire monAnnuaire(fichier);
	cout << monAnnuaire << endl;

	cout << "Fin normale" << endl;

	return 0;
}
