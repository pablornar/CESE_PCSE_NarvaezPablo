// Bibliotecas
#include "sapi.h"        // <= Biblioteca sAPI
#include "inicio.h"

void inicio() {
	/* Inicializar UART_USB a 115200 baudios */
	uartConfig(UART_USB, 230400);
	uartConfig(UART_232, 230400);
	/* Inicializar AnalogIO */
	adcConfig(ADC_ENABLE); /* ADC */
	/***configuracion de pines*/
	D0 = GPIO0;
	D1 = GPIO1;
	D2 = GPIO2;
	D3 = GPIO3;
	D4 = GPIO4;
	D5 = GPIO5;
	D6 = GPIO6;
	D7 = GPIO7;
	D8 = GPIO8;
	D9 = LCDEN;
	D10 = LCD1;
	D11 = LCD2;
	D12 = LCD3;
	D13 = LCD4;
	D14 = LCDRS;
	D15 = T_COL0;
	RS = T_FIL2;
	WR = T_FIL3;
	CS = T_FIL0;
	REST = T_COL1;
	/***Inicializacion de pines*/
	gpioInit(D0, GPIO_OUTPUT);
	gpioInit(D1, GPIO_OUTPUT);
	gpioInit(D2, GPIO_OUTPUT);
	gpioInit(D3, GPIO_OUTPUT);
	gpioInit(D4, GPIO_OUTPUT);
	gpioInit(D5, GPIO_OUTPUT);
	gpioInit(D6, GPIO_OUTPUT);
	gpioInit(D7, GPIO_OUTPUT);
	gpioInit(D8, GPIO_OUTPUT);
	gpioInit(D9, GPIO_OUTPUT);
	gpioInit(D10, GPIO_OUTPUT);
	gpioInit(D11, GPIO_OUTPUT);
	gpioInit(D12, GPIO_OUTPUT);
	gpioInit(D13, GPIO_OUTPUT);
	gpioInit(D14, GPIO_OUTPUT);
	gpioInit(D15, GPIO_OUTPUT);
	gpioInit(RS, GPIO_OUTPUT);
	gpioInit(WR, GPIO_OUTPUT);
	gpioInit(CS, GPIO_OUTPUT);
	gpioInit(REST, GPIO_OUTPUT);
	//gpioMap_t pin

	/*Inicializacion de variables  */

}
