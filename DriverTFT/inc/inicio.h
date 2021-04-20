/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _INICIO_H_
#define _INICIO_H_

/*==================[inclusiones]============================================*/

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
uint8_t D0;
uint8_t D1;
uint8_t D2;
uint8_t D3;
uint8_t D4;
uint8_t D5;
uint8_t D6;
uint8_t D7;
uint8_t D8;
uint8_t D9;
uint8_t D10;
uint8_t D11;
uint8_t D12;
uint8_t D13;
uint8_t D14;
uint8_t D15;
uint8_t RS;
uint8_t WR;
uint8_t CS;
uint8_t REST;

/*==================[declaraciones de funciones externas]====================*/
void inicio(void);
//*******funciones de Libreria Inicio
void extern inicioLCD(uint8_t orientation);
void extern initlcd(void);

//*******funciones de Libreria Comandos
void extern clrScr(void);
void extern clrXY(void);
void extern _fast_fill_16(int ch, int cl, long pix);
void extern setXY(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void extern setXYa(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void extern setFont(uint8_t* font);

//*******funciones de Libreria Configuracion
void extern Conflcd(int model, int RS, int WR, int CS, int RST);
void extern _set_direction_registers(uint8_t mode);
void extern LCD_Writ_Bus(char VH, char VL, uint8_t mode);
void extern LCD_Write_DATA(char VL);
void extern LCD_Write_DATAb(char VH, char VL);
void extern LCD_Write_COM(char VL);

//*******funciones de Libreria graficos
void extern setColorb(uint8_t r, uint8_t g, uint8_t b);
void extern setColor(int color);
void extern setBackColorb(uint8_t r, uint8_t g, uint8_t b);
void extern setBackColor(uint32_t color);
void extern drawHLine(int x, int y, int l);
void extern drawVLine(int x, int y, int l);
void extern drawLine(int x1, int y1, int x2, int y2);
void extern setPixel(int color);
void extern drawPixel(int x, int y);
void extern printCharAscii(uint8_t c, int x, int y);
void extern rotateChar(uint8_t c, int x, int y, int pos, int deg);
void extern print(char *st, int x, int y, int deg);
void extern printNumI(long num, int x, int y, int length, char filler);
void extern printNumF(double num, uint8_t dec, int x, int y, char divider, int length, char filler);
void _convert_float(char *buf, double num, int width, uint8_t prec);

void extern drawRectangulo(int x1, int y1, int x2, int y2);
void extern drawRoundRect(int x1, int y1, int x2, int y2);
void extern drawfillRect(int x1, int y1, int x2, int y2);
void extern drawCircle(int x, int y, int radius);
void extern drawfillCircle(int x, int y, int radius);

/*==================[end of file]============================================*/
#endif
