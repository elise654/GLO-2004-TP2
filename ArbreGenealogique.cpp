/**
 * \file ArbreGenealogique.cpp
 * \brief implémentation de la classe arbre genealogique
 * \author mario
 * \version 0.1
 * \date 2015
 */

#include "ArbreGenealogique.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

//! \brief Constructeur sans paramètre
ArbreGenealogique::ArbreGenealogique()
{
	m_nom = "";
	m_racine = NULL;
}

//! \brief constructeur à un paramètre
ArbreGenealogique::ArbreGenealogique(pEntree p_personne_it)
{
	m_racine = new Noeud(p_personne_it);
	m_nom = p_personne_it->first.reqNom();
}

//! \brief constructeur de copie
ArbreGenealogique::ArbreGenealogique(const ArbreGenealogique & p_source)
{
	m_racine = new Noeud(p_source.m_racine->m_personne_it);
	copierUnArbre(p_source.m_racine, m_racine);
	m_nom = p_source.reqNom();
}

//! \brief Destructeur
ArbreGenealogique::~ArbreGenealogique()
{
	detruireNoeuds(m_racine);
}

//! \brief surcharge de l'opérateur =
const ArbreGenealogique & ArbreGenealogique::operator=(const ArbreGenealogique & p_source)
{
	ArbreGenealogique *nouvelArbre = new ArbreGenealogique(p_source);
	return *nouvelArbre;
}

//! \brief retourne le nom de l'arbre généalogique
string ArbreGenealogique::reqNom() const
{
	return m_nom;
}

//! \brief Ajouter un enfant (ou possiblement son parent) dans un arbre genealogique
//!			Le parent peut appartenir à un arbre généalogique ssi il a le même nom que celui de l'arbre généalogique.
//!			Le nom d'un enfant doit être celui d'un de ses parents (mais il est possiblement différent de celui du parent pour cet appel).
//!			Un enfant se trouvant dans un arbre généalogique d'un nom différent sera donc une feuille: les efants de cet enfant seront dans un autre arbre généalogique.
//!			Toute personne n'est présente qu'une seule fois dans un arbre généalogique.
//!			Si le parent est dans son arbreGene mais pas l'enfant, alors ajouter l'enfant dans cet arbreGene.
//!			Si le parent n'est pas dans l'arbreGene et que son enfant est l'ancêtre ; alors remplacer l'ancêtre (l'ancien ancêtre devient un enfant du nouvel ancêtre)
//!			Si le parent n'est pas dans l'arbreGene et que son enfant n'est pas l'ancêtre, alors ne pas modifier l'arbreGene.
//! \param[in] p_parent le pointeur d'une personne
//! \param[in] p_enfant le pointeur d'une personne
//! \exception logic_error si le parent a un nom différent de l'arbreGene
//! \exception logic_error si le parent n'est pas dans l'arbreGene et que son enfant n'est pas l'ancêtre
void ArbreGenealogique::ajouterEnfant(pEntree p_parent_it, pEntree p_enfant_it)
{
	if (p_parent_it->first.reqNom() == m_nom)
	{
		if (appartient(p_parent_it) && !appartient(p_enfant_it))
		{
			Noeud* noeudAAjouter = new Noeud(p_enfant_it);
			noeudPEntree(p_parent_it, m_racine)->m_enfants.push_back(noeudAAjouter);
		}
		else if (!appartient(p_parent_it) && noeudPEntree(p_enfant_it, m_racine) == m_racine)
		{
			Noeud &ancienneRacine = *m_racine;
			m_racine = new Noeud(p_parent_it);
			Noeud* noeudAAjouter = new Noeud(p_enfant_it);
			m_racine->m_enfants.push_back(noeudAAjouter);
			for (list<Noeud*>::const_iterator it = ancienneRacine.m_enfants.begin(); it != ancienneRacine.m_enfants.end(); it++)
			{
				noeudPEntree(p_enfant_it, m_racine)->m_enfants.push_back(*it);
			}
		}
		else if (!appartient(p_parent_it) && noeudPEntree(p_enfant_it, m_racine) != m_racine)
		{
			throw std::logic_error("Le parent n'est pas dans l'arbreGene et son enfant n'est pas l'ancêtre");
		}
	}
	else
	{
		throw std::logic_error("Le parent a un nom différent de l'arbreGene");
	}

}

//! \brief opérateur surcharge de sortie
//!		affichage des noeuds de l,arbre en pré-ordre
std::ostream & operator <<(std::ostream & p_out,
		const ArbreGenealogique & p_arbreG)
{
	p_out << p_arbreG.preordre(p_arbreG.m_racine);
	return p_out;
}

