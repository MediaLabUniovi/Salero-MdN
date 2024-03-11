// Inclusión de librerías -----------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>                                    // Librería para uso del bus I2C
#include <MPU6050.h>                                 // Librería del acelerómetro
#include <LowPower.h>                                // Librería del modo de bajo consumo

const int LEDpin = 5;

// Constructor del objeto del acelerómetro ------------------------------------------------------------------------------
MPU6050 mpu;

// Declaración e inicialización de constantes ---------------------------------------------------------------------------
const uint8_t prescaler = 16;                        // Factor de división del prescaler
const bool debug = 1;                                // Toggle para activar o desactivar el serial

const int umbral = 8000;                             // Umbral para la detección de cambio

// Función que enciende el LED y mete en sleep el micro durante el tiempo que se desee ==================================
void enciendeLED(){
  if(debug == 1){                                    // Activo aquí el serial y no en el setup para ahorrar recursos
    Serial.begin(600*prescaler);                     // Poner serial monitor a baudios*prescaler
  }

  delay(500/prescaler);                              // TODOS LOS DELAYS ANTES DE MENSAJES AL SERIAL SON POR HABER BAJADO LA VELOCIDAD DEL RELOJ
  Serial.println("Salero en uso...");

  digitalWrite(LEDpin, HIGH);                        // Pongo el LED a brillar

  delay(500/prescaler);
  Serial.println("Sleeping...");

  for (int i = 0 ;  i  <  4 ; i++){                  // Me voy a dormir y, cuidado, el primer parámetro de powerDown está definido y no se puede poner lo que se quiera, por lo que se debe de jugar multiplicando uno de los disponibles en un bucle for (aquí son 4 segundos 4 veces, 16 segundos)
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }

  digitalWrite(LEDpin, LOW);                         // Tras despertar apago el LED
  delay(500/prescaler);
  Serial.println("Waking up...");

  Serial.end();                                      // Apago el serial para ahorrar recursos
}

// SETUP ===============================================================================================================
void setup() {
  CLKPR = 0x80;
  CLKPR = 0x04;                                      // Prescaler del reloj dividiendo la velocidad entre 16, ahora a 1 MHz

  Wire.begin();                                      // Inicio el bus I2C
  mpu.initialize();                                  // Inicio el acelerómetro

  pinMode(LEDpin, OUTPUT);

  digitalWrite(LEDpin, LOW);                         // CUIDADO CON LA POLARIZACIÓN DEL LED CON ÁNODO COMÚN
}

// LOOP ================================================================================================================
void loop() {
  int16_t ay = mpu.getAccelerationY();               // Función de librería para obtener la aceleración en el eje Y

  if (abs(ay) > umbral){                             // Si la aceleración supera al umbral definido
    enciendeLED();                                   // llamo a la función del indicativo luminoso
  }else{
    digitalWrite(LEDpin, LOW);                       // De superar el umbral, dejo el LED apagado
  }

  delay(500/prescaler);                              // Delay "de cortesía" para el ciclo del loop
}