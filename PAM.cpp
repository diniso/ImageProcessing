#include "PAM.h"
#include <cstdint>
#include <fstream>
#include "layer.h"
#include <string>
#include <iostream>


Layer* Pam::ucitaj(const char* path, uint8_t prozirnost) {
	char strin[255];
	char pom;
	int i = 0;
	uint8_t red, blue, green, alfa ;
	uint32_t visina, sirina , broj_kanala , maks;
	std::ifstream ulaz((char*)path, std::ios::binary);
	if (ulaz) {
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x20) break;
		} // ucitao "P7.WIDTH " // ucitao sve do praznog znaka
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
			strin[i++] = pom;
		} // ucitao sirinu
		strin[i++] = '\0';
		sirina = atoi(strin);
		i = 0;


		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x20) break;
		} // ucitao opet sve do praznog znaka
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
			strin[i++] = pom;
		} // ucitao visinu
		strin[i++] = '\0';
		visina = atoi(strin);
		i = 0;


		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x20) break;
		}  // ucitao sve do praznog znaka
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
			strin[i++] = pom;
		} // ucitao broj kanala
		strin[i++] = '\0';
		broj_kanala = atoi(strin);
		i = 0;

		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x20) break;
		}  // ucitao sve do praznog znaka
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
			strin[i++] = pom;
		} // maks vrednost piksela
		strin[i++] = '\0';
		maks = atoi(strin);
		i = 0;


		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x20) break;
		}  // ucitao sve do praznog znaka
		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
			strin[i++] = pom;
		} // tip
		strin[i++] = '\0';

		while (1) {
			ulaz.read((char*)&pom, 1);
			if (pom == 0x0a) break;
		} // zarvsio header, sad ide ucitavanje piksela


	//	std::cout << visina << " " << sirina << " " << broj_kanala << " " << maks << " " << strin << std::endl;
		
		std::vector<std::vector<Piksel>> mat;

		if ((!strcmp(strin, "RGB_ALPHA") )&& maks == 255) {
			for (unsigned i = 0; i < visina; i++) {
				std::vector<Piksel> niz;
				for (unsigned j = 0; j < sirina; j++) {
					ulaz.read((char*)&red, 1);
					ulaz.read((char*)&green, 1);
					ulaz.read((char*)&blue, 1);
					ulaz.read((char*)&alfa, 1);
					Piksel p(red, green, blue, alfa);
					niz.push_back(p);
				}
				mat.push_back(niz);
			//	ulaz.read((char*)&red, 1); // ucitaj znak za novi red
			}

		}


		ulaz.close();
		Layer *l = new Layer(mat, visina, sirina, prozirnost);
		return l;





	}
	else {
		std::cout << "fajl nije otvoren. Stvorice se prazan sloj. " << std::endl;
		Layer *l = new Layer(400, 400);
		return l;
	}
}




void Pam::ispisi(const char* path, Layer& l) {
	std::ofstream izlaz(path, std::ios::binary);
	uint8_t pom = 0x0a;
	if (izlaz) {
		std::string izla = "P7";
		izla += '\n';
		izla += "WIDTH ";
		izla += std::to_string(l.get_sirina());
		izla += '\n';
		izla += "HEIGHT ";
		izla += std::to_string(l.get_visina());
		izla += '\n';
		izla += "DEPTH 4";
		izla += '\n'; 
		izla += "MAXVAL 255";
		izla += '\n'; 
		izla += "TUPLTYPE RGB_ALPHA";
		izla += '\n'; 
		izla += "ENDHDR";
		izla += '\n';
		izlaz.write(izla.c_str(), izla.size());

		for (unsigned i = 0; i < l.get_visina();i++) {
			for (unsigned j = 0; j < l.get_sirina(); j++) {
				pom = l.get_piksels()[i][j].get_red();
				izlaz.write((char*)&pom, 1);
				pom = l.get_piksels()[i][j].get_green();
				izlaz.write((char*)&pom, 1);
				pom = l.get_piksels()[i][j].get_blue();
				izlaz.write((char*)&pom, 1);
				pom = l.get_piksels()[i][j].get_alfa();
				izlaz.write((char*)&pom, 1);

			}

		//	izlaz.write((char*)&pom, 1);
		}
		izlaz.close();

	}
	else std::cout << "Izlazni fajl nije mogao da se otvori." << std::endl;
}


