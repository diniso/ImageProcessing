#include "Formater.h"
#include "PAM.h"
#include "BMP.h"
#include "XMLConverter.h"
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS


Layer* Formater::ucitaj(const char* path, uint8_t prozirnost) {
	unsigned size = strlen(path);
	if (size < 4) std::cout << "Fajl ne postoji!" << std::endl;
	else {
		if ((path[size - 4] == '.') && (path[size - 3] == 'b') && (path[size - 2] == 'm') && (path[size - 1] == 'p')) {
			BMP b;
			status = 2;
			return b.ucitaj(path, prozirnost);
		}
		if ((path[size - 4] == '.') && (path[size - 3] == 'p') && (path[size - 2] == 'a') && (path[size - 1] == 'm')) {
			Pam p;
			status = 3;
			return p.ucitaj(path, prozirnost);
		}
		else {
			std::cout << "Program ne podrzava uneseni formati! Stvorena je podrazumevana slika." << std::endl;
			Layer *l = new Layer(400, 400);
			return l;
		}
	}
	Layer *l = new Layer(400, 400);
	return l;
}

void Formater::ispisi(char* path,  char* name, Layer& l){
	path = (char*)spoji(path, (char*)"\\");
	path = (char*)spoji(path, name);
	if (status == 1) {
		BMP b;
		path = (char*)spoji(path,(char*) ".bmp");
		b.ispisi_24(path, l);
	}
	if (status == 2) {
		BMP b;
		 path = (char*)spoji(path,(char*) ".bmp");
		b.ispisi_32(path , l);
	}
	if (status == 3) {
		Pam p;
		path = (char*)spoji(path,(char*) ".pam");
		p.ispisi(path, l);
	}
}

const char* spoji(char* prvi,char* drugi) {
	char *pom = (char*)malloc(strlen(prvi) + strlen(drugi) + 1);
	strcpy(pom, prvi);
	strcat(pom, drugi);
	return pom;
}


void Formater::ispisi(char*path, Layer& l) {
	unsigned size = strlen(path);
	if (size < 4) std::cout << "Fajl ne postoji!" << std::endl;
	else {
		if ((path[size - 4] == '.') && (path[size - 3] == 'b') && (path[size - 2] == 'm') && (path[size - 1] == 'p')) {
			BMP b;
			if (status == 1) b.ispisi_24(path, l);
			else b.ispisi_32(path, l);
		}
		if ((path[size - 4] == '.') && (path[size - 3] == 'p') && (path[size - 2] == 'a') && (path[size - 1] == 'm')) {
			Pam p;
			p.ispisi(path, l);
		}
	}
}