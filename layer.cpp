#include "layer.h"
#include <vector>




Layer::Layer(uint32_t vis, uint32_t sir, uint8_t prozirnos) {
	visina = vis;
	sirina = sir;
	prozirnost = prozirnos;
	active = visible = false;
	for (unsigned i = 0; i < vis; i++) {
		std::vector<Piksel> pom;
		for (unsigned j = 0; j < sir; j++) {
			pom.push_back(Piksel(0 , 0 , 0 ,0));
		}
		niz.push_back(pom);
	}

}

Layer::Layer(std::vector<std::vector<Piksel>>& pik, uint32_t vis, uint32_t sir, uint32_t prozirnos) {
	visina = vis;
	sirina = sir;
	prozirnost = prozirnos;
	active = visible = true;
	niz = pik;
}

Layer::Layer() {
	prozirnost = 0;
}
