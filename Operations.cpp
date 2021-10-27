#include "Operations.h"
#include "Image.h"
#include "layer.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <exception>

using namespace rapidxml;

void Sabiranje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Sabiranje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina()- p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < ( p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void Oduzimanje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Oduzimanje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void InverznoOduzimanje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void InverznoOduzimanje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void Mnozenje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Mnozenje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void Deljenje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Deljenje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void InverznoDeljenje::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void InverznoDeljenje::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void Stepen::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Stepen::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}



void Logaritam::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Logaritam::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void ApsolutnaVrednost::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void ApsolutnaVrednost::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void Minimum::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Minimum::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (m.get_active()) {
			if (!l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void Maksimum::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Maksimum::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void Inverzija::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		radi(value);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		radi(value);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		radi(value);
		p.set_green(promenljiva);
	}
}

void Inverzija::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void CrnoBela::piksel_operation(Piksel& p, int value) {
	promenljiva = 0;
	dodaj(p.get_red());
	dodaj(p.get_blue());
	dodaj(p.get_green());
	podeli();
	radi(value);
	p.set_red(promenljiva);

	p.set_blue(promenljiva);

	p.set_green(promenljiva);
}

void CrnoBela ::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void Siva::piksel_operation(Piksel& p, int value) {
	promenljiva = 0;
	dodaj(p.get_red());
	dodaj(p.get_blue());
	dodaj(p.get_green());
	podeli();
	p.set_red(promenljiva);

	p.set_blue(promenljiva);

	p.set_green(promenljiva);
}

void Siva::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}






void Medijana::piksel_operation(Piksel& p, int value) {
	
	count++;
	crvena += p.get_red();
	zelena += p.get_green();
	plava += p.get_blue();


}

void Medijana::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active() || (m.get_active() && l.get_acitive())) {
			std::vector<std::vector<Piksel>> mat;
			for (unsigned i = 0; i < l.get_visina(); i++) {
				std::vector<Piksel> niz;
				for (unsigned j = 0; j < l.get_sirina(); j++) {
					crvena = plava = zelena = count = 0;
					if (i == 0 && j == 0) {
						piksel_operation(l.get_piksels()[i + 1][j]);
						piksel_operation(l.get_piksels()[i ][j +1]);
						piksel_operation(l.get_piksels()[i + 1][j +1]);
					}
					else if (i == 0 && j == (l.get_sirina()-1)) {
						piksel_operation(l.get_piksels()[i + 1][j]);
						piksel_operation(l.get_piksels()[i][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j - 1]);
					}
					else if(i == (l.get_visina()-1) && j == (l.get_sirina() - 1)){
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i][j - 1]);
						piksel_operation(l.get_piksels()[i - 1][j - 1]);
					}
					else if(i == (l.get_visina() - 1) && j == 0) {
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i][j + 1]);
						piksel_operation(l.get_piksels()[i - 1][j + 1]);
					}
					else if (i == 0) {
						piksel_operation(l.get_piksels()[i + 1][j]);
						piksel_operation(l.get_piksels()[i][j + 1]);
						piksel_operation(l.get_piksels()[i + 1][j + 1]);
						piksel_operation(l.get_piksels()[i ][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j - 1]);
					}
					else if (i == (l.get_visina() - 1)) {
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i][j + 1]);
						piksel_operation(l.get_piksels()[i - 1][j - 1]);
						piksel_operation(l.get_piksels()[i][j - 1]);
						piksel_operation(l.get_piksels()[i - 1][j + 1]);
					}
					else if (j == 0) {
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i-1][j + 1]);
						piksel_operation(l.get_piksels()[i ][j + 1]);
						piksel_operation(l.get_piksels()[i + 1][j + 1]);
						piksel_operation(l.get_piksels()[i + 1][j]);
					}
					else if (j == (l.get_sirina() - 1)) {
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i - 1][j - 1]);
						piksel_operation(l.get_piksels()[i][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j]);
					}
					else {
						piksel_operation(l.get_piksels()[i - 1][j]);
						piksel_operation(l.get_piksels()[i - 1][j - 1]);
						piksel_operation(l.get_piksels()[i][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j - 1]);
						piksel_operation(l.get_piksels()[i + 1][j]);

						piksel_operation(l.get_piksels()[i- 1][j + 1]);
						piksel_operation(l.get_piksels()[i ][j + 1]);
						piksel_operation(l.get_piksels()[i + 1][j]);
					}
					podeli(count);
					Piksel p(crvena, zelena, plava, l.get_piksels()[i][j].get_alfa());
					niz.push_back(p);
				}
				mat.push_back(niz);
			}
			//prebaciti referencu na stvoren niz
			l.set_piksels(mat);
		}
	}
}





