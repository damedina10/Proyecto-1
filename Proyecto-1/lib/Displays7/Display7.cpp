#include "Display7.h"

//Variables globales
uint8_t pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP;

//función para configurar Display de 7 segmentos
void configurardisplay(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP){
    pinA = A;
    pinB = B;
    pinC = C;
    pinD = D;
    pinE = E;
    pinF = F;
    pinG = G;
    pinDP = DP;

    //Establecemos que los pines son salidas
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(DP, OUTPUT);

    //Establecemos que todas las salidas van a estar en 0 inicialmente
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(DP, 1);
}

//Función para desplegar el digito en el display
void desplegardigito(uint8_t digito){
    switch (digito)
    {
    case 0:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 0);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 1);
        break;
    case 1:
        digitalWrite(pinA, 1);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 1);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 1);
        digitalWrite(pinG, 1);
        break;
    case 2:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 1);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 0);
        digitalWrite(pinF, 1);
        digitalWrite(pinG, 0);
        break;
    case 3:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 1);
        digitalWrite(pinG, 0);
        break;
    case 4:
        digitalWrite(pinA, 1);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 1);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 0);
        break;
    case 5:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 1);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 0);
        break;
    case 6:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 1);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 0);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 0);
        break;
    case 7:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 1);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 1);
        digitalWrite(pinG, 1);
        break;
    case 8:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 0);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 0);
        break;
    case 9:
        digitalWrite(pinA, 0);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 0);
        break;
    default:
        break;
    }
}

//Función para desplegar el punto decimal en el segundo display
void desplegarpunto(boolean punto){
    if (punto == 1){
        digitalWrite(pinDP, 0);
    }
    else{
        digitalWrite(pinDP, 1);
    }
}