/**
 * \file ArbreGenealogique.h
 * \brief interface de la classe arbre genealogique
 * \author mario
 * \version 0.1
 * \date 2015
 */

#ifndef ARBREGENEALOGIQUE_H_
#define ARBREGENEALOGIQUE_H_
#include <vector>
#include <list>
#include <map>
#include <stdexcept>
#include "Personne.h"
#include "Adresse.h"

/**
 * \class ArbreGenealogique
 *
 * \brief classe générique représentant un Arbre Genealogique.
 *
 *  La classe gère un arbre Genealogique.
 *  L'implémentation se fait par listes.
 */
class ArbreGenealogique
{
public:

	typedef std::map<Personne,Adresse>::const_iterator pEntree;

	ArbreGenealogique();
	ArbreGenealogique(pEntree p_personne_it);
	ArbreGenealogique(const ArbreGenealogique & p_source);
	~ArbreGenealogique();

	const ArbreGenealogique & operator=(const ArbreGenealogique & p_source);

	void ajouterEnfant(pEntree p_parent_it, pEntree p_enfant_it);
	bool appartient(pEntree p_personne_it) const;
	std::string reqNom() const;

	friend std::ostream& operator <<(std::ostream& p_out, const ArbreGenealogique& p_arbreG);

private:
	class Noeud
	{
	public:
		pEntree m_personne_it; /*!< Pointe sur une entrée du bottin*/
		std::list<Noeud *> m_enfants; /*!< Liste des enfants de cette personne*/
		Noeud(pEntree p_personne_it) : m_personne_it(p_personne_it)
		{
		}
	};

	Noeud * m_racine; //!< La m_racine de l'arbre généalogique: pointe sur le Noeud de l'ancêtre
	std::string m_nom;//!< Le nom de l'arbre généalogique (= nom de l'ancêtre)
	bool appartient(Noeud *p_noeud, pEntree p_personne_it) const;
	std::string preordre(Noeud *p_noeud) const;
	void detruireNoeuds(Noeud *p_noeud);
	Noeud * noeudPEntree(pEntree pEntree, Noeud *p_noeud);
	void copierUnArbre(Noeud* p_source, Noeud* p_noeudDepart);

};

#endif /* ARBREGENEALOGIQUE_H_ */
