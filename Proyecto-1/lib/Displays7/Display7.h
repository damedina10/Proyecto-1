#ifndef __DISPLAY7_H__
#define __DISPLAY7_H__

#include <Arduino.h>

//Variables globales
extern uint8_t pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP;

//función para configurar Display de 7 segmentos
void configurardisplay(uint8_t A, uint8_t B,uint8_t C,uint8_t D,uint8_t E,uint8_t F,uint8_t G,uint8_t DP);

//Función para desplegar el digito en el display
void desplegardigito(uint8_t digito);

//Función para desplegar el punto decimal en el segundo display 
void desplegarpunto(boolean punto);

#endif // __DISPLAY7_H__