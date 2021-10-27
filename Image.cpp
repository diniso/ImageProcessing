#include "Image.h"
#include "layer.h"
#include "cstdint"
#include "BMP.h"
#include <algorithm>
#include "Operations.h"
#include <iostream>


Image::Image(uint32_t visina, uint32_t sirina) {
	Layer l(visina , sirina);
	slojevi.push_back(l);
	visina = l.get_visina();
	sirina = l.get_sirina();
	saved = active = false;
}

Layer* Image::operator[](uint32_t poz) {
	if (poz > slojevi.size()) return nullptr;
	return &slojevi[poz];
}

Image::Image(const char* path, uint8_t prozirnost) {
	Layer l1;
	l1 = *f.ucitaj(path, prozirnost);
	slojevi.push_back(l1);
	sirina = l1.get_sirina();
	visina = l1.get_visina();
	saved = active = false;
}

void Image::operator+= (Layer& l) {
	saved = false;
	uint32_t sir = l.get_sirina();
	uint32_t vis = l.get_visina();
	if (sirina > sir) {
		uint32_t raz = sirina - sir;
		l.set_sirina(sirina);
		for (std::vector<Piksel> &s : l.get_piksels()) {
			for (unsigned i = 0; i < raz; i++)
				s.push_back(Piksel());
		}
	}
	else if (sirina < sir) {
		uint32_t raz = sir - sirina;
		for (Layer &l1 : slojevi) {
			l1.set_sirina(sir);
			for (std::vector<Piksel> &p : l1.get_piksels()) {
				for (unsigned i = 0; i < raz; i++)
					p.push_back(Piksel());
			}
		}
	}
	sirina = std::max(sir, sirina);
	if (visina > vis) {
		uint32_t raz = visina - vis;
		l.set_visina(visina);
		for (unsigned j = 0; j < raz; j++) {
			std::vector<Piksel> p;
			for (unsigned i = 0; i < sirina; i++)
				p.push_back(Piksel());
			l.get_piksels().push_back(p);
		}
	}
	else if (visina < vis) {
		uint32_t raz = vis - visina;
		for (Layer &l1 : slojevi) {
			l1.set_visina(vis);
			for (unsigned j = 0; j < raz; j++) {
				std::vector<Piksel> p;
				for (unsigned i = 0; i < sirina; i++)
					p.push_back(Piksel());
				l1.get_piksels().push_back(p);
			}
		}
	}
	 visina = std::max(visina , vis);

	slojevi.push_back(l);
}


void Image::operator+= (Selekcija& s) {
	selection.push_back(s);
}

Layer* Image::format() {
	uint16_t ukupno_prozi = 0 , layer_pro , red , green , blue , alfa;
	Layer *l = new Layer(visina, sirina);
	unsigned cnt = 0;
	for (unsigned i = 0; i < slojevi.size(); i++) {
		if (!slojevi[i].get_visible()) continue;
		cnt++;
		ukupno_prozi += slojevi[i].get_prozirnost() / (i + 1);
		if (ukupno_prozi >= 100) break;
	}
	ukupno_prozi = 0;

	for (unsigned i = 0; i < slojevi.size(); i++) {
		if (!slojevi[i].get_visible()) continue;
		layer_pro = slojevi[i].get_prozirnost() / (i + 1);
		if (layer_pro + ukupno_prozi > 100) layer_pro = 100 - ukupno_prozi;
		for (unsigned j = 0; j < slojevi[i].get_visina(); j++) {
			for (unsigned k = 0; k < slojevi[i].get_sirina(); k++) {
				red = slojevi[i].get_piksels()[j][k].get_red()* layer_pro / 100;
				blue = slojevi[i].get_piksels()[j][k].get_blue()* layer_pro / 100;
				green = slojevi[i].get_piksels()[j][k].get_green() * layer_pro / 100;
				alfa = slojevi[i].get_piksels()[j][k].get_alfa() / cnt;

				l->get_piksels()[j][k] += Piksel(red, green, blue, alfa);
			}
			
		}
		ukupno_prozi += layer_pro;
		if (ukupno_prozi >= 100) break;
	}
	return l;
}


void Image::postaviPocetneFje() {
	Operation *o;
	o = new Sabiranje();
	operacije.push_back(o);

	o = new Oduzimanje();
	operacije.push_back(o);

	o = new InverznoOduzimanje();
	operacije.push_back(o);

	o = new Mnozenje();
	operacije.push_back(o);

	o = new Deljenje();
	operacije.push_back(o);

	o = new InverznoDeljenje();
	operacije.push_back(o);

	o = new Stepen();
	operacije.push_back(o);

	o = new Logaritam();
	operacije.push_back(o);

	o = new Minimum();
	operacije.push_back(o);

	o = new Maksimum();
	operacije.push_back(o);

	o = new ApsolutnaVrednost();
	operacije.push_back(o);

	o = new Inverzija();
	operacije.push_back(o);

	o = new CrnoBela();
	operacije.push_back(o);

	o = new Siva();
	operacije.push_back(o);

	o = new Medijana();
	operacije.push_back(o);

}


void Image::dodajFunkciju(std::string ime, std::vector<std::pair<Operation*, int>>& argu) {
	if (argu.size() > 0) {
		bool flag = true;
		for (unsigned i = 0; i < Image::operacije.size(); i++) {
			if (Image::operacije[i]->get_name().compare(ime) == 0) flag = false;
		}
		if (flag) {
			Operation *o = new Kompozitna(ime, argu);
			operacije.push_back(o);
		}
		else std::cout << "Funkcija sa ovim imenom vec postoji!" << std::endl;
	}
	else std::cout << "Ne moze se dodati funkcija koja nije dobro napravljena!" << std::endl;
}

void Image::spisakFunkcija() {
	for (unsigned i = 0; i < operacije.size(); i++)
		std::cout << (i + 1) << ". " << operacije[i]->get_name() << std::endl;
}

void Image::pokreni(std::string nazivFje, int para) {
	bool flag = false;
	for (Operation *o : operacije) {
		if (nazivFje.compare(o->get_name()) == 0) {
			flag = true;
			saved = false;
			o->operation(*this, para);
			break;
		}
	}
	if (!flag) std::cout << "Funkcija koju ste pozvali ne postoji!" << std::endl;
}

void Image::operator() (std::string s) {
	for (auto iter = selection.begin(); iter != selection.end(); iter++) {
		if ((*iter).getIme().compare(s) == 0) {
			selection.erase(iter);
			break;
		}
	}
}


void Image::operator() (int id) {
	if (id < 0 || id >= ((int)slojevi.size())) std::cout << "Nije moguce obrisati sloj!" << std::endl;
	else {
		slojevi.erase(slojevi.begin() + id);
	}
}


void Image::ispisi(char* path, char* name) {
	saved = true;
	Layer l;
	l = *format();
	f.ispisi(path, name, l);
}

void Image::ispisi(char* path) {
	saved = true;
	Layer l;
	l = *format();
	f.ispisi(path, l);
}


Selekcija* Image::operator[] (std::string name) {
	for (Selekcija& s : selection) {
		if (s.getIme().compare(name) == 0) {
			return &s;
		}
	}
	return nullptr;
}


void Image::obojSaSelekcijom(uint8_t red, uint8_t green, uint8_t blue , uint8_t alfa) {
	Operation::obojiPiksele(*this, red, green, blue , alfa);
}