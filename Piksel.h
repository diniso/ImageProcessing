#pragma once
#include<cstdint>


class Piksel {
	uint8_t red, green, blue , alfa;
public:
	Piksel(uint8_t re = 255, uint8_t gree = 255, uint8_t blu = 255, uint8_t alf = 0) {
		red = re;
		blue = blu;
		green = gree;
		alfa = alf;
	}

	uint8_t get_red() const { return red; }
	uint8_t get_blue() const { return blue; }
	uint8_t get_green() const { return green; }
	uint8_t get_alfa() const { return alfa; }

	void set_red(uint8_t re) { red = re; }
	void set_blue(uint8_t blu) { blue = blu; }
	void set_green(uint8_t gree) { green = gree; }
	void set_alfa(uint8_t alf) { alfa = alf; }

	void operator+= (const Piksel& p) {

		this->red += p.red;
		this->blue += p.blue;
		this->alfa += p.alfa;
		this->green += p.green;
	}
};
