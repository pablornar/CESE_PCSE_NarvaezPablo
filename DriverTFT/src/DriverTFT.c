/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include "sapi.h"        	// <= Biblioteca sAPI
#include "inicio.h"			// Biblioteca de inicio del micro.
#include "displaygraf.h"	//libreria general del display
#include "DriverTFT.h"         // = Su propia cabecera

//+++++++++++++++++++++variables de display
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Dingbats1_XL[];
short ResH = 800;
short ResV = 480;

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();
	inicio();		//inicializacion

	/*configura lcd y selecciona el modelo*/
	Conflcd(CTE70, 38, 39, 40, 41);	//configura RS, WR, CS y rest pero no se usan por ahora vienen por defecto
	inicioLCD(LANDSCAPE); //inicializa LCD
	setFont(BigFont); //configura letra pantalla
	clrScr();  //borra lcd

	/* Retardo bloqueante durante 100ms */

	delay(1000);

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {
		setColor(VGA_GREEN);
		drawVLine(100, 100, 200);
		delay(500);
		drawHLine(100, 100, 400);
		delay(500);
		setColor(VGA_WHITE);
		drawLine(200, 200, 400, 200);
		delay(500);
		setColor(VGA_RED);
		drawPixel(380, 470);
		delay(500);
		setFont(BigFont);
		printCharAscii(97, 300, 350);
		delay(500);
		clrScr();
		delay(500);

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
