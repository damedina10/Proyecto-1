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
int lectura = 0;
float voltaje = 0;
float temperatura = 0;

//Variables para el filtro EMA
double adcFiltradoEMA = 0; // S(0) = Y(0)
double alpha = 0.09;       // Factor de suavizado (0-1)

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
  filtrosensor();
}


//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  //Botón
  pinMode(B1,INPUT_PULLUP);

  //LED RGB
  pinMode(Ledrojo, OUTPUT);
  pinMode(Ledverde, OUTPUT);
  pinMode(Ledazul, OUTPUT);


  //Servo
  pinMode(servo,OUTPUT);

  //Se llama a la función para configurar el boton
  configurarboton();
  
  //Se llama a la función para configurar el sensor
  //filtrosensor();
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

  if(temperatura <= 37.0){
    //Cuando la temperatura sea menor o igual a 37° se enciende el LED verde 
    ledcWrite(1,0); //El LED rojo se mantiene apagado
    ledcWrite(3,0); //El LED azul se mantiene apagado
    //Dutycycle = 75
    ledcWrite(2,191);
    //El servo apunta hacia el LED verde
    ledcWrite(0,17);
  }
  if(37.1 <= temperatura && temperatura <= 37.5){
    //Cuando la temperatura sea mayor a 37° y menor o igual a 37.5°
    //se enciende el LED azul 
    ledcWrite(1,0); //El LED rojo se mantiene apagado
    ledcWrite(2,0); //El LED verde se mantiene apagado
    //Dutycycle = 75
    ledcWrite(3,191);
    //El servo apunta hacia el LED azul
    ledcWrite(0,22);
  }
  if(temperatura > 37.5){
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
  lectura = analogRead(sensor);
  adcFiltradoEMA = (alpha * lectura) + ((1.0 - alpha) * adcFiltradoEMA);
  voltaje = adcFiltradoEMA*3300.0/4095.0;
  temperatura = voltaje/10.0;
  Serial.println(temperatura);
  delay(1000);
  
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
