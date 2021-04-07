/*
 * LCDFinicio.h
 *
 * Created: 27/02/2021 8:21:36
 *  Author: Pablo
 */

#ifndef LCDFINICIO_H_
#define LCDFINICIO_H_

void inicioLCD(uint8_t orientation) {
	orient = orientation;
	if (display_transfer_mode != 1)
		_set_direction_registers (display_transfer_mode);

	//sbi(P_RST, B_RST);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111110111111111) | 0b00000000000000000000001000000000; //PC9-RST
	gpioWrite(REST, ON);
	delay(1);
	//cbi(P_RST, B_RST);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111110111111111) | 0b00000000000000000000001000000000; //PC9-RST
	gpioWrite(REST, OFF);
	delay(1);
	//sbi(P_RST, B_RST);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111110111111111) | 0b00000000000000000000001000000000; //PC9-RST
	gpioWrite(REST, ON);
	delay(1);

	//cbi(P_CS, B_CS);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, OFF);

	initlcd();

	//sbi (P_CS, B_CS);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111011111111) | 0b00000000000000000000000100000000; //PC8-CS
	gpioWrite(CS, ON);

	setColorb(255, 255, 255);
	setBackColorb(0, 0, 0);
	cfont.font = 0;
	_transparent = false;
}

void initlcd(void) {
	LCD_Write_COM(0xE2);    //PLL multiplier, set PLL clock to 120M
	LCD_Write_DATA(0x23);     //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_Write_DATA(0x02);   //frecuencia pll a 120mhz
	LCD_Write_DATA(0x04);
	LCD_Write_COM(0xE0);    // PLL enable
	LCD_Write_DATA(0x01);
	delay(1);
	//delay(10);
	LCD_Write_COM(0xE0);
	LCD_Write_DATA(0x03);
	delay(1);
	//delay_us(100);
	LCD_Write_COM(0x01);    // software reset
	delay(5);
	//delay_us(500);
	LCD_Write_COM(0xE6);    //PLL setting for PCLK, depends on resolution
	LCD_Write_DATA(0x04);   //para 3.43mhz de clock
	LCD_Write_DATA(0x93);
	LCD_Write_DATA(0xE0);

	LCD_Write_COM(0xB0);    //LCD SPECIFICATION
	LCD_Write_DATA(0x00); // 0x24
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x03);   //Set HDP 799
	LCD_Write_DATA(0x1F);
	LCD_Write_DATA(0x01);   //Set VDP 479
	LCD_Write_DATA(0xDF);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(0xB4);    //HSYNC
	LCD_Write_DATA(0x03);   //Set HT  928
	LCD_Write_DATA(0xA0);
	LCD_Write_DATA(0x00);   //Set HPS 46
	LCD_Write_DATA(0x2E);
	LCD_Write_DATA(0x30);   //Set HPW 48
	LCD_Write_DATA(0x00);   //Set LPS 15
	LCD_Write_DATA(0x0F);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(0xB6);    //VSYNC
	LCD_Write_DATA(0x02);   //Set VT  525
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x00);   //Set VPS 16
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x10);   //Set VPW 16
	LCD_Write_DATA(0x00);   //Set FPS 8
	LCD_Write_DATA(0x08);

	LCD_Write_COM(0xBA);
	LCD_Write_DATA(0x05);   //GPIO[3:0] out 1

	LCD_Write_COM(0xB8);
	LCD_Write_DATA(0x07);     //GPIO3=input, GPIO[2:0]=output
	LCD_Write_DATA(0x01);   //GPIO0 normal

	LCD_Write_COM(0x36);    //rotation
	LCD_Write_DATA(0x22);   // -- Set to 0x21 to rotate 180 degrees

	LCD_Write_COM(0xF0);    //pixel data interface
	LCD_Write_DATA(0x03);

	delay(1);
	//delay_us(100);

	setXY(0, 0, 799, 479);
	LCD_Write_COM(0x29);    //display on

	LCD_Write_COM(0xBE);    //set PWM for B/L
	LCD_Write_DATA(0x06);
	LCD_Write_DATA(0xF0);
	LCD_Write_DATA(0x01);
	LCD_Write_DATA(0xF0);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);

	LCD_Write_COM(0xD0);
	LCD_Write_DATA(0x0D);

	LCD_Write_COM(0x2C);

}

#endif /* LCDFINICIO_H_ */
