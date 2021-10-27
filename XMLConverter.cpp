#include "XMLConverter.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <exception>

using namespace rapidxml;

Image* Xml::ucitaj(const char* path) {
	xml_document<> doc;
	xml_node<> * root_node;

	Image* m = nullptr;

	try {
	
		file<> f(path);


		doc.parse<0>(&(f.data()[0])); // ne znam sta znaci
		m = new Image();

		root_node = doc.first_node("Image");
		xml_node<> *tek = root_node;
		tek = tek->first_node("aktivnost");

		std::string pom;
		int n;

		pom = tek->first_attribute("active")->value();
		if (pom.compare("true") == 0) m->active = true;
		tek = tek->next_sibling(); // aktivnost slike


		pom = tek->first_attribute("vis")->value();
		m->visina = std::stoi(pom);
		tek = tek->next_sibling(); // visina

		pom = tek->first_attribute("sir")->value();
		m->sirina = std::stoi(pom);
		tek = tek->next_sibling(); // sirina

		pom = tek->first_attribute("br")->value();
		n = std::stoi(pom); // broj layera
		//tek pokazuje na broj lejera

		xml_node<> *lej = tek->first_node("Layer"); // usao u lajere

		for (int i = 0; i < n; i++) {
			xml_node<> *tmp = lej->first_node("visible");
			bool visible= false , active = false;
			int prozir;

			pom = tmp->first_attribute("vidljiv")->value();
			if (pom.compare("true") == 0) visible = true;

			tmp = tmp->next_sibling();
			pom = tmp->first_attribute("active")->value();
			if (pom.compare("true") == 0) active = true;

			tmp = tmp->next_sibling();
			pom = tmp->first_attribute("prozir")->value();
			prozir = std::stoi(pom);
			if (prozir > 100) prozir = 100;
			if (prozir < 0) prozir = 0;

			tmp = tmp->next_sibling();
			tmp = tmp->first_node("Piksel");

			std::vector<std::vector<Piksel>> mat;
			int red, green, blue, alfa;
			for (unsigned k = 0; k < m->visina; k++) {
				std::vector<Piksel> niz;
				for (unsigned j = 0; j < m->sirina; j++) {
					red = std::stoi(tmp->first_attribute("red")->value());
					blue = std::stoi(tmp->first_attribute("blue")->value());
					green = std::stoi(tmp->first_attribute("green")->value());
					alfa = std::stoi(tmp->first_attribute("alfa")->value());
					Piksel p(red , green , blue , alfa);
					niz.push_back(p);
					tmp = tmp->next_sibling();
				}
				mat.push_back(niz);
			//	tmp = tmp->next_sibling();
			}

			Layer *l = new Layer(mat, m->visina, m->sirina, prozir);
			l->set_acitive(active);
			l->set_visible(visible);

			m->slojevi.push_back(*l);

			lej = lej->next_sibling();
		}


		tek = tek->next_sibling(); // tek pokazuje na broj selekcija
		pom = tek->first_attribute("br")->value();
		n = std::stoi(pom); // broj selekcija

		xml_node<> *selek = tek->first_node("Selekcija");
		for (int i = 0; i < n; i++) {
			std::vector<Pravougaonik> niz;
			std::string name;
			bool active = false;
			xml_node<> *tmp = selek->first_node("name");

			name = tmp->first_attribute("ime")->value(); // ime selekcije

			tmp = tmp->next_sibling();

			pom =  tmp->first_attribute("active")->value();
			if (pom.compare("true") == 0) active = true; // aktivnost sloja

			tmp = tmp->next_sibling();
			pom = tmp->first_attribute("br")->value();
			int k = std::stoi(pom); // broj Pravougaonika

			tmp = tmp->first_node("Pravougaonik");
			for (int j = 0; j < k; j++) {
				int y1 = std::stoi(tmp->first_attribute("y1")->value());
				int x1 = std::stoi(tmp->first_attribute("x1")->value());
				int visina = std::stoi(tmp->first_attribute("visina")->value());
				int sirina = std::stoi(tmp->first_attribute("sirina")->value());

				Pravougaonik p(std::pair<int, int>(y1, x1), visina, sirina);
				niz.push_back(p);
				tmp = tmp->next_sibling();
			}

			Selekcija s(name, niz);
			s.setActive(active);

			m->selection.push_back(s);

			selek = selek->next_sibling();
		}

		tek = tek->next_sibling(); // pokazuje na broj kompozitnih fja
		n = std::stoi(tek->first_attribute("br")->value()); // broj kompozitnih funkcija

		tek = tek->first_node("kompozitna"); // pokazuje na prvu kompozitnu funkciju
		for (int i = 0; i < n; i++) {
			std::string name = tek->first_attribute("ime")->value();
			int m = std::stoi(tek->first_attribute("br")->value());

			std::vector<std::pair<Operation*, int>> arg;
			xml_node<> *fje = tek->first_node("funkcija");
			for (int j = 0; j < m; j++) {
				std::string prov = fje->first_attribute("ime")->value();
				int par = std::stoi(fje->first_attribute("par")->value());
				Operation* o = nullptr;

				if (prov.compare("sabiranje") == 0) o = new Sabiranje();
				if (prov.compare("oduzimanje") == 0) o = new Oduzimanje();
				if (prov.compare("inverznooduzimanje") == 0) o = new InverznoOduzimanje();
				if (prov.compare("mnozenje") == 0) o = new Mnozenje();
				if (prov.compare("deljenje") == 0) o = new Deljenje();
				if (prov.compare("inverznodeljenje") == 0) o = new InverznoDeljenje();
				if (prov.compare("stepen") == 0) o = new Stepen();
				if (prov.compare("logaritam") == 0) o = new Logaritam();
				if (prov.compare("minimum") == 0) o = new Minimum();
				if (prov.compare("maksimum") == 0) o = new Maksimum();
				if (prov.compare("aposolutnavrednost") == 0) o = new ApsolutnaVrednost();

				if (o == nullptr) {
					std::cout << "Fja na ne postoji. Fja sadrzi ucitane fje do reda: " << (j+1)<< std::endl;
					break;
				}

				arg.push_back(std::pair<Operation*, int>(o, par));

				fje = fje->next_sibling();
			}



			Image::dodajFunkciju(name, arg);
			tek = tek->next_sibling();
		}


	

	}
	catch (std::exception &e) {
		m = new Image(400, 400);
		std::cout << "Fajl nije moguce ucitati!" << std::endl;
	}
	return m;
}


