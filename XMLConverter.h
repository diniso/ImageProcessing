#pragma once
#include "Image.h"

class Image;
class Xml {
public:
	Image* ucitaj(const char* path);
	void ispisi(const char* path, Image& m);
};
