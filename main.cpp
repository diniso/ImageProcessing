#include<iostream>
#include<fstream>
#include <exception>
#include<cstdint>
#include "Piksel.h"
#include "layer.h"
#include "Formater.h"
#include "Image.h"
#include "Operations.h"
#include <vector>
#include "Selekcija.h"
#include <string>
#include "XMLConverter.h"


int Operation::promenljiva = 0;
std::vector<Operation*> Image::operacije{};
bool Operation::crvena = true;
bool Operation::zelena = true;
bool Operation::plava = true;


void menu() {
	std::cout << "0. Opcije slike, postavljanje aktivnosti( slojeva, slike, selekcija, piksela)" << std::endl;
	std::cout << "1. Rad sa slojevima" << std::endl;
	std::cout << "2. Rad sa selekcijama" << std::endl;
	std::cout << "3. Operacije nad slikom" << std::endl;
	std::cout << "4. Za zavrsetak programa" << std::endl;
	std::cout << "5. Za snimanje slike" << std::endl;
	std::cout << "6. Informacije o slici" << std::endl;
}

void option_menu() {
	std::cout << "0. Menjanje aktivnosti slike" << std::endl;
	std::cout << "1. Menjanje aktivnosti slojeva i slojeva koji ulaze u konacnu sliku" << std::endl;
	std::cout << "2. Menjanje aktivnosti selekcija" << std::endl;
	std::cout << "3. Podesavanje komponenti piksela nad kojim se vrse operacije" << std::endl;
}

void selection_menu() {
	std::cout << "0. Brisanje selekcije" << std::endl;
	std::cout << "1. Pravljenje i dodavanje selekcije." << std::endl;
	std::cout << "2. Postavljanje komponenti aktivnih selekcija." << std::endl;
}

void function_menu() {
	std::cout << "0. Za dodavanje kompozitne funkcije" << std::endl;
	std::cout << "1. Pokretanje funkcije." << std::endl;
}

void layer_menu() {
	std::cout << "0. Brisanje layera" << std::endl;
	std::cout << "1. Pravljenje i dodavanje layera." << std::endl;
}

void save_menu() {
	std::cout << "1. Ispis u bmp24 formatu" << std::endl;
	std::cout << "2. Ispis u bmp32 formatu" << std::endl;
	std::cout << "3. Ispis u pam formatu(RGBA)" << std::endl;
}


