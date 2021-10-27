#pragma once

#include "layer.h"
#include <cstdint>
#include "Formater.h"



class BMP {
	friend class Formater;

	Layer* ucitaj(const char* path, uint8_t prozirnost = 100);
	void ispisi_24(const char* path,  Layer& slika);
	void ispisi_32(const char* path, Layer& slika);
};
