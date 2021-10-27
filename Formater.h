#pragma once

#include "BMP.h"
#include "PAM.h"
#include "layer.h"
#include <cstdint>


class Formater {
	int status; // 0 - nije koristen , 1 - bmp24  , 2 - bmp32 , 3 - ramRGPA , 4-Xml

public:
	int getStatus() const { return status; }
	void setStatus(int stat) { status = stat; }

	Layer* ucitaj(const char* path, uint8_t prozirnost = 100);
	void ispisi(char* path, char* name , Layer& l);
	void ispisi(char*path, Layer& l);


				
};

const char* spoji(char*, char*);