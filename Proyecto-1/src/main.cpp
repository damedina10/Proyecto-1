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
#include "AdafruitIO_WiFi.h"
#include "Display7.h"

//-------------------------------------------------------------------------------------------------
// Configuración de Adafruit IO
//-------------------------------------------------------------------------------------------------
//KEY
#define IO_USERNAME "diegomed10"
#define IO_KEY "aio_yHBt60BiPm4zFPanX5d01lHzwO4J"

// WIFI
#define WIFI_SSID "TIGO-656A"
#define WIFI_PASS "4D9697500333"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------
//Botón
#define B1 15

//Sensor
#define sensor 34

//LEDs del RGB
#define Ledrojo 23
#define Ledverde 2
#define Ledazul 4

//Servo
#define servo 5

//Displays de 7 segmentos
#define sA 25
#define sB 26
#define sC 27
#define sD 13
#define sE 12
#define sF 33
#define sG 32
#define sDP 14

//Transistores para los displays
#define display1 21
#define display2 19
#define display3 18 

//Timer 
#define prescaler 80

//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------

//Variables para el botón
int estadoBoton = 0;
//Variables para la lectura del sensor
int lectura = 0;
float voltaje = 0.0;
float temperatura = 0.0;
float temp = 0.0;

//Variables para el filtro EMA
double adcFiltradoEMA = 0; // S(0) = Y(0)
double alpha = 0.05;       // Factor de suavizado (0-1)

//Adafruit IO
int count = 0;
AdafruitIO_Feed *temperaturaFeed = io.feed("temperatura");

//Instanciamos el timer
hw_timer_t * timer = NULL;
//Contador del timer
int contadorT = 0;

//Variables para los displays de 7 segmentos
int decenas = 0;
int unidades = 0;
int decimal = 0;

//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------
void configurarboton(void);
void filtrosensor(void);
void configurarlrojo(void);
void configurarlverde(void);
void configurarlazul(void);
void configurarservo(void);
void configurartimer(void);

//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------

//Interrupción del botón que permite la medición de temperatura
void IRAM_ATTR ISRboton(){
  estadoBoton = 1;
}

//Interrupción del temporizador
void IRAM_ATTR ISRTimer(){
  contadorT ++; 
  if(contadorT > 2){
    contadorT = 0;
  } 
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
  //Se llama a la función para configurar la señal PMW del LED rojo
  configurarlrojo();
  //Se llama a la función para configurar la señal PMW del LED verde
  configurarlverde();
  //Se llama a la función para configurar la señal PMW del LED azul
  configurarlazul();
  //Se llama a la función para configurar la señal PMW del servo
  configurarservo();
  //Se llama a la función para configurar el timer
  configurartimer();
  
  //Adafruit IO
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  //Configuración de los displays de 7 segmentos
  configurardisplay(sA, sB, sC, sD, sE, sF, sG, sDP);

  //Transistores para los displays
  pinMode(display1,OUTPUT);
  pinMode(display2,OUTPUT);
  pinMode(display3,OUTPUT);

  digitalWrite(display1,0);
  digitalWrite(display2,0);
  digitalWrite(display3,0);
}

//-------------------------------------------------------------------------------------------------
// Loop principal
//-------------------------------------------------------------------------------------------------
void loop() {
  if(estadoBoton == 1){
    estadoBoton = 0;
    lectura = analogReadMilliVolts(sensor);
    adcFiltradoEMA = (alpha * lectura) + ((1.0 - alpha) * adcFiltradoEMA);
    temperatura = adcFiltradoEMA/10.0;

    //Obtención de las decenas
    decenas = temperatura / 10;

    //Obtención de las unidades
    unidades = temperatura - (decenas * 10);

    //Obtención de los decimales
    decimal = ((temperatura*10)-(decenas*100)-(unidades*10));

    //Semáforo de temperatura
    if(temperatura <= 20.0){
      //Cuando la temperatura sea menor o igual a 37° se enciende el LED verde 
      ledcWrite(1,0); //El LED rojo se mantiene apagado
      ledcWrite(3,0); //El LED azul se mantiene apagado
      //Dutycycle = 75
      ledcWrite(2,191);
      //El servo apunta hacia el LED verde
      ledcWrite(0,17);
    }
    
    if(20 <= temperatura && temperatura <= 40){
      //Cuando la temperatura sea mayor a 37° y menor o igual a 37.5°
      //se enciende el LED azul 
      ledcWrite(1,0); //El LED rojo se mantiene apagado
      ledcWrite(2,0); //El LED verde se mantiene apagado
      //Dutycycle = 75
      ledcWrite(3,191);
      //El servo apunta hacia el LED azul
      ledcWrite(0,22);
    }
    
    if(temperatura > 40){
      //Cuando la temperatura sea mayor a 37.5° se enciende el LED rojo  
      ledcWrite(3,0); //El LED azul se mantiene apagado
      ledcWrite(2,0); //El LED verde se mantiene apagado
      //Dutycycle = 75
      ledcWrite(1,191);
      //El servo apunta hacia el LED rojo
      ledcWrite(0,27);
    }

    //Segmento de Adafruit IO
    io.run();

    // save count to the 'counter' feed on Adafruit IO
    Serial.print("sending temperatura-> ");
    Serial.println(temperatura);
    temperaturaFeed->save(temperatura);
  }

  //Despliegue de la temperatura en los displays de 7 segmentos
  if(contadorT == 0){
    //Se enciende el display de las decenas
    digitalWrite(display1,1);
    digitalWrite(display2,0);
    digitalWrite(display3,0);
    //Llamamos a la función desplegardigito para que muestre las decenas
    desplegardigito(decenas);
    //Llamamos a la función del punto para decirle que no queremos el punto
    desplegarpunto(0);
    
  }
  if(contadorT == 1){
    //Se enciende el display de las unidades
    digitalWrite(display1,0);
    digitalWrite(display2,1);
    digitalWrite(display3,0);
    //Llamamos a la función desplegardigito para que muestre las unidades
    desplegardigito(unidades);
    //Llamamos a la función del punto para decirle que queremos el punto
    desplegarpunto(1);
    
  }
  if(contadorT == 2){
    //Se enciende el display de los decimales
    digitalWrite(display1,0);
    digitalWrite(display2,0);
    digitalWrite(display3,1);
    //Llamamos a la función desplegardigito para que muestre el decimal
    desplegardigito(decimal);
    //Llamamos a la función del punto para decirle que no queremos el punto
    desplegarpunto(0);
    delay(5);
  }

}

//-------------------------------------------------------------------------------------------------
// función para configurar la interrupción del botón 
//-------------------------------------------------------------------------------------------------
void configurarboton(void){
  //Adjuntamos la interrupción a un pin
  attachInterrupt(B1,ISRboton, RISING);
  
}

//-------------------------------------------------------------------------------------------------
// función para el filtro del sensor 
//-------------------------------------------------------------------------------------------------
void filtrosensor(void){
  lectura = analogReadMilliVolts(sensor);
  adcFiltradoEMA = (alpha * lectura) + ((1.0 - alpha) * adcFiltradoEMA);
  temperatura = adcFiltradoEMA/10.0;
  Serial.println(temperatura);
  
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

//-------------------------------------------------------------------------------------------------
// Función para configurar timer
//-------------------------------------------------------------------------------------------------
void configurartimer(void){
  //Fosc/prescaler = 80,000,000/80 = 1,000,000
  //Tosc = 1/Fosc = 1 us
  //Seleccionamos el timer
  timer = timerBegin(0, prescaler, true);
  
  //Asignar el handler de la interrupcion
  timerAttachInterrupt(timer, &ISRTimer, true);

  //Programar Alarma
  //Frecuencia = 5,000
  timerAlarmWrite(timer,5000,true);

  //Iniciamos la alarma
   timerAlarmEnable(timer); 
}