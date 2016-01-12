/**
 * \file Annuaire.h
 * \brief interface de la classe annuaire genealogique
 * \author mario
 * \version 0.1
 * \date 2015
 */

#ifndef ANNUAIRE_H_
#define ANNUAIRE_H_
#include <fstream>		// Pour les fichiers
#include <map>
#include <vector>
#include <list>
#include "ArbreGenealogique.h"
#include "Personne.h"
#include "Adresse.h"


class Annuaire
{
public:
	Annuaire(std::ifstream & p_fichierEntree);
	void inscrire(const Personne& p_personne, const Adresse& p_adresse);
	void ajouterParentEnfant(const Personne& p_parent, const Personne& p_enfant);
	friend std::ostream& operator <<(std::ostream& p_out,
			const Annuaire& p_annuaire);

private:
	std::map<Personne,Adresse> m_bottin;
	std::list<ArbreGenealogique> m_listeArbreGene;//! La liste contenant les arbres généalogique par famille
};

#endif /* ANNUAIRE_H_ */
