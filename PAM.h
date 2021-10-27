#pragma once

#include <cstdint>
#include "layer.h"
#include "Formater.h"

class Pam {
	friend class Formater;
	Layer* ucitaj(const char* path, uint8_t prozirnost = 100);
	void ispisi(const char* path, Layer& l); // ispisuje iskljucivo u RGBA 255
};
