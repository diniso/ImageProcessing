#pragma once

#include <vector>
#include <cstdint>
#include <map>
#include "Piksel.h"

class Layer {
	uint32_t visina, sirina;
	std::vector<std::vector<Piksel>> niz;
	bool active, visible;
	uint8_t prozirnost; // prozirnost 100-proziran , 0 neproziran

public:
	
	Layer();
	Layer(uint32_t vis , uint32_t sir , uint8_t prozirnos = 0);
	Layer(std::vector<std::vector<Piksel>>& pik, uint32_t vis , uint32_t sir , uint32_t prozirnos = 100);
	virtual ~Layer() {}


	void set_acitive(bool act) { active = act; }
	void set_visible(bool vis) { visible = vis; }
	void set_prozirnost(uint8_t prozirnos) { prozirnost = prozirnos; }
	void set_sirina(uint32_t si) { sirina = si; }
	void set_visina(uint32_t vi) {visina = vi; }
	void set_piksels(std::vector<std::vector<Piksel>>& mat) { niz = mat; }

	std::vector<std::vector<Piksel>>& get_piksels() { return niz; }
	bool get_acitive() const { return active; }
	bool get_visible() const { return visible; }
	uint32_t get_sirina() const { return sirina; }
	uint32_t get_visina() const { return visina; }
	uint8_t get_prozirnost() const { return prozirnost; }






};
