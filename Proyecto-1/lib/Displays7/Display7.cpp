#include "Display7.h"

//función para configurar Display de 7 segmentos
void configurardisplay(uint8_t A, uint8_t B,uint8_t C,uint8_t D,uint8_t E,uint8_t F,uint8_t G,uint8_t DP){
    //Establecemos que los pines son salidas
    pinMode(A,OUTPUT);
    pinMode(B,OUTPUT);
    pinMode(C,OUTPUT);
    pinMode(D,OUTPUT);
    pinMode(E,OUTPUT);
    pinMode(F,OUTPUT);
    pinMode(G,OUTPUT);
    pinMode(DP,OUTPUT);

    //Establecemos que todas las salidas van a estar en 0 inicialmente
    digitalWrite(A,1);
    digitalWrite(B,1);
    digitalWrite(C,1);
    digitalWrite(D,1);
    digitalWrite(E,1);
    digitalWrite(F,1);
    digitalWrite(G,1);
    digitalWrite(DP,1);
}

//Función para desplegar el digito en el display
void desplegardigito(uint8_t digito){

}

//Función para desplegar el punto decimal en el segundo display 
void desplegarpunto(boolean punto){

}