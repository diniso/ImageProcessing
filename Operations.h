#pragma once

#include "Image.h"
#include <cstdint>
#include <string>
#include <algorithm>
#include <math.h>

class Image;

class Operation {
	std::string name;

protected:
	virtual void piksel_operation(Piksel& p, int value) {}
	static int promenljiva;
	static bool crvena, plava, zelena;

public:


	virtual void radi(int value) {}
	Operation(std::string _name) { name = _name; }
	std::string get_name() { return name; }

	static void set_red(bool red) { crvena = red; }
	static void set_blue(bool blue) { plava = blue; }
	static void set_green(bool green) { zelena = green; }
	static bool get_red() { return crvena; }
	static bool get_blue() { return plava; }
	static bool get_green() { return zelena; }

	virtual void operation(Image& m, int value) = 0;

	void static obojiPiksele(Image& m, uint8_t red, uint8_t green, uint8_t blue, uint8_t alfa);
};


class Sabiranje : public Operation {

protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public :
	Sabiranje() : Operation("sabiranje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva += value; }
};



class Oduzimanje : public Operation {

protected:
	void piksel_operation(Piksel& p, int value) override final;

public:
	Oduzimanje() : Operation("oduzimanje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva -= value; }
};



class InverznoOduzimanje : public Operation {

protected :
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	InverznoOduzimanje() : Operation("inverznooduzimanje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = -promenljiva + value; }

};



class Mnozenje : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Mnozenje() : Operation("mnozenje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva *= value; }
};



class Deljenje : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Deljenje() : Operation("deljenje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva /= value; }
};


class InverznoDeljenje : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	InverznoDeljenje() : Operation("inverznodeljenje") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = value / promenljiva; }
};



class Stepen : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Stepen() : Operation("stepen") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = (int)pow(promenljiva, value); }
};



class Logaritam : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Logaritam() : Operation("logaritam") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = (int)log(promenljiva); }
};



class ApsolutnaVrednost : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	ApsolutnaVrednost() : Operation("apsolutnavrednost") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = abs(promenljiva); }
};



class Minimum : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Minimum() : Operation("minimum") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = std::min(promenljiva, value); }
};



class Maksimum : public Operation {
protected:
	
	void piksel_operation(Piksel& p, int value) override final;

public:
	Maksimum() : Operation("maksimum") {}

	void operation(Image& m, int value) final override;
	void radi(int value) final override { promenljiva = std::max(promenljiva, value); }
};




class Inverzija : public Operation {

protected:
	
	void piksel_operation(Piksel& p, int value = 0) override final;

public:
	Inverzija() : Operation("inverzija") {}

	void operation(Image& m, int value = 0) final override;
	void radi(int value = 0) final override { promenljiva = -promenljiva + 255; }

};




class CrnoBela : public Operation {

protected:
	void dodaj(int value) { promenljiva += value; }
	void podeli() { promenljiva /= 3; }

	void piksel_operation(Piksel& p, int value = 0) override final;

public:
	CrnoBela() : Operation("crnobela") {}

	void operation(Image& m, int value = 0) final override;
	void radi(int value = 0) final override { promenljiva > 127 ? promenljiva = 255 : promenljiva = 0; }
};


class Siva : public Operation {

protected:
	void dodaj(int value) { promenljiva += value; }
	void podeli() { promenljiva /= 3; }
	void piksel_operation(Piksel& p, int value = 0) override final;

public:
	Siva() : Operation("siva") {}

	void operation(Image& m, int value = 0) final override;


};




class Medijana : public Operation {
	int count;
	int crvena, plava, zelena;
protected:
	void podeli(int value) { 
		crvena /= value;
		plava /= value;
		zelena /= value;
	}
	void piksel_operation(Piksel& p, int value = 0) override final;
public:
	Medijana() : Operation("medijana") {}

	void operation(Image& m, int value = 0) final override;


};



class Kompozitna : public Operation {
	std::vector<std::pair<Operation* , int>> fje;

protected:
	void piksel_operation(Piksel& p, int value = 0) override final;

public:
	Kompozitna(std::string ime, std::vector<std::pair<Operation*, int>>& o) : Operation(ime) {
		fje = o;
	}

	std::vector<std::pair<Operation*, int>>& getOperations() { return fje; }
	void operation(Image& m, int value = 0) final override;
};



void ucitaj_funkciju(const char* putanja);
