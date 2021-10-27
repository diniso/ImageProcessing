#include "BMP.h"
#include <cstdint>
#include "Piksel.h"
#include <fstream>
#include <iostream>



Layer* BMP::ucitaj(const char* path, uint8_t prozirnost) {
	uint32_t  offset_piksel , fleg;
	int32_t sirina, visina;
	uint16_t bpp , tip;
	std::vector<std::vector<Piksel>> niz;
	std::ifstream ulaz((char*)path, std::ios::binary);
	if (ulaz) {
		ulaz.read((char*)&tip, 2);
		if (tip != 0x4D42) throw std::runtime_error("Nepostojeci tip formata.\n");
		ulaz.seekg(10);
		//	ulaz >> offset_piksel;  
		ulaz.read((char*)&offset_piksel, 4);
		ulaz.seekg(18);
		//	ulaz >> sirina >> visina;
		ulaz.read((char*)&sirina, 4);
		ulaz.read((char*)&visina, 4);
		if (visina < 0) throw std::runtime_error("Ne moze da se ucitava sa te strane.\n");
		ulaz.seekg(28);
		//	ulaz >> bpp >> fleg;
		ulaz.read((char*)&bpp, 2);
		ulaz.read((char*)&fleg, 4);
		ulaz.seekg(offset_piksel);
		if (bpp == 24) {
			// 24bit
			uint8_t gree1, gree2, blu1, blu2, re1, re2;
			uint16_t ped;
			if (sirina % 4 != 0 ) { // postoji padding
				for (int j = 0; j < visina; j++) {
					std::vector<Piksel> pom;
					for (int i = 0; i < sirina / 2; i++) {
						ulaz.read((char*)&blu1, 1);
						ulaz.read((char*)&gree1, 1);
						ulaz.read((char*)&re1, 1);
						ulaz.read((char*)&blu2, 1);
						ulaz.read((char*)&gree2, 1);
						ulaz.read((char*)&re2, 1);
						ulaz.read((char*)&ped, 2);
						Piksel p1(re1, gree1, blu1 , 255), p2(re2, gree2, blu2 , 255);
						pom.push_back(p1);
						pom.push_back(p2);
					}
					niz.push_back(pom);
				}
			}
			else {
				for (int j = 0; j < visina; j++) {
					std::vector<Piksel> pom;
					for (int i = 0; i < sirina / 2; i++) {
						ulaz.read((char*)&blu1, 1);
						ulaz.read((char*)&gree1, 1);
						ulaz.read((char*)&re1, 1);
						ulaz.read((char*)&blu2, 1);
						ulaz.read((char*)&gree2, 1);
						ulaz.read((char*)&re2, 1);
						Piksel p1(re1, gree1, blu1 , 255), p2(re2, gree2, blu2 , 255);
						pom.push_back(p1);
						pom.push_back(p2);
					}
					niz.push_back(pom);
				}
			}
			Layer *l = new Layer(niz, visina, sirina , prozirnost);
			ulaz.close();
			return l;
		}
		else { // obradi 32
			uint8_t gree1, gree2, blu1, blu2, re1, re2, alfa1 , alfa2;
			for (int j = 0; j < visina; j++) {
				std::vector<Piksel> pom;
				for (int i = 0; i < sirina / 2; i++) {
					ulaz.read((char*)&blu1, 1);
					ulaz.read((char*)&gree1, 1);
					ulaz.read((char*)&re1, 1);
					ulaz.read((char*)&alfa1, 1);
					ulaz.read((char*)&blu2, 1);
					ulaz.read((char*)&gree2, 1);
					ulaz.read((char*)&re2, 1);
					ulaz.read((char*)&alfa2, 1);
					Piksel p1(re1, gree1, blu1, alfa1), p2(re2, gree2, blu2, alfa2);
					pom.push_back(p1);
					pom.push_back(p2);
				}
				niz.push_back(pom);
			}
			Layer *l = new Layer(niz , visina , sirina , prozirnost);
			ulaz.close();
			return l;
		}
	}
	else { // fajl nije otvoren

			std::cout << "fajl nije otvoren. Stvorice se prazan sloj. " << std::endl;
			Layer *l = new Layer(400 , 400);
			return l;
	}
}