void Xml::ispisi(const char* path, Image& m) {
	xml_document<> doc;

	std::ofstream izlaz(path, std::ios::out);
	if (izlaz) {
		xml_node<> *root = doc.allocate_node(node_element, "Image");
		std::string pom; char textToWrite[16];

		xml_node<> *tek = doc.allocate_node(node_element, "aktivnost");
		if (m.active) pom = "true";
		else pom = "false";
		tek->append_attribute(doc.allocate_attribute("active", doc.allocate_string(pom.c_str())));

		root->append_node(tek); // ubacio aktivnost

		xml_node<> *hig = doc.allocate_node(node_element, "visina");
		sprintf(textToWrite, "%lu", m.visina);
		hig->append_attribute(doc.allocate_attribute("vis", doc.allocate_string(textToWrite)));
		root->append_node(hig); // ubacio visinu

		xml_node<> *wid = doc.allocate_node(node_element, "sirina");
		sprintf(textToWrite, "%lu", m.sirina);
		wid->append_attribute(doc.allocate_attribute("sir", doc.allocate_string(textToWrite)));
		root->append_node(wid); // ubacio sirinu

		xml_node<> *num_lay = doc.allocate_node(node_element, "Broj_layera");
		sprintf(textToWrite, "%lu", m.slojevi.size());
		num_lay->append_attribute(doc.allocate_attribute("br", doc.allocate_string(textToWrite)));

		for (Layer &l : m.slojevi) {
			xml_node<> * lay  = doc.allocate_node(node_element, "Layer");

			xml_node<> *ley_vis = doc.allocate_node(node_element, "visible");
			if (l.get_visible()) pom = "true";
			else pom = "false";
			ley_vis->append_attribute(doc.allocate_attribute("vidljiv", doc.allocate_string(pom.c_str())));
			lay->append_node(ley_vis); // ubacio vidljivost layera

			xml_node<> *ley_act = doc.allocate_node(node_element, "aktivnost");
			if (l.get_acitive()) pom = "true";
			else pom = "false";
			ley_act->append_attribute(doc.allocate_attribute("active", doc.allocate_string(pom.c_str())));
			lay->append_node(ley_act); // ubacio aktivnost layera

			xml_node<> *proz = doc.allocate_node(node_element, "prozirnost");
			sprintf(textToWrite, "%lu", l.get_prozirnost());
			proz->append_attribute(doc.allocate_attribute("prozir", doc.allocate_string(textToWrite)));
			lay->append_node(proz); // ubacio prozirnost


			xml_node<> *piksel = doc.allocate_node(node_element, "Pikseli");
			char pom2[8]; 
			for (unsigned i = 0; i < m.visina; i++) {
				for (unsigned j = 0; j < m.sirina; j++) {
					xml_node<> * pik = doc.allocate_node(node_element, "Piksel");
					sprintf(pom2, "%u", l.get_piksels()[i][j].get_red());
					pik->append_attribute(doc.allocate_attribute("red", doc.allocate_string(pom2)));

					sprintf(pom2, "%u", l.get_piksels()[i][j].get_green());
					pik->append_attribute(doc.allocate_attribute("green", doc.allocate_string(pom2)));

					sprintf(pom2, "%u", l.get_piksels()[i][j].get_blue());
					pik->append_attribute(doc.allocate_attribute("blue", doc.allocate_string(pom2)));

					sprintf(pom2, "%u", l.get_piksels()[i][j].get_alfa());
					pik->append_attribute(doc.allocate_attribute("alfa", doc.allocate_string(pom2)));

					piksel->append_node(pik);
				}
			}

			lay->append_node(piksel);
			
			num_lay->append_node(lay); // ubacio sloj


		}

		root->append_node(num_lay); //ubacio sve layere

		xml_node<> *num_sel = doc.allocate_node(node_element, "Broj_selekcija");
		sprintf(textToWrite, "%lu", m.selection.size());
		num_sel->append_attribute(doc.allocate_attribute("br", doc.allocate_string(textToWrite))); // napravio broj selekcija

		for (Selekcija& s : m.selection) {
			xml_node<> *sel = doc.allocate_node(node_element, "Selekcija");

			xml_node<> *ime = doc.allocate_node(node_element, "name");
			ime->append_attribute(doc.allocate_attribute("ime",doc.allocate_string( s.getIme().c_str())));
			sel->append_node(ime); // ubacio ime u selekciju

			xml_node<> *acti = doc.allocate_node(node_element, "aktivnost");
			if (s.getActive()) pom = "true";
			else pom = "false";
			acti->append_attribute(doc.allocate_attribute("active", doc.allocate_string(pom.c_str())));
			sel->append_node(acti); // ubacio aktivnost

			xml_node<> * num_pra = doc.allocate_node(node_element, "Broj_pravougaonika");
			sprintf(textToWrite, "%lu", s.getPravougaonik().size());
			num_pra->append_attribute(doc.allocate_attribute("br", doc.allocate_string(textToWrite)));

			for (Pravougaonik& p : s.getPravougaonik()) {
				xml_node<> * prav = doc.allocate_node(node_element, "Pravougaonik");

				sprintf(textToWrite, "%lu", p.getPocetak().first);
				prav->append_attribute(doc.allocate_attribute("y1", doc.allocate_string(textToWrite)));

				sprintf(textToWrite, "%lu", p.getPocetak().second);
				prav->append_attribute(doc.allocate_attribute("x1", doc.allocate_string(textToWrite)));

				sprintf(textToWrite, "%lu", p.getVisina());
				prav->append_attribute(doc.allocate_attribute("visina", doc.allocate_string(textToWrite)));

				sprintf(textToWrite, "%lu", p.getSirina());
				prav->append_attribute(doc.allocate_attribute("sirina", doc.allocate_string(textToWrite)));

				num_pra->append_node(prav);
			}

			sel->append_node(num_pra);
			
			num_sel->append_node(sel); // ubacio selekciju u sve selekcije
		}

		root->append_node(num_sel); // ubacio broj selekcija


		xml_node<> *num_fun = doc.allocate_node(node_element, "Broj_funkcija");
		sprintf(textToWrite, "%lu", Image::operacije.size()-15);
		num_fun->append_attribute(doc.allocate_attribute("br", doc.allocate_string(textToWrite)));

		for (unsigned i = 15; i < Image::operacije.size();i++) {
			xml_node<>* fja = doc.allocate_node(node_element, "kompozitna");
			fja->append_attribute(doc.allocate_attribute("ime", doc.allocate_string(Image::operacije[i]->get_name().c_str())));

			sprintf(textToWrite, "%lu",((Kompozitna*) Image::operacije[i])->getOperations().size());
			fja->append_attribute(doc.allocate_attribute("br", doc.allocate_string(textToWrite)));

			for (unsigned j = 0; j < ((Kompozitna*)Image::operacije[i])->getOperations().size(); j++) {
				xml_node<>* ope = doc.allocate_node(node_element, "funkcija");

				ope->append_attribute(doc.allocate_attribute("ime", doc.allocate_string(((Kompozitna*)Image::operacije[i])->getOperations()[j].first->get_name().c_str())));

				sprintf(textToWrite, "%lu", ((Kompozitna*)Image::operacije[i])->getOperations()[j].second);;
				ope->append_attribute(doc.allocate_attribute("par", doc.allocate_string(textToWrite)));

				fja->append_node(ope);
			}


			num_fun->append_node(fja); // ubacio kompozitnu
		}

		root->append_node(num_fun); // ubacio sve kompozitne funkcije

		std::string xml_string; // ispis
		doc.append_node(root);
		print(std::back_inserter(xml_string), doc);
		izlaz << xml_string;
		izlaz.close();
		doc.clear();

	}
	else {
		std::cout << "Putanja u fajlu nije dobra." << std::endl;
	}
}