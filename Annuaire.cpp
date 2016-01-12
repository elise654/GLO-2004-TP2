/**
 * \file Annuaire.cpp
 * \brief implémantation de la classe annuaire
 * \author mario
 * \version 0.1
 * \date 2015
 */

#include "Annuaire.h"
#include <stdlib.h>
using namespace std;

//! \brief Constructeur à partir d'un fichier en entrée.
//! \param[in] p_fichierEntree un flux d'entrée vers un fichier contenant la liste des personnes à charger.
//! \pre			Le fichier p_fichierEntree est ouvert corectement.
//! \post		Le fichier p_fichierEntree n'est pas fermé par la fonction.
//! \post		Si les préconditions sont respectées, les données contenu
//!				dans le fichier en entrée sont stockées dans l'annuaire.
//! \exception	bad_alloc si pas assez de mémoire pour contenir toute les données du fichier.
//! \exception	logic_error si le fichier p_fichierEntree n'est pas ouvert correctement.
Annuaire::Annuaire(std::ifstream & p_fichierEntree)
{
	try
	{
		std::string line;
		if (p_fichierEntree.is_open())
		{
			while (!p_fichierEntree.eof())
			{
				std::string nom;
				std::getline(p_fichierEntree, nom);
				if (nom != "$\r" && nom != "$")
				{
					nom = nom.substr(0, nom.size() - 1);
					std::string prenom;
					std::getline(p_fichierEntree, prenom);
					prenom = prenom.substr(0, prenom.size() - 1);
					std::string dateNaissance;
					std::getline(p_fichierEntree, dateNaissance);
					int dateNaissanceInt = atoi(dateNaissance.c_str());
					Personne nouvellePersonne = Personne(nom, prenom, dateNaissanceInt);
					std::string numero;
					std::getline(p_fichierEntree, numero);
					int numeroInt = atoi(numero.c_str());
					std::string rue;
					std::getline(p_fichierEntree, rue);
					rue = rue.substr(0, rue.size() - 1);
					std::string ville;
					std::getline(p_fichierEntree, ville);
					ville = ville.substr(0, ville.size() - 1);
					Adresse nouvelleAdresse = Adresse(numeroInt, rue, ville);
					inscrire(nouvellePersonne, nouvelleAdresse);
				}
				else
				{
					std::string nomParent;
					std::getline(p_fichierEntree, nomParent);
					nomParent = nomParent.substr(0, nomParent.size() - 1);
					std::string prenomParent;
					std::getline(p_fichierEntree, prenomParent);
					prenomParent = prenomParent.substr(0, prenomParent.size() - 1);
					std::string dateNaissanceParent;
					std::getline(p_fichierEntree, dateNaissanceParent);
					int dateNaissanceParentInt = atoi(dateNaissanceParent.c_str());
					Personne nouveauParent = Personne(nomParent, prenomParent, dateNaissanceParentInt);
					std::string nomEnfant;
					std::getline(p_fichierEntree, nomEnfant);
					nomEnfant = nomEnfant.substr(0, nomEnfant.size() - 1);
					std::string prenomEnfant;
					std::getline(p_fichierEntree, prenomEnfant);
					prenomEnfant = prenomEnfant.substr(0, prenomEnfant.size() - 1);
					std::string dateNaissanceEnfant;
					std::getline(p_fichierEntree, dateNaissanceEnfant);
					int dateNaissanceEnfantInt = atoi(dateNaissanceEnfant.c_str());
					Personne nouvelEnfant = Personne(nomEnfant, prenomEnfant, dateNaissanceEnfantInt);
					ajouterParentEnfant(nouveauParent, nouvelEnfant);
				}

			}
		}
		else
		{
			throw std::logic_error("Le fichier n'est pas ouvert correctement");
			std::cout << "Le fichier n'est pas ouvert correctement \n";
		}
	}
	catch(std::bad_alloc& e)
	{
		std::cout << e.what();
	}
}

//! \brief pour inscrire une personne dans l'annuaire
//! \param[in] p_personne la personne à àjouter.
//! \param[in] p_adresse de la personne à inscrire
void Annuaire::inscrire(const Personne & p_personne, const Adresse& p_adresse)
{
	m_bottin.insert(std::pair<Personne,Adresse>(p_personne,p_adresse));
}

//! \brief ajoute un enfant et un parent dans l'arbre généalogique du même nom que le parent.
//!			Le parent et l'enfant doivent exister dans le bottin pour l'insertion dans un arbre généalogique.
//! \param[in] p_parent : le parent.
//! \pre Precondition p_parent et p_enfant existent dans le bottin
//! \param[in] p_enfant : l'enfant.
//! \pre Precondition p_enfant existe dans le bottin
//! \exception logic_error le parent n'existe pas dans le bottin.
//! \exception logic_error l'enfant n'existe pas dans le bottin.

void Annuaire::ajouterParentEnfant(const Personne & p_parent,
		const Personne & p_enfant)
{
	std::map<Personne,Adresse>::const_iterator iterEnfant;
	std::map<Personne,Adresse>::const_iterator iterParent;
	iterParent = m_bottin.find(p_parent);
	iterEnfant = m_bottin.find(p_enfant);

	if (iterParent == m_bottin.end())
	{
		throw std::logic_error ("Le parent n'existe pas dans le bottin");
		std::cout << "Le parent " << iterParent->first << "n'existe pas dans le bottin \n";
	}
	if (iterEnfant == m_bottin.end())
	{
		throw std::logic_error ("L'enfant n'existe pas dans le bottin");
		std::cout << "L'enfant " << iterEnfant->first << "n'existe pas dans le bottin \n";
	}

	bool arbreTrouve = false;
	for (std::list<ArbreGenealogique>::iterator iterator = m_listeArbreGene.begin(), end = m_listeArbreGene.end(); iterator != end; ++iterator)
	{
	    if ((iterator->appartient(iterParent) && !iterator->appartient(iterEnfant) && iterator->reqNom() == iterParent->first.reqNom()) || (!iterator->appartient(iterParent) && iterator->appartient(iterEnfant) && iterator->reqNom() == iterParent->first.reqNom()))
	    {
	    	iterator->ajouterEnfant(iterParent, iterEnfant);
	    	arbreTrouve = true;
	    	break;
	    }
	    else if (iterator->appartient(iterParent) && !iterator->appartient(iterEnfant) && iterator->reqNom() != iterParent->first.reqNom())
	    {
	    	arbreTrouve = false;
	    }
	    else if(iterator->appartient(iterParent) && iterator->appartient(iterEnfant))
	    {
	    	arbreTrouve = true;
	    	std::cout << "L'enfant " << iterEnfant->first << " se trouve déjà dans cet arbre généalogique, ajout refusé \n";
	    	break;
	    }
	}

	if (arbreTrouve == false)
	{
		ArbreGenealogique nouvelArbre = ArbreGenealogique(iterParent);
		m_listeArbreGene.push_back(nouvelArbre);
		ajouterParentEnfant(p_parent, p_enfant);
	}
}

//! \fn std::ostream & Annuaire::operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
//! \brief operateur de sortie du contenu de l'annuaire formatage des infos dans un string puis sortie
//! \param[in] p_annuaire l'annuaire a sortir.
//! \pre l'annuaire n'est pas vide
//! \param[out] p_out le flux de sortie contenant l'annuaire .
//! \exception exception_name Description des raisons de l'exception (peut en avoir plusieurs ou aucune).
//! \return un flux de sortie pour les appel en cascade.
std::ostream & operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
{
	//L'affichage des exceptions est gérée lors de leur déclenchement
	p_out << "bottin: \n\n";
	for(map<Personne, Adresse>::const_iterator it = p_annuaire.m_bottin.begin(); it != p_annuaire.m_bottin.end(); ++it)
	{
		if (it->first.reqNom() != "")
		{
			p_out << it->first << "\n" << it->second << "\n";
		}
	}

	p_out << "\n arbres généalogiques : \n\n";
	for(list<ArbreGenealogique>::const_iterator it = p_annuaire.m_listeArbreGene.begin(); it != p_annuaire.m_listeArbreGene.end(); ++it)
	{
		p_out << "Arbre " + it->reqNom() + " affiché en pré-ordre: \n";
		p_out << *it;
	}
	return p_out;
}

