#pragma once
#include <cstdint>
#include <vector>

class Pravougaonik {
	std::pair<int, int>  koordinate;// gore levo
	int visina, sirina;

public:
	Pravougaonik(std::pair<int, int> tacka, int vis, int sir) {
		koordinate = tacka;
		visina = vis;
		sirina = sir;
	}


	int getVisina() const { return visina; }
	int getSirina() const { return sirina; }
	std::pair<int, int> getPocetak() const { return koordinate; }
};