void Kompozitna::piksel_operation(Piksel& p, int value) {
	if (crvena) {
		promenljiva = p.get_red();
		for (unsigned i = 0; i < fje.size(); i++)
			fje[i].first->radi(fje[i].second);
		p.set_red(promenljiva);
	}

	if (plava) {
		promenljiva = p.get_blue();
		for (unsigned i = 0; i < fje.size(); i++)
			fje[i].first->radi(fje[i].second);
		p.set_blue(promenljiva);
	}

	if (zelena) {
		promenljiva = p.get_green();
		for (unsigned i = 0; i < fje.size(); i++)
			fje[i].first->radi(fje[i].second);
		p.set_green(promenljiva);
	}
}

void Kompozitna::operation(Image& m, int value) {
	for (Layer &l : m.get_slojevi()) {
		if (!m.get_active()) {
			if (l.get_acitive()) {
				for (std::vector<Piksel> &v : l.get_piksels()) {
					for (Piksel &p : v) {
						piksel_operation(p, value);
					}
				}
			}
		}
		else {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									piksel_operation(l.get_piksels()[poz1][poz2], value);
								}
							}
						}
					}
				}
			}
		}
	}
}




void ucitaj_funkciju(const char* putanja) {
	std::vector<std::pair<Operation*, int>> niz;
	std::string name, text;
	bool flag = false;

	int n = strlen(putanja);
	if (n > 8 && (putanja[n - 8] == '.') && (putanja[n - 7] == 'f') && (putanja[n - 6] == 'u') && (putanja[n - 5] == 'n') &&
		(putanja[n - 4] == '.') && (putanja[n - 3] == 't') && (putanja[n - 2] == 'x') && (putanja[n - 1] == 't')
		) {
		flag = true;
		std::ifstream ula((char*)putanja);
		if (ula) {
			ula >> name;
			getline(ula, text);
			std::regex rx("[' ']*([a-z]*)[' ']*\\([' ']*([0-9]*)[' ']*\\).*");
			int count = 1;
			while (getline(ula, text)) {
				std::smatch result;
				if (regex_match(text, result, rx)) {
					std::string fja = result.str(1);
					int par = atoi(result.str(2).c_str());
					Operation *o = nullptr;
					if (fja.compare("sabiranje") == 0) o = new Sabiranje();
					if (fja.compare("oduzimanje") == 0) o = new Oduzimanje();
					if (fja.compare("inverznooduzimanje") == 0) o = new InverznoOduzimanje();
					if (fja.compare("mnozenje") == 0) o = new Mnozenje();
					if (fja.compare("deljenje") == 0) o = new Deljenje();
					if (fja.compare("inverznodeljenje") == 0) o = new InverznoDeljenje();
					if (fja.compare("stepen") == 0) o = new Stepen();
					if (fja.compare("logaritam") == 0) o = new Logaritam();
					if (fja.compare("minimum") == 0) o = new Minimum();
					if (fja.compare("maksimum") == 0) o = new Maksimum();
					if (fja.compare("aposolutnavrednost") == 0) o = new ApsolutnaVrednost();

					if (o == nullptr) {
						std::cout << "Fja na ne postoji. Fja sadrzi ucitane fje do reda: " << count << std::endl;
						break;
					}

					count++;
					std::pair<Operation*, int> pa(o, par);
					niz.push_back(pa);



				}
				else {
					std::cout << "Uneseni fajl nije ispravnog formata. Fja sadrzi ucitane fje do reda: " << count << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "Putanja do fajla ne postoji(funkcije)!" << std::endl;
		}
	}
	else if (n > 8 && (putanja[n - 8] == '.') && (putanja[n - 7] == 'f') && (putanja[n - 6] == 'u') && (putanja[n - 5] == 'n') &&
		(putanja[n - 4] == '.') && (putanja[n - 3] == 'x') && (putanja[n - 2] == 'm') && (putanja[n - 1] == 'l')
		) {
		flag = true;
		xml_document<> doc;
		xml_node<> * root_node;
		try {
			file<> f(putanja);
			doc.parse<0>(&(f.data()[0]));

			root_node = doc.first_node("kompozitna");
			name = root_node->first_attribute("ime")->value();
			int m = std::stoi(root_node->first_attribute("br")->value());

			root_node = root_node->first_node("funkcija");

			for (int i = 0; i < m; i++) {
				std::string prov = root_node->first_attribute("ime")->value();
				int par = std::stoi(root_node->first_attribute("par")->value());
				Operation* o = nullptr;

				if (prov.compare("sabiranje") == 0) o = new Sabiranje();
				if (prov.compare("oduzimanje") == 0) o = new Oduzimanje();
				if (prov.compare("inverznooduzimanje") == 0) o = new InverznoOduzimanje();
				if (prov.compare("mnozenje") == 0) o = new Mnozenje();
				if (prov.compare("deljenje") == 0) o = new Deljenje();
				if (prov.compare("inverznodeljenje") == 0) o = new InverznoDeljenje();
				if (prov.compare("stepen") == 0) o = new Stepen();
				if (prov.compare("logaritam") == 0) o = new Logaritam();
				if (prov.compare("minimum") == 0) o = new Minimum();
				if (prov.compare("maksimum") == 0) o = new Maksimum();
				if (prov.compare("aposolutnavrednost") == 0) o = new ApsolutnaVrednost();

				if (o == nullptr) {
					std::cout << "Fja na ne postoji. Fja sadrzi ucitane fje do reda: " << (i + 1) << std::endl;
					break;
				}
				niz.push_back(std::pair<Operation*, int>(o, par));

				root_node = root_node->next_sibling();
			}

		}
		catch (std::exception& e) {
			std::cout << "Xml fajl nije moguce ucitati!" << std::endl;
		}
	}


	if (flag) Image::dodajFunkciju(name, niz);
	else std::cout << "Putanja do funkicje nije dobrog formata!" << std::endl;
	
}


void Operation::obojiPiksele(Image& m, uint8_t red, uint8_t green, uint8_t blue , uint8_t alfa) {
	if (m.get_active()) {
		for (Layer &l : m.get_slojevi()) {
			if (l.get_acitive()) {
				for (unsigned i = 0; i < m.get_selection().size(); i++) {
					if (m.get_selection()[i].getActive()) {
						for (Pravougaonik &p : m.get_selection()[i]) {
							for (unsigned poz1 = l.get_visina() - p.getPocetak().first; poz1 > (l.get_visina() - p.getPocetak().first - p.getVisina()) && poz1 > 0; poz1--) {
								for (unsigned poz2 = p.getPocetak().second; poz2 < (p.getPocetak().second + p.getSirina()) && poz2 < l.get_sirina(); poz2++) {
									l.get_piksels()[poz1][poz2].set_red(red);
									l.get_piksels()[poz1][poz2].set_green(green);
									l.get_piksels()[poz1][poz2].set_blue(blue);
									l.get_piksels()[poz1][poz2].set_alfa(alfa);
								}
							}
						}
					}
				}
			}
		}
	}
	else std::cout << "Slika nije aktivna.Nije moguce raditi sa selekcijama" << std::endl;
}




