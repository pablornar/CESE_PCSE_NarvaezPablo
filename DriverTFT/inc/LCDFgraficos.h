/*
 * LCDFgraficos.h
 *
 * Created: 27/02/2021 8:17:43
 *  Author: Pablo
 */

#ifndef LCDFGRAFICOS_H_
#define LCDFGRAFICOS_H_
void setColorb(uint8_t r, uint8_t g, uint8_t b) {
	fch = ((r & 248) | g >> 5);
	fcl = ((g & 28) << 3 | b >> 3);
}

void setColor(int color) {
	//fch=Byte(color>>8);
	//fcl=Byte(color & 0xFF);
	fch = (color >> 8);
	fcl = (color & 0xFF);
}

void setBackColorb(uint8_t r, uint8_t g, uint8_t b) {
	bch = ((r & 248) | g >> 5);
	bcl = ((g & 28) << 3 | b >> 3);
	_transparent = false;
}

void setBackColor(uint32_t color) {
	if (color == VGA_TRANSPARENT)
		_transparent = true;
	else {
		//bch=Byte(color>>8);
		//bcl=Byte(color & 0xFF);
		bch = (color >> 8);
		bcl = (color & 0xFF);
		_transparent = false;
	}
}

//para dibujar una line horizontal l pixeles
void drawHLine(int x, int y, int l) {
	if (l < 0) {
		l = -l;
		x -= l;
	}
	//cbi(P_CS, B_CS);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);

	setXY(x, y, x + l, y);
	if (display_transfer_mode == 16) {
		//sbi(P_RS, B_RS);
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
		gpioWrite(RS, ON);
		_fast_fill_16(fch, fcl, l);
	}

	//sbi(P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);
	clrXY();
}

//para graficar linea horizontal l pixeles
void drawVLine(int x, int y, int l) {
	if (l < 0) {
		l = -l;
		y -= l;
	}
	//cbi(P_CS, B_CS);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);
	setXY(x, y, x, y + l);
	if (display_transfer_mode == 16) {
		//sbi(P_RS, B_RS);
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
		gpioWrite(RS, ON);

		_fast_fill_16(fch, fcl, l);
	}

	//sbi(P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);
	clrXY();
}

//para dibujar una linea mediante dos puntos
void drawLine(int x1, int y1, int x2, int y2) {
	if (y1 == y2)
		drawHLine(x1, y1, x2 - x1);
	else if (x1 == x2)
		drawVLine(x1, y1, y2 - y1);
	else {
		unsigned int dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		short xstep = x2 > x1 ? 1 : -1;
		unsigned int dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		short ystep = y2 > y1 ? 1 : -1;
		int col = x1, row = y1;

		//cbi(P_CS, B_CS);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
		gpioWrite(CS, OFF);
		if (dx < dy) {
			int t = -(dy >> 1);
			while (true) {
				setXY(col, row, col, row);
				LCD_Write_DATAb(fch, fcl);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0) {
					col += xstep;
					t -= dy;
				}
			}
		} else {
			int t = -(dx >> 1);
			while (true) {
				setXY(col, row, col, row);
				LCD_Write_DATAb(fch, fcl);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0) {
					row += ystep;
					t -= dx;
				}
			}
		}
		//sbi(P_CS, B_CS);
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
		gpioWrite(CS, ON);
	}
	clrXY();
}

// para enviar el dato del pixel
void setPixel(int color) {
	LCD_Write_DATAb((color >> 8), (color & 0xFF));  // rrrrrggggggbbbbb
}

//para dibujar un pixel en x e y
void drawPixel(int x, int y) {
	//cbi(P_CS, B_CS);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);
	setXY(x, y, x, y);
	setPixel((fch << 8) | fcl);
	//sbi(P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);
	clrXY();
}

//Para imprimir un caracter ASCII en x e y
void printCharAscii(uint8_t c, int x, int y) {
	uint8_t i, ch;
	int j;
	int temp;

	//cbi(P_CS, B_CS);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);
	if (!_transparent) {
		if (orient == PORTRAIT) {
			setXY(x, y, x + cfont.x_size - 1, y + cfont.y_size - 1);

			temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size))
					+ 4;
			for (j = 0; j < ((cfont.x_size / 8) * cfont.y_size); j++) {
				ch = pgm_read_byte(&cfont.font[temp]);
				for (i = 0; i < 8; i++) {
					if ((ch & (1 << (7 - i))) != 0) {
						setPixel((fch << 8) | fcl);
					} else {
						setPixel((bch << 8) | bcl);
					}
				}
				temp++;
			}
		} else {
			temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size))
					+ 4;

			for (j = 0; j < ((cfont.x_size / 8) * cfont.y_size);
					j += (cfont.x_size / 8)) {
				setXY(x, y + (j / (cfont.x_size / 8)), x + cfont.x_size - 1,
						y + (j / (cfont.x_size / 8)));
				for (int zz = (cfont.x_size / 8) - 1; zz >= 0; zz--) {
					ch = pgm_read_byte(&cfont.font[temp + zz]);
					for (i = 0; i < 8; i++) {
						if ((ch & (1 << i)) != 0) {
							setPixel((fch << 8) | fcl);
						} else {
							setPixel((bch << 8) | bcl);
						}
					}
				}
				temp += (cfont.x_size / 8);
			}
		}
	} else {
		temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
		for (j = 0; j < cfont.y_size; j++) {
			for (int zz = 0; zz < (cfont.x_size / 8); zz++) {
				ch = pgm_read_byte(&cfont.font[temp + zz]);
				for (i = 0; i < 8; i++) {

					if ((ch & (1 << (7 - i))) != 0) {
						setXY(x + i + (zz * 8), y + j, x + i + (zz * 8) + 1,
								y + j + 1);
						setPixel((fch << 8) | fcl);
					}
				}
			}
			temp += (cfont.x_size / 8);
		}
	}

	//sbi(P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);
	clrXY();
}

#endif /* LCDFGRAFICOS_H_ */
