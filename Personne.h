/**
 * \file Personne.h
 * \brief interface d'une classe modélisant une personne
 * \author Mario à partir de Thierry
 * \version 0.1
 * \date 2015
 */

#ifndef PERSONNE_H_
#define PERSONNE_H_

#include <string>
#include <iostream>

/**
 * \class Personne
 * \brief Classe représentant une personne.
 */
class Personne
{
public:
	Personne(const std::string&, const std::string&, int);
	Personne (const Personne& p_personne);
	bool operator <(const Personne& p_personne) const;

	friend std::ostream& operator<<(std::ostream&, const Personne&);

	int reqDateNaissance() const;
    std::string reqNom() const;
    std::string reqPrenom() const;
private:
	std::string m_nom;
	std::string m_prenom;
	int m_dateNaissance;
};


#endif /* PERSONNE_H_ */