void BMP::ispisi_24(const char* path, Layer& slika) {
	std::ofstream izlaz(path, std::ios::binary);
	uint32_t size  = slika.get_piksels().size(), pom2 = 0 , visina , sirina;
	visina = slika.get_visina();
	sirina = slika.get_sirina();
	uint16_t pom = 0x4d42;
	if (sirina % 4 == 0)  size *= 3;
	else size *= 4;
	if (izlaz) {
		izlaz.write((char*)&pom, 2); // govori o vrsti bmp formata
		size += 54;
		izlaz.write((char*)&size, 4); // velicina fajla
		izlaz.write((char*)&pom2, 4); // nebitni biti
		pom2 = 54;
		izlaz.write((char*)&pom2, 4); // offset_piksela, broj bajtova ukupno u oba zaglavlja
		pom2 = 40;
		izlaz.write((char*)&pom2, 4); // velicina DIB zaglavlja
		izlaz.write((char*)&sirina, 4);// sirina
		izlaz.write((char*)&visina, 4); // visina
		pom = 1;
		izlaz.write((char*)&pom, 2); // karatna boja, nije bitno
		pom = 24;
		izlaz.write((char*)&pom, 2); // broj bita po pikselu
		pom2 = 0;
		izlaz.write((char*)&pom2, 4); // kompresija
		size -= 54;
		izlaz.write((char*)&size, 4); // velicina piksela
		pom2 = 2835;
		izlaz.write((char*)&pom2, 4);
		izlaz.write((char*)&pom2, 4);
		pom2 = 0;
		izlaz.write((char*)&pom2, 4);
		izlaz.write((char*)&pom2, 4);
		// ispis piksela
		pom = 0; // dopunjavanje
		pom2 = 0;
		uint8_t red, blue, green;
		if (sirina % 4 != 0 ) { // ako treba
			for (std::vector<Piksel> s : slika.get_piksels()) {
				for (Piksel p : s) {
					red = p.get_red();
					blue = p.get_blue();
					green = p.get_green();
					izlaz.write((char*)&blue, 1);
					izlaz.write((char*)&green, 1);
					izlaz.write((char*)&red, 1);
					if (pom2) {
						izlaz.write((char*)&pom, 2);
						pom2 = 0;
					}
					else pom2++;
				}
			}
		}
		else { // ako ne treba padding
			for (std::vector<Piksel> s : slika.get_piksels()) {
				for (Piksel p : s) {
					red = p.get_red();
					blue = p.get_blue();
					green = p.get_green();
					izlaz.write((char*)&blue, 1);
					izlaz.write((char*)&green, 1);
					izlaz.write((char*)&red, 1);
				}
			}
		}
		izlaz.close();

	}
	else { std::cout << "Output fajl nije otvoren." << std::endl; }
}

void BMP::ispisi_32(const char* path, Layer& slika) {
	std::ofstream izlaz(path, std::ios::binary);
	uint32_t size = slika.get_piksels().size() * 4, pom2 = 0, visina, sirina;
	visina = slika.get_visina();
	sirina = slika.get_sirina();
	uint16_t pom = 0x4d42;
	if (izlaz) {
		izlaz.write((char*)&pom, 2); // govori o vrsti bmp formata
		size += 122;
		izlaz.write((char*)&size, 4); // velicina fajla
		izlaz.write((char*)&pom2, 4); // nebitni biti
		pom2 = 122;
		izlaz.write((char*)&pom2, 4); // offset_piksela, broj bajtova ukupno u oba zaglavlja
		pom2 = 108;
		izlaz.write((char*)&pom2, 4); // velicina DIB zaglavlja
		izlaz.write((char*)&sirina, 4);// sirina
		izlaz.write((char*)&visina, 4); // visina
		pom = 1;
		izlaz.write((char*)&pom, 2); // karatna boja, nije bitno
		pom = 32;
		izlaz.write((char*)&pom, 2); // broj bita po pikselu
		pom2 = 3;
		izlaz.write((char*)&pom2, 4); // kompresija
		size -= 122;
		izlaz.write((char*)&size, 4); // velicina piksela
		pom2 = 2835;
		izlaz.write((char*)&pom2, 4);
		izlaz.write((char*)&pom2, 4);
		pom2 = 0;
		izlaz.write((char*)&pom2, 4);
		izlaz.write((char*)&pom2, 4);
		pom2 = 0x00FF0000;
		izlaz.write((char*)&pom2, 4); // crveni maska
		pom2 = 0x0000FF00;
		izlaz.write((char*)&pom2, 4);// zeleni maska
		pom2 = 0x000000FF;
		izlaz.write((char*)&pom2, 4); // alfa maska
		pom2 = 0xFF000000;
		izlaz.write((char*)&pom2, 4); // alfa maska
		pom2 = 0x57696e20;
		izlaz.write((char*)&pom2, 4); //nesto ya win
		pom2 = 0;
		for (int i = 0; i < 12; i++) {
			izlaz.write((char*)&pom2, 4); // nesto za win
		}
		// ispis piksela
		uint8_t red, green, blue, alfa;
		for (std::vector<Piksel> s : slika.get_piksels()) {
			for (Piksel p : s) {
				red = p.get_red();
				blue = p.get_blue();
				green = p.get_green();
				alfa = p.get_alfa();
				izlaz.write((char*)&blue, 1);
				izlaz.write((char*)&green, 1);
				izlaz.write((char*)&red, 1);
				izlaz.write((char*)&alfa, 1);
			}
		}
		izlaz.close();
	}
	else { std::cout << "Output fajl nije otvoren." << std::endl; }
}



