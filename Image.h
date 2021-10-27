#pragma once

#include <cstdint>
#include "Formater.h"
#include "layer.h"
#include <vector>
#include "Operations.h"
#include "Selekcija.h"
#include "XMLConverter.h"

class Operation;

class Image {
	friend class Xml;

	Formater f;
	std::vector<Layer> slojevi;
	std::vector < Selekcija > selection;
	uint32_t visina, sirina;
	bool active , saved;

public:
	static std::vector<Operation*> operacije;
	static void postaviPocetneFje();
	static void dodajFunkciju(std::string ime , std::vector<std::pair<Operation*, int>>& argu);
	static void spisakFunkcija();


	void pokreni(std::string nazivFje, int para = 0); // za pokretanje fje sa vrednosti para

	void operator() (std::string); // brisanje selekcije
	void operator() (int);// brisanje sloja

	Image(uint32_t visina , uint32_t sirina);
	Image() {}
	Image(const char* path , uint8_t prozirnost = 100);
	~Image() {}

	bool get_active() { return active; }
	std::vector<Layer>& get_slojevi() { return slojevi; }
	std::vector<Selekcija>& get_selection() { return selection; }
	Formater& get_formater() { return f; }
	uint32_t getVisina() const { return visina; }
	uint32_t getSirina() const { return sirina; }
	bool getSaved() const { return saved; }

	void set_active(bool activ) { active = activ; }
	void obojSaSelekcijom(uint8_t red, uint8_t green, uint8_t blue, uint8_t alfa);
	

	void operator+= (Layer& l);      // dodaje novi sloj
	void operator+= (Selekcija& s); // dodaje se selekcija

	Layer* operator[](uint32_t poz); // vraca poziciju sloja
	Selekcija* operator[] (std::string name);

	Layer* format();


	void ispisi(char* path , char* name);
	void ispisi(char* path);
};



