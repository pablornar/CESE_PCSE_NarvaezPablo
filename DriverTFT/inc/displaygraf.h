/*
 * IncFile1.h
 *
 * Created: 24/02/2021 16:54:21
 *  Author: Pablo
 */
#include <LCDFonts.h>	//agrega las librerias de fonts

#ifndef	DISPLAYGRAF_H_
#define DISPLAYGRAF_H_

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998
//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF

struct _current_font {
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

struct _current_font cfont;

#define swap(type, i, j) {type t = i; i = j; j = t;}
#define fontbyte(x) cfont.font[x]
#define pgm_read_word(data) *data
#define pgm_read_byte(data) *data
#define bitmapdatatype unsigned short*

int mode = 16;
char VH;
char VL;
uint8_t fch, fcl, bch, bcl;
uint8_t orient = 1;
long disp_x_size, disp_y_size;
int display_model, display_transfer_mode, display_serial_mode;
long *P_RS, *P_WR, *P_CS, *P_REST, *P_SDA, *P_SCL, *P_ALE;
long B_RS, B_WR, B_CS, B_REST, B_SDA, B_SCL, B_ALE;
uint8_t __p1, __p2, __p3, __p4, __p5;

bool _transparent;
uint8_t LANDSCAPE = 1;
uint8_t PORTRAIT = 0;

uint8_t model = 20;

int SER;
int CTE70 = 20;
int SERIAL_4PIN = 4;
int SERIAL_5PIN = 5;
int LATCHED_16 = 17;
int NOTINUSE = 255;

#include <LCDFconfiguracion.h>  //agrega la libreria de configuracion de lcd
#include <LCDFcomandos.h>  //agrega la libreria de comandos.
#include <LCDFinicio.h>  //agrega la libreria de inicializacion de lcd
#include <LCDFgraficos.h>  //agrega la libreria de graficos

#endif /* INCFILE1_H_ */