void user() {
	Image *m;
	int red = 0, blue = 0, green = 0 , alfa = 0;
	std::string pom , path;
	std::cout << "Da li zelite da ucitate sliku?" << std::endl;
	std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
	if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
		std::cout << "Unesite putanju do slike." << std::endl;
		std::cin >> path; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');

		int n = strlen(path.c_str());
		if (n > 4 && (path[n - 4] == '.') && (path[n - 3] == 'x') && (path[n - 2] == 'm') && (path[n - 1] == 'l')) {
			Xml x;
			m = x.ucitaj(path.c_str());

		}
		else {

			int providnost = 0;
			std::cout << "Da li zelite da ucitate providnost?" << std::endl;
			std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
				std::cout << "Unesite providnost slike." << std::endl;
				std::cin >> providnost; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (providnost > 100) providnost = 100;
				if (providnost < 0) providnost = 0;

					m = new Image(path.c_str() , providnost);
				
			}
			m = new Image(path.c_str());
		}
	}
	else {
		std::cout << "Stvorena je podrazumevana slika";
		m = new Image(400 , 400);
	}
	// napravio sliku
	bool radi = true;
	int id;
	int n;
	while (radi) {
		menu();
		std::cin >> n; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		switch (n) {
		case 0: option_menu();
			std::cin >> n; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			switch (n)
			{
			case 0: // aktivnost slike
				std::cout << "Activnost slike: ";
				if (m->get_active()) std::cout << "active" << std::endl;
				else std::cout << "inacitive" << std::endl;
				std::cout << "Da li zelite da promenite aktivnost?" << std::endl;
				std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					m->set_active(!m->get_active());
				}
					break;
			case 1: // promeniti aktivnost layera
				std::cout << "Da li zelite da promenite aktivnost nekog layera?" << std::endl;
				std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					std::cout << "Informacije o slojevima(da li sloje aktivan). " << std::endl;
					for (unsigned i = 0; i < m->get_slojevi().size(); i++) {
						std::cout << i << "-ti sloj ";
						if ((*m)[i]->get_acitive()) std::cout << "active." << std::endl;
						else std::cout << "inactive." << std::endl;
					}
					std::cout << "Unesite id layera ciju aktivnost zelite da promenite" << std::endl;
					do {
						if (std::cin >> n) {
							if ((*m)[n] != nullptr) (*m)[n]->set_acitive(!(*m)[n]->get_acitive());
							else std::cout << "Layer sa id-em: " << n << " ne postoji." << std::endl;
						}
					} while (std::cin && std::cin.peek() != '\n');
				}

				std::cout << "Da li zelite da promenite slojeve koje ulaze u sastav konacne slike?" << std::endl;
				std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					std::cout << "Informacije o slojevima(da li ulaze ili ne ulaze u sastav konacne slike). " << std::endl;
					for (unsigned i = 0; i < m->get_slojevi().size();i++) {
						std::cout << i << "-ti sloj ";
						if ((*m)[i]->get_visible()) std::cout << "ulazi." << std::endl;
						else std::cout << "ne ulazi." << std::endl;
					}
					std::cout << "Unesite id layera ciju aktivnost zelite da promenite" << std::endl;
					do {
						if (std::cin >> n) {
							if ((*m)[n] != nullptr) (*m)[n]->set_visible(!(*m)[n]->get_visible());
							else std::cout << "Layer sa id-em: " << n << " ne postoji." << std::endl;
						}
					} while (std::cin && std::cin.peek() != '\n');
				}
				break;
			case 2: // Menjanje aktivnost selekcija
				std::cout << "Imena postojecih selekcija i akvitnosti:" << std::endl;
				for (Selekcija &s : m->get_selection()) {
					std::cout << s.getIme() << " ";
					if (s.getActive()) std::cout << "active" << std::endl;
					else std::cout << "inactive" << std::endl;
				}
				std::cout << "Da li zelite da promenite aktivnost neke selekcije?" << std::endl;
				std::cin >> pom; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					std::cout << "Unesite naziv selekcija ciju aktivnost zelite da promenite" << std::endl;
					do {
						if (std::cin >> pom) {
							if ((*m)[pom] != nullptr) (*m)[pom]->setActive(!(*m)[pom]->getActive());
							else std::cout << "Selekcija sa imenom: " << pom << " ne postoji." << std::endl;
						}
					} while (std::cin && std::cin.peek() != '\n');
				}



				break;

			case 3: // promena piksela koji ulaze u sastavi slike
				std::cout << "Activne komponente piksela: ";
				if (Operation::get_red()) std::cout << "red " ;
				if (Operation::get_green()) std::cout << "green " ;
				if (Operation::get_blue()) std::cout << "blue " << std::endl;

				std::cout << "Da li zelite da promenite aktivne komponente?" << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					std::cout << "Unesite naziv komponenti koje hocete da se !promene![red]" << std::endl;
					do  {
						if (std::cin >> pom) {
							if (pom.compare("red") == 0 || pom.compare("Red") == 0 || pom.compare("crvena") == 0 || pom.compare("Crvena") == 0) Operation::set_red(!Operation::get_red());
							if (pom.compare("green") == 0 || pom.compare("Green") == 0 || pom.compare("Zelena") == 0 || pom.compare("zelena") == 0) Operation::set_green(!Operation::get_green());
							if (pom.compare("blue") == 0 || pom.compare("Blue") == 0 || pom.compare("plava") == 0 || pom.compare("Plava") == 0) Operation::set_blue(!Operation::get_blue());
						}
					} while (std::cin && std::cin.peek() != '\n');
				}


				break;
			default: std::cout << "Uneta opcija ne postoji" << std::endl;
				break;
			}



			break;
		case 1: layer_menu(); // rad sa slojevima
			std::cin >> n;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			switch (n) {
			case 0: std::cout << "Unesite id layera koji hocete da izbrisete" << std::endl;
				std::cin >> id;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				(*m)(id);
				break;
			case 1: std::cout << "Da li zelite da unesete putanju?" << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				Layer *l;
				if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
					std::cout << "Unesite putanju." << std::endl;
					std::cin >> path;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					int providnost = 0;
					std::cout << "Da li zelite da ucitate providnost?" << std::endl;
					std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
						std::cout << "Unesite providnost slike." << std::endl;
						std::cin >> providnost;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
						if (providnost > 100) providnost = 100;
						if (providnost < 0) providnost = 0;
					}
					l = m->get_formater().ucitaj(path.c_str(), providnost);
				}
				else {
					l = new Layer(m->getVisina(), m->getSirina());
				}
				*m += *l;
				break;
			default: std::cout << "Uneta opcija ne postoji." << std::endl;
				break;
			}
			break;


		case 2: selection_menu(); 
			std::cin >> n; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			switch (n)
			{
			case 0:	std::cout << "Imena postojecih selekcija:" << std::endl;
				for (Selekcija s : m->get_selection()) {
					std::cout << s.getIme() << std::endl;
				}
				std::cout << "Unesite ime selekcije koje hocete da izbrisete:" << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				(*m)(pom);
				break;

			case 1: {std::cout << "Unesite broj pravougaonih oblika: ";
				std::vector<Pravougaonik> niz;
				int visina = 0, sirina = 0, vis = 0, sir = 0;
				std::cin >> n;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				for (int i = 0; i < n; i++) {
					std::cout << "Unesite kordinate tacke(gore , levo) ][visina , sirina] " << std::endl;
					std::cin >> vis >> sir;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					std::cout << "Unesite visinu i sirinu pravougaonog oblika" << std::endl;
					std::cin >> visina >> sirina;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					Pravougaonik p(std::pair<int, int>(vis, sir), visina, sirina);
					niz.push_back(p);
				}
				std::cout << "Unesite ime selekcije:" << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				Selekcija se(pom, niz);
				(*m) += se;

				break;
			}
			case 2:
				std::cout << "Unesti vrednost za komponente piksel(red , green , blue , alfa)" << std::endl;
				std::cin >> red >> green >> blue >> alfa; std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				m->obojSaSelekcijom(red, green, blue , alfa);

				break;
			default:
				std::cout << "Uneta opcija ne postoji." << std::endl;
				break;
			}

			break;
		case 3: // operacije sa slikom
			function_menu();
			std::cin >> n;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			switch (n) {
			case 0:
				std::cout << "Uneti putanju do kompozitne funkcije." << std::endl;
				std::cin >> path;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				ucitaj_funkciju(path.c_str());
				break;
			case 1:
				std::cout << "Spisak mogucih funkcija:" << std::endl;
				Image::spisakFunkcija();
				std::cout << "Ucitati ime zeljene funkcije." << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				n = 100;
				for (unsigned i = 0; i < Image::operacije.size(); i++) {
					if (pom.compare(Image::operacije[i]->get_name()) == 0) n = i;
				}
				if (n >= 0 && n <= 10) {
					std::cout << "Ucitati vrednost parametra:" << std::endl;
					std::cin >> n;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					m->pokreni(pom, n);
				}
				else {
					m->pokreni(pom);
				}
				
				break;
			default: std::cout << "Uneta opcija ne postoji." << std::endl;
				break;
			}

			break;
		case 4: radi = false;
			if (m->getSaved()) break;
			else {
				std::cout << "Poslednja verzija slike nije snimljenja. Da li hocete da snimite sliku?" << std::endl;
				std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				if (!(pom.compare("da") == 0 || pom.compare("Da") == 0)) {
					break;
				}
			}
		case 5: std::cout << "Da li hocete da promenite vrstu izlaznog formata?";
			std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
				save_menu();
				std::cin >> n;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				m->get_formater().setStatus(n);
			}
			std::cout << "Ucitati putanju izlaznog fajla." << std::endl;
			std::cin >> path;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			std::cout << "Ucitati naziv izlaznog fajla." << std::endl;
			std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			m->ispisi((char*)path.c_str(), (char*)pom.c_str());

			break; // gotovo

		case 6:
			std::cout << "Informacije o layerima" << std::endl << "Broj layera: " << m->get_slojevi().size() << std::endl;

			for (unsigned i = 0; i < m->get_slojevi().size(); i++) {
				std::cout << i << "-ti sloj ";
				if ((*m)[i]->get_acitive()) std::cout << "active and " ;
				else std::cout << "inactive and " ;
				if ((*m)[i]->get_visible()) std::cout << "visible." << std::endl;
				else std::cout << "invisible." << std::endl;
			}
			std::cout <<std::endl;
			std::cout << "Informacije o selekcijama" << std::endl << "Broj selekcija: " << m->get_selection().size() << std::endl;

			for (Selekcija &s : m->get_selection()) {
				std::cout << "Naziv selekcije: " << s.getIme() << std::endl;
				if (s.getActive()) std::cout << "Selekcija je aktivna" << std::endl;
				else std::cout << "Selekcija nije aktivna" << std::endl;
				std::cout << "Selekcija sadrzi: " << s.getPravougaonik().size() << " pravougaonik figura" << std::endl;
				for (Pravougaonik &p : s.getPravougaonik()) {
					std::cout << "Koordinate tacke: x= " << p.getPocetak().second << "y= " << p.getPocetak().first << std::endl;
					std::cout << "Visina: " << p.getVisina() << ", sirina: " << p.getSirina() << std::endl << std::endl;
				}
			}

			break;
		default:std::cout << "Uneta opcija ne postoji" << std::endl;
			break;
		}
	}
	std::cout << "Program se zavrsava. Da li zelite da sacuvate dosadasnji rad? Slika ce se cuvati u Xml-formatu." << std::endl;
	std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
	if (pom.compare("da") == 0 || pom.compare("Da") == 0) {
		std::cout << "Ucitati putanju izlaznog fajla." << std::endl;
		std::cin >> path;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		std::cout << "Ucitati naziv izlaznog fajla." << std::endl;
		std::cin >> pom;  std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		Xml x;
		path = spoji((char*)path.c_str(),(char*) "\\");
		x.ispisi((char*)spoji((char*)path.c_str(), (char*)pom.c_str()), *m);
	}
	delete m;
}

int main(int argc, char* argv[]) {
	Image::postaviPocetneFje();
	if (argc > 2) {
		Image *m;
		int n = strlen(argv[1]);
		if (n > 4 && (argv[1][n - 4] == '.') && (argv[1][n - 3] == 'x') && (argv[1][n - 2] == 'm') && (argv[1][n - 1] == 'l')) {
			Xml x;
			m = x.ucitaj(argv[1]);

		}
		else {
			m = new Image(argv[1]);
		}
		ucitaj_funkciju(argv[2]);
		if (Image::operacije.size() > 15)
			m->pokreni(Image::operacije[Image::operacije.size() - 1]->get_name());

		
			if (n > 4 && (argv[1][n - 4] == '.') && (argv[1][n - 3] == 'x') && (argv[1][n - 2] == 'm') && (argv[1][n - 1] == 'l')) {
				Xml x;
				x.ispisi(argv[1] , *m);

			}
			else {
				m->ispisi(argv[1]);
			}


			return 0;
	}
	else {
			
		user();



		return 0;
	}
}


