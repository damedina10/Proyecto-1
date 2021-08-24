//-------------------------------------------------------------------------------------------------
/*
 * Universidad del Valle de Guatemala
 * BE3015 - Electrónica Digital 2
 * Proyecto # 1
 * Sensor de temperatura
 * Nombre: Diego Andrés Medina Mencos
 * Carné: 19697
 */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Librerías
//-------------------------------------------------------------------------------------------------
#include <Arduino.h>

//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------
void configurarboton(void);


//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  

}

//-------------------------------------------------------------------------------------------------
// Loop principal
//-------------------------------------------------------------------------------------------------
void loop() {
  
  
}

//-------------------------------------------------------------------------------------------------
// función para configurar la interrupción del botón 
//-------------------------------------------------------------------------------------------------
void configurarboton(void){
  //Adjuntamos la interrupción a un pin
  attachInterrupt(B1,ISRboton, HIGH);
  
}