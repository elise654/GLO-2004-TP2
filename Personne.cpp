/**
 * \file Personne.cpp
 * \brief implémentation de l'interface de la classe Personne
 * \author Mario à partir de Thierry
 * \version 0.1
 * \date 2015
 */

#include "Personne.h"
#include <sstream>
using namespace std;

Personne::Personne(const std::string& p_nom, const std::string& p_prenom,
		int p_date)
{
    m_nom = p_nom;
    m_prenom = p_prenom;
    m_dateNaissance = p_date;
}

Personne::Personne(const Personne & p_personne)
{
    m_nom = p_personne.m_nom;
    m_prenom = p_personne.m_prenom;
    m_dateNaissance = p_personne.m_dateNaissance;
}

//! \brief surcharge de l'opérateur <
bool Personne::operator <(const Personne & p_personne) const
{
	if (p_personne.reqNom() > m_nom)
	{
		return true;
	}
	else if (p_personne.reqNom() == m_nom)
	{
		if (p_personne.reqPrenom() > m_prenom)
		{
			return true;
		}
		else if (p_personne.reqPrenom() == m_prenom)
		{
			if (p_personne.reqDateNaissance() > m_dateNaissance)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

//! \brief surcharge de l'opérateur << d'écriture dans une ostream
//! \param[in] p_os un ostream vide dans laquelle on va écrire
//! \param[in] p_personne qui est une personne
//! \return le ostream dans laquelle on a écrit les information sur la personne
ostream& operator<<(ostream& p_os, const Personne& p_personne)
{
	ostringstream ss;
	ss << p_personne.m_dateNaissance;
	p_os << p_personne.m_nom + ", " + p_personne.m_prenom + ", " + ss.str();
	return p_os;
}

//! \brief obtient la date de naissance
//! \return la date de naissance
int Personne::reqDateNaissance() const
{
	return m_dateNaissance;
}

//! \brief obtient le nom (de famille) de la personne
//! \return le nom de la personne
std::string Personne::reqNom() const
{
	return m_nom;
}
//! \brief obtient le prénom de la personne
//! \return le prénom de la personne
std::string Personne::reqPrenom() const
{
	return m_prenom;
}