//! \brief permet de savoir si une personne appartient à l'arbre
//! \param[in] p_personne_it la personne recherchée.
//! \pre non nulle
//! \return vrai si la personne est dans l'arbre, faux sinon.
bool ArbreGenealogique::appartient(pEntree p_personne_it) const
{
	if (p_personne_it->first.reqDateNaissance() != 0)
	{
		return appartient(m_racine, p_personne_it);
	}
	return false;
}

//! \brief permet de savoir si une personne appartient à l'arbre en appelant la méthode récursive nécessaire pour parcours l'arbre
//! \param[in] p_noeud le noeud de départ pour la recherche.
//! \param[in] p_personne_it la personne recherchée.
//! \return vrai si la personne est dans l'arbre, faux sinon.
bool ArbreGenealogique::appartient(Noeud *p_noeud, pEntree p_personne_it) const
{
	if (p_personne_it->first.reqNom() != p_noeud->m_personne_it->first.reqNom() || p_personne_it->first.reqPrenom() != p_noeud->m_personne_it->first.reqPrenom() || p_personne_it->first.reqDateNaissance() != p_noeud->m_personne_it->first.reqDateNaissance())
	{
		if (!p_noeud->m_enfants.empty())
		{
			for (list<Noeud*>::const_iterator it = p_noeud->m_enfants.begin(); it != p_noeud->m_enfants.end(); it++)
			{
				if (appartient(*it, p_personne_it) == true)
				{
					return true;
				}
			}
		}
		return false;
	}
	else
	{
		return true;
	}
}


//! \brief permet d'obtenir la chaine de caractères représentant l'arbre en préordre
//! \param[in] p_noeud le noeud de départ pour l'affichage (le noeud racine).
//! \return la string représentant le préordre de l'arbre.
std::string ArbreGenealogique::preordre(Noeud *p_noeud) const
{
	std::string noeudsPreordre;
	std::ostringstream convertionInt;
	convertionInt << p_noeud->m_personne_it->first.reqDateNaissance();
	noeudsPreordre = p_noeud->m_personne_it->first.reqNom() + ", " + p_noeud->m_personne_it->first.reqPrenom() + ", " + convertionInt.str() + "\n";
	if (!p_noeud->m_enfants.empty())
	{
		for (list<Noeud*>::const_iterator it = p_noeud->m_enfants.begin(); it != p_noeud->m_enfants.end(); it++)
		{
			noeudsPreordre = noeudsPreordre + preordre(*it);
		}
	}
	return noeudsPreordre;
}

//! \brief permet de détruire tous les pointeurs de noeuds de l'arbre
//! \param[in] p_noeud le noeud de départ pour la suppression.
void ArbreGenealogique::detruireNoeuds(Noeud *p_noeud)
{
	list<Noeud*> NoeudsADetruire = p_noeud->m_enfants;
	delete p_noeud;
	if (!NoeudsADetruire.empty())
	{
		for (list<Noeud*>::const_iterator it = p_noeud->m_enfants.begin(); it != p_noeud->m_enfants.end(); it++)
		{
			detruireNoeuds(*it);
		}
	}
}

//! \brief permet d'obtenir la valeur du type Noeud* de l'arbre associée à la valeur du type pEntree fourni.
//! \param[in] p_noeud le noeud de départ pour la recherche.
//! \param[in] p_entree la valeur du type PEntre.
//! \return le noeud de l'arbre correspondant à la valeur du type pEntre.
ArbreGenealogique::Noeud * ArbreGenealogique::noeudPEntree(pEntree p_entree, Noeud *p_noeud) //AJUSTER
{
	if (p_noeud->m_personne_it == p_entree)
	{
		return p_noeud;
	}
	else
	{
		return noeudPEntree(p_entree, p_noeud->m_enfants.front());
		return noeudPEntree(p_entree, p_noeud->m_enfants.back());
	}
}

//! \brief permet de faire une copie profonde de l'arbre de manière récursive.
//! \param[in] p_source le noeud source que l'on doit copier.
//! \param[in] p_noeudDepart le noeud de départ sur lequel on doi ajouter les nouveaux noeuds copiés.
void ArbreGenealogique::copierUnArbre(Noeud* p_source, Noeud* p_noeudDepart)
{
	for (list<Noeud*>::const_iterator it = p_source->m_enfants.begin(); it != p_source->m_enfants.end(); it++)
	{
		Noeud * enfant = new Noeud ((*it)->m_personne_it);
		p_noeudDepart->m_enfants.push_back(enfant);
		if (!(*it)->m_enfants.empty())
		{
			copierUnArbre(*it, enfant);
		}
	}
}




