/**
 * \file Adresse.h
 * \brief Déclaration de la classe Adresse
 * \author theud1
 * \version 0.1
 * \date 2013-11-30
 */

#ifndef ADRESSE_H_
#define ADRESSE_H_
#include <string>
#include <iostream>

class Adresse
{
	friend std::ostream& operator<<(std::ostream&, const Adresse&);

public:
	Adresse(int p_numero=int(), const std::string& p_rue=std::string(), const std::string& p_ville=std::string());
	int reqNumero() const;
	std::string reqRue() const;
	std::string reqVille() const;

	bool operator==(const Adresse&) const;

private:

	int m_numero;
	std::string m_rue;
	std::string m_ville;

};

#endif /* ADDRESSE_H_ */
