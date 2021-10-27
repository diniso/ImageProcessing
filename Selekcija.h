#pragma once
#include "pravougaonik.h"
#include <string>


class Selekcija {
	std::string ime;
	std::vector<Pravougaonik> figure;
	bool active;

public:
	Selekcija(std::string _ime, std::vector<Pravougaonik>& p) {
		ime = _ime;
		figure = p;
		active = true;
	}

	bool getActive() const { return active; }
	std::string getIme() const { return ime; }
	std::vector<Pravougaonik>& getPravougaonik() { return figure; }

	void setActive(bool acti) { active = acti; }
	std::vector<Pravougaonik>::iterator begin() { return figure.begin(); }
	std::vector<Pravougaonik>::iterator end() { return figure.end(); }

};