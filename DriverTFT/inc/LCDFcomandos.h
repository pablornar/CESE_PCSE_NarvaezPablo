/*
 * LCDFcomandos.h
 *
 * Created: 27/02/2021 8:11:01
 *  Author: Pablo
 */

#ifndef LCDFCOMANDOS_H_
#define LCDFCOMANDOS_H_

//para borrar el display
void clrScr(void) {
	long i;

	//cbi(P_CS, B_CS); pone a cero CS
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);

	clrXY();

	if (display_transfer_mode != 1)
		//sbi(P_RS, B_RS);
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
		gpioWrite(RS, ON);

	if (display_transfer_mode == 16)
		_fast_fill_16(0, 0, ((disp_x_size + 1) * (disp_y_size + 1)));
	else {
		for (i = 0; i < ((disp_x_size + 1) * (disp_y_size + 1)); i++) {
			if (display_transfer_mode != 1)
				LCD_Writ_Bus(0, 0, display_transfer_mode);
			else {
				LCD_Writ_Bus(1, 0, display_transfer_mode);
				LCD_Writ_Bus(1, 0, display_transfer_mode);
			}
		}
	}
	//sbi(P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);
	clrXY();
}

void clrXY(void) {
	if (orient == PORTRAIT)
		setXY(0, 0, disp_x_size, disp_y_size);
	else
		setXY(0, 0, disp_y_size, disp_x_size);
}

void _fast_fill_16(int ch, int cl, long pix) {
	long blocks;

	//REG_PIOA_CODR=0x0000C080;  //pone en cero los pines seleccionados
	gpioWrite(D6, OFF);
	gpioWrite(D9, OFF);
	gpioWrite(D10, OFF);
	//REG_PIOB_CODR=0x4000000;
	gpioWrite(D8, OFF);

	//REG_PIOC_CODR=0x0000003E;
	gpioWrite(D0, OFF);
	gpioWrite(D1, OFF);
	gpioWrite(D2, OFF);
	gpioWrite(D3, OFF);
	gpioWrite(D4, OFF);
	//REG_PIOD_CODR=0x0000064F;
	gpioWrite(D5, OFF);
	gpioWrite(D7, OFF);
	gpioWrite(D11, OFF);
	gpioWrite(D12, OFF);
	gpioWrite(D13, OFF);
	gpioWrite(D14, OFF);
	gpioWrite(D15, OFF);

	//REG_PIOA_SODR=((VH & 0x06)<<13) | ((VL & 0x40)<<1);   //pone en 1 los bits seleccionados por puerto
	if ((cl & 0x040)) {
		gpioWrite(D6, ON);
	}
	if ((ch & 0x02)) {
		gpioWrite(D9, ON);
	}
	if ((ch & 0x04)) {
		gpioWrite(D10, ON);
	}
	//(VH & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
	if ((ch & 0x01)) {
		gpioWrite(D8, ON);
	}

	//REG_PIOC_SODR=((VL & 0x01)<<5) | ((VL & 0x02)<<3) | ((VL & 0x04)<<1) | ((VL & 0x08)>>1) | ((VL & 0x10)>>3);
	if ((cl & 0x01)) {
		gpioWrite(D0, ON);
	}
	if ((cl & 0x02)) {
		gpioWrite(D1, ON);
	}
	if ((cl & 0x04)) {
		gpioWrite(D2, ON);
	}
	if ((cl & 0x08)) {
		gpioWrite(D3, ON);
	}
	if ((cl & 0x010)) {
		gpioWrite(D4, ON);
	}
	//REG_PIOD_SODR=((VH & 0x78)>>3) | ((VH & 0x80)>>1) | ((VL & 0x20)<<5) | ((VL & 0x80)<<2);
	if ((cl & 0x020)) {
		gpioWrite(D5, ON);
	}
	if ((cl & 0x080)) {
		gpioWrite(D7, ON);
	}
	if ((ch & 0x08)) {
		gpioWrite(D11, ON);
	}
	if ((ch & 0x010)) {
		gpioWrite(D12, ON);
	}
	if ((ch & 0x020)) {
		gpioWrite(D13, ON);
	}
	if ((ch & 0x04)) {
		gpioWrite(D14, ON);
	}
	if ((ch & 0x08)) {
		gpioWrite(D15, ON);
	}

	blocks = pix / 16;
	for (int i = 0; i < blocks; i++) {
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		// delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		// delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		// delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		// delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		// delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
		//pulse_low(P_WR, B_WR);
		//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, OFF);
		//delayMicroseconds(1); //retardo minimo de 12nseg
		//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
		gpioWrite(WR, ON);
	}
	if ((pix % 16) != 0)
		for (int i = 0; i < (pix % 16) + 1; i++) {
			//pulse_low(P_WR, B_WR);
			//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
			gpioWrite(WR, OFF);
			//delayMicroseconds(1); //retardo minimo de 12nseg
			//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
			gpioWrite(WR, ON);

		}
}

void setXY(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	if (orient == LANDSCAPE) {
		swap(uint32_t, x1, y1);
		swap(uint32_t, x2, y2)
		y1=disp_y_size-y1;
		y2 = disp_y_size - y2;
		swap(uint32_t, y1, y2)
	}
	swap(uint32_t, x1, y1);
	swap(uint32_t, x2, y2);
	LCD_Write_COM(0x2a);		//habilita las direccion de las columnas
	LCD_Write_DATA(x1 >> 8);
	LCD_Write_DATA(x1);
	LCD_Write_DATA(x2 >> 8);
	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b);		//setea la direccion de pagina, filas
	LCD_Write_DATA(y1 >> 8);
	LCD_Write_DATA(y1);
	LCD_Write_DATA(y2 >> 8);
	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c);		//inicio de escritura de memoria
							/*Transfer image information from the host processor interface
							to the SSD1963 starting at the location provided by
							set_column_address and set_page_address*/
}

//para establecer el tipo de letra
void setFont(uint8_t* font) {
cfont.font = font;
cfont.x_size = fontbyte(0);
cfont.y_size = fontbyte(1);
cfont.offset = fontbyte(2);
cfont.numchars = fontbyte(3);
}

#endif /* LCDFCOMANDOS_H_ */
