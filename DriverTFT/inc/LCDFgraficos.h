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

//Para dibujar una rectangulo
void drawRectangulo(int x1, int y1, int x2, int y2){
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

//Para dibujar una rectangulo con las esquinas redondeadas.
void drawRoundRect(int x1, int y1, int x2, int y2){
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

//Para dibujar una rectangulo relleno NO FUNCION BIEN
void drawfillRect(int x1, int y1, int x2, int y2){
	long pix;
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if (display_transfer_mode==16)
	{
		//cbi(P_CS, B_CS);
		gpioWrite(CS, OFF);
		setXY(x1, y1, x2, y2);
		//sbi(P_RS, B_RS);
		gpioWrite(CS, ON);
		pix=(((x2-x1)+1)*((y2-y1)+1));
		_fast_fill_16(fch,fcl,pix);
		//sbi(P_CS, B_CS);
		gpioWrite(CS, ON);
	}
	else
	{
		if (orient==PORTRAIT)
		{
			for (int i=0; i<((y2-y1)/2)+1; i++)
			{
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
		else
		{
			for (int i=0; i<((x2-x1)/2)+1; i++)
			{
				drawVLine(x1+i, y1, y2-y1);
				drawVLine(x2-i, y1, y2-y1);
			}
		}
	}
}

//Para dibujar un circulo
void drawCircle(int x, int y, int radius){
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;

	//cbi(P_CS, B_CS);
	gpioWrite(CS, OFF);
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATAb(fch,fcl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATAb(fch,fcl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATAb(fch,fcl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATAb(fch,fcl);

	while(x1 < y1)
	{
		if(f >= 0)
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATAb(fch,fcl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATAb(fch,fcl);
	}
	//sbi(P_CS, B_CS);
	gpioWrite(CS, ON);
	clrXY();
}

//Para dibujar un circulo relleno
void drawfillCircle(int x, int y, int radius){
	for(int y1=-radius; y1<=0; y1++)
		for(int x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius)
			{
				drawHLine(x+x1, y+y1, 2*(-x1));
				drawHLine(x+x1, y-y1, 2*(-x1));
				break;
			}
}

void rotateChar(uint8_t c, int x, int y, int pos, int deg){
	uint8_t i,j,ch;
	uint32_t temp;
	int newx,newy;
	double radian;
	radian=deg*0.0175;

	//cbi(P_CS, B_CS);
	gpioWrite(CS, OFF);

	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++)
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch=pgm_read_byte(&cfont.font[temp+zz]);
			for(i=0;i<8;i++)
			{
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);

				if((ch&(1<<(7-i)))!=0)
				{
					setPixel((fch<<8)|fcl);
				}
				else
				{
					if (!_transparent)
						setPixel((bch<<8)|bcl);
				}
			}
		}
		temp+=(cfont.x_size/8);
	}
	//sbi(P_CS, B_CS);
	gpioWrite(CS, ON);

	clrXY();
}

//para imprimir un string en x,y y rotarlo
void print(char *st, int x, int y, int deg){
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printCharAscii(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

//para imprimir un numero entero
void printNumI(long num, int x, int y, int length, char filler){
	char buf[25];
	char st[27];
	bool neg=false;
	int c=0, f=0;

	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}

		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;

		if (neg)
		{
			st[0]=45;
		}

		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}

	print(st,x,y,0);
}

//para imprimir un numero con coma
void printNumF(double num, uint8_t dec, int x, int y, char divider, int length, char filler){
	char st[27];
	bool neg=false;

	if (dec<1)
		dec=1;
	else if (dec>5)
		dec=5;

	if (num<0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.')
	{
		for (int i=0; i<sizeof(st); i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
			for (int i=1; i<sizeof(st); i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
			for (int i=0; i<sizeof(st); i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y,0);
}

void _convert_float(char *buf, double num, int width, uint8_t prec)
{
	char format[10];
	char formato[10]="%d.%0";
	char formatob[10]="u";
	int decimales;
	int i;

	sprintf(formatob,"%d",prec);
	i=0;
	decimales=1;
	while(i!=prec){
		decimales=(10*decimales);
		i++;
	}
	strcat (formatob, "u");
	strcat (formato, formatob);
	sprintf(buf,(formato), (int) num, (int) ((num - (int) num ) * decimales) );

}



#endif /* LCDFGRAFICOS_H_ */
