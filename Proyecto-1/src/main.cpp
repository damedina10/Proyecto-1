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
//Botón
#define B1 1

//Sensor
#define sensor 34

//LEDs del RGB
#define Ledrojo 27
#define Ledverde 14
#define Ledazul 12

//Servo
#define servo 5

//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------
//Variables para la lectura del sensor
float lectura = 0;

//Variables para el filtro de Kalman
float varVolt = 1.9615;
float varProcess = 1e-9;
float Pact = 0.0;
float KG = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xest = 0.0;
float adcFiltradoKalman = 0.0;

//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------
void configurarboton(void);
void filtrosensor(void);
void configurarlrojo(void);
void configurarlverde(void);
void configurarlazul(void);
void configurarservo(void);

//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------

//Interrupción del botón que permite la medición de temperatura
void IRAM_ATTR ISRboton(){
  lectura = analogRead(sensor);
  Serial.println(lectura);
}


//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  //Botón
  pinMode(B1,INPUT_PULLUP);

  //Sensor
  //pinMode(sensor,INPUT_PULLUP);

  //LED RGB
  pinMode(Ledrojo, OUTPUT);
  pinMode(Ledverde, OUTPUT);
  pinMode(Ledazul, OUTPUT);

  //Servo
  pinMode(servo,OUTPUT);

  //Se llama a la función para configurar el boton
  configurarboton();
  
  //Se llama a la función para configurar el sensor
  filtrosensor();
  //Se llama a la función para configurar la señal PMW del LED rojo
  configurarlrojo();
  //Se llama a la función para configurar la señal PMW del LED verde
  configurarlverde();
  //Se llama a la función para configurar la señal PMW del LED azul
  configurarlazul();
  //Se llama a la función para configurar la señal PMW del servo
  configurarservo();
  
}

//-------------------------------------------------------------------------------------------------
// Loop principal
//-------------------------------------------------------------------------------------------------
void loop() {
  lectura = analogRead(sensor);
  delay (100);
  Serial.println(lectura);
  
  if(lectura < 37.1){
    //Cuando la temperatura sea menor o igual a 37° se enciende el LED verde 
    ledcWrite(1,0); //El LED rojo se mantiene apagado
    ledcWrite(3,0); //El LED azul se mantiene apagado
    //Dutycycle = 75
    ledcWrite(2,191);
    //El servo apunta hacia el LED verde
    ledcWrite(0,17);
  }
  if(37.0 < lectura < 37.6){
    //Cuando la temperatura sea mayor a 37° y menor o igual a 37.5°
    //se enciende el LED azul 
    ledcWrite(1,0); //El LED rojo se mantiene apagado
    ledcWrite(2,0); //El LED verde se mantiene apagado
    //Dutycycle = 75
    ledcWrite(3,191);
    //El servo apunta hacia el LED azul
    ledcWrite(0,22);
  }
  if(lectura > 37.5){
    //Cuando la temperatura sea mayor a 37.5° se enciende el LED rojo  
    ledcWrite(3,0); //El LED azul se mantiene apagado
    ledcWrite(2,0); //El LED verde se mantiene apagado
    //Dutycycle = 75
    ledcWrite(1,191);
    //El servo apunta hacia el LED rojo
    ledcWrite(0,27);
  }
  
}

//-------------------------------------------------------------------------------------------------
// función para configurar la interrupción del botón 
//-------------------------------------------------------------------------------------------------
void configurarboton(void){
  //Adjuntamos la interrupción a un pin
  attachInterrupt(B1,ISRboton, HIGH);
  
}

//-------------------------------------------------------------------------------------------------
// función para el filtro del sensor 
//-------------------------------------------------------------------------------------------------
void filtrosensor(void){
  
  
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
//-------------------------------------------------------------------------------------------------
// función para configurar la señal PMW del led azul
//-------------------------------------------------------------------------------------------------
void configurarlazul(void){
  //Se establece que la frecuencia de la señal PMW sea 60Hz
  ledcSetup(3,60,8);
  //Adjuntamos la señal PMW a un pin
  ledcAttachPin(Ledazul, 3);
}

//-------------------------------------------------------------------------------------------------
// función para la señal PMW del servo
//-------------------------------------------------------------------------------------------------
void configurarservo(void){
  //frec = 1/20ms = 50
  ledcSetup(0,50,8);
  //Adjuntamos la señal PMW a un pin
  ledcAttachPin(servo, 0);
}
