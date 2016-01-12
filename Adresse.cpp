/**
 * \file Adresse.cpp
 * \brief implantation de l'interface de la classe adresse
 * \author theud1
 * \version 0.1
 * \date 2013-11-30
 */
#include "Adresse.h"
#include <sstream>
using namespace std;

//! \brief constructeur avec paramètres
//! On construit un objet Adresse à partir de valeurs passées en paramètres.
//! \param [in] p_numero : le numéro de la rue
//! \param [in] p_rue : le nom de la rue
//! \param [in] p_ville : la ville où se situe l'adresse
Adresse::Adresse(int p_numero, const string& p_rue, const string& p_ville)
{
    m_numero = p_numero;
    m_rue = p_rue;
    m_ville = p_ville;
}

//! \brief surcharge de l'opérateur ==
//! \param[in] p_adresse qui est une adresse
//! \return un booléen indiquant si les deux adresses sont égales ou non
bool Adresse::operator==(const Adresse& p_adresse) const
{
	if (p_adresse.m_numero == m_numero && p_adresse.m_rue == m_rue && p_adresse.m_ville == m_ville)
	{
		return true;
	}
	return false;
}

//! \brief surcharge de l'opérateur << d'écriture dans une ostream
//! \param[in] p_os un stream vide dans laquelle on va écrire
//! \param[in] p_adresse qui est une adresse
//! \return le stream dans laquelle on a écrit l'adresse
ostream& operator<<(ostream& p_os, const Adresse& p_adresse)
{
	ostringstream ss;
	ss << p_adresse.m_numero;
	p_os << ss.str() + ", " + p_adresse.m_rue + "\n" + p_adresse.m_ville;
	return p_os;
}

//! \brief Retourne le numéro de la rue
//! \return m_numero
int Adresse::reqNumero() const
{
	return m_numero;
}
//! \brief Retourne le nom de la rue
//! \return m_rue
string Adresse::reqRue() const
{
	return m_rue;
}
//! \brief Retourne la ville de l'adresse
//! \return m_ville
string Adresse::reqVille() const
{
	return m_ville;
}

