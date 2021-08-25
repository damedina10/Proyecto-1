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
#include <driver/adc.h>
//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------
//Botón
#define B1 1

//Sensor
#define sensor 25

//LEDs del RGB
#define Ledrojo 27
#define Ledverde 14
#define Ledazul 12


//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------
int lectura = 0;
int medicion = 0;

//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------
void configurarboton(void);
void configurarsensor(void);
void configurarlrojo(void);
void configurarlverde(void);

//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------

//Interrupción del botón que permite la medición de temperatura
void IRAM_ATTR ISRboton(){
  lectura = adc2_get_raw(ADC2_CHANNEL_8);
  medicion = lectura * 100;
}


//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  //Botón
  pinMode(B1,INPUT_PULLUP);

  //Sensor
  pinMode(sensor,INPUT_PULLUP);

  //LED RGB
  pinMode(Ledrojo, OUTPUT);
  pinMode(Ledverde, OUTPUT);
  pinMode(Ledazul, OUTPUT);

  //Se llama a la función para configurar el boton
  configurarboton();
  //Se llama a la función para configurar el sensor
  configurarsensor();
  //Se llama a la función para configurar la señal PMW del LED rojo
  configurarlrojo();
  //Se llama a la función para configurar la señal PMW del LED verde
  configurarlverde();
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

//-------------------------------------------------------------------------------------------------
// función para configurar el ADC del sensor 
//-------------------------------------------------------------------------------------------------
void configurarsensor(void){
  //Configuramos el ancho de bits del ADC
  adc2_config_width(ADC_WIDTH_BIT_12);

  //Configuramos el canal y la atenuación
  adc2_config_channel_atten(ADC2_CHANNEL_8,ADC_ATTEN_DB_0);
  
}

//-------------------------------------------------------------------------------------------------
// función para configurar la señal PMW del led rojo
//-------------------------------------------------------------------------------------------------
void configurarlrojo(void){
  //Se establece que la frecuencia de la señal PMW sea 60Hz
  ledcSetup(1,60,8);
  //Adjuntamos la señal PMW a un pin
  ledcAttachPin(Ledrojo, 1);
}
//-------------------------------------------------------------------------------------------------
// función para configurar la señal PMW del led verde
//-------------------------------------------------------------------------------------------------
void configurarlverde(void){
  //Se establece que la frecuencia de la señal PMW sea 60Hz
  ledcSetup(2,60,8);
  //Adjuntamos la señal PMW a un pin
  ledcAttachPin(Ledverde, 2);
}