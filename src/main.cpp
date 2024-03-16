/* **********************************************************************************************************************
SALERO MAR DE NIEBLA V1: aditamento para salero que indica con LEDs cuántas veces se ha echado sal a la comida con un
máximo de tres veces. Cada vez que se use, los LEDs quedarán encendidos durante una hora y, posteriormente, se entra-
rá en sleep mode de forma indeterminada. Cuando el botón por inclinación se cierre durante el sleep mode, provocará una
interrupción que despertará al dispositivo y lo llevará de nuevo al estado inicial de la máquina de estados.
********************************************************************************************************************** */

// Inclusión de librerías -----------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <LowPower.h>

// Pin number declarations ----------------------------------------------------------------------------------------------
const uint8_t  greenLEDpin    = 3;
const uint8_t  yellowLEDpin   = 4;
const uint8_t  redLEDpin      = 5;
const uint8_t  incbutPin      = 2;

// Declaración e inicialización de constantes ---------------------------------------------------------------------------
const bool     debug          = true;                // Toggle para activar o desactivar el serial
const uint8_t  prescaler      = 16;                  // Factor de división del prescaler
const uint16_t bloqueo        = 2000/prescaler;      // Tiempo de bloqueo entre aplicaciones de sal
const uint16_t espera         = 5000/prescaler;      // Intervalo de espera entre usos del salero
const uint16_t esperaSerial   = 50/prescaler;        // Intevalo de espera antes de un serial print
const uint16_t esperaPinDig   = 100/prescaler;       // Intervalo de espera después de cambio de estado de pin digital



// Declaración e inicialización de variables
uint8_t        salCount       = 0;                   // Indicador de cuántas veces se ha echado sal
unsigned long  previousMillis = 0;                   // Variable para guardar el estado previo de la función millis

// SUBRUTINA DE LA INTERRUPCIÓN ----------------------------------------------------------------------------------------
void incbutAct(){
}                                                    // Vacía porque sólo quiero que despierte el micro

// SETUP ===============================================================================================================
void setup() {
  CLKPR = 0x80;
  CLKPR = 0x04;                                      // Prescaler del reloj dividiendo la velocidad entre 2, ahora a 8 MHz

  if(debug){
    delay(esperaSerial);                             // Delay para que el serial se sincronice dada la bajada de velocidad del reloj
    Serial.begin(1200*prescaler);                    // Poner serial monitor a baudios*prescaler
  }

  // Pin modes
  pinMode(greenLEDpin, OUTPUT);
  pinMode(yellowLEDpin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(incbutPin, INPUT);

  // Modo de inicio de los pines
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(yellowLEDpin, LOW);
  digitalWrite(redLEDpin, LOW);
  delay(esperaPinDig);                               // Delay de cortesía para cambiar estados digitales por la bajada de velocidad del reloj

  // Interrupción por input en pin digital
  attachInterrupt(0, incbutAct, RISING);             // Añado la interrupción al pin 2, referido a 0, para que ejecture la ISR cuando haya un flanco ascendente

  delay(esperaSerial);
  Serial.println("Salero MdN inicializado");
}

// LOOP ================================================================================================================
void loop() {
  unsigned long currentMillis = millis();

  // Máquina de estados Salero Mar de Niebla ---------------------------------------------------------------------------
  switch(salCount){

    // Caso 0: Aún no se ha echado sal ninguna vez ---------------------------------------------------------------------
    case 0:
      if(digitalRead(incbutPin) == HIGH){
        Serial.println("Primera vez echada");

        digitalWrite(greenLEDpin, HIGH);
        delay(esperaPinDig);

        salCount++;

        delay(bloqueo);                              // Delay para bloquear que se cuente echar sal más de una vez a cada una de las veces
      }
      break;
    // Caso 1: Se ha echado sal una vez --------------------------------------------------------------------------------
    case 1:
      if(currentMillis - previousMillis >= espera){  // Si despues de echar sal una vez pasa 1h, se vuelve al estado inicial
        previousMillis = currentMillis;
        
        digitalWrite(greenLEDpin, LOW);

        // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 -----------------------------------------------
        delay(esperaSerial);
        Serial.println("Me voy a dormir...");
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        delay(esperaSerial);
        Serial.println("¡Me he despertado!");
        // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ---------------------------------------------------------

        salCount = 0;
      }
      else if(digitalRead(incbutPin) == HIGH){
        Serial.println("Segunda vez echada");

        digitalWrite(yellowLEDpin, HIGH);
        delay(esperaPinDig);

        salCount++;
        delay(bloqueo);
      }
      break;

    // Caso 2: Se ha echado sal dos veces -----------------------------------------------------------------------------
    case 2:
      if(currentMillis - previousMillis >= espera){  // Si despues de echar sal dos veces pasa 1h, se vuelve al estado inicial
        previousMillis = currentMillis;

        digitalWrite(greenLEDpin, LOW);
        digitalWrite(yellowLEDpin, LOW);

        // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 -----------------------------------------------
        delay(esperaSerial);
        Serial.println("Me voy a dormir...");
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        delay(esperaSerial);
        Serial.println("¡Me he despertado!");
        // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ---------------------------------------------------------

        salCount = 0;
      }
      else if(digitalRead(incbutPin) == HIGH){
        Serial.println("Tercera vez echada");

        digitalWrite(redLEDpin, HIGH);
        delay(esperaPinDig);

        salCount++;
        delay(2000/prescaler);
      }
      break;

    // Caso 3: Se ha echado sal tres veces ----------------------------------------------------------------------------
    case 3:
      unsigned long tiempoInicio = millis();
      while(millis() - tiempoInicio < espera){          // Después de echar sal tres veces mantengo el sistema como está 1h
        previousMillis = currentMillis;
      }

      digitalWrite(greenLEDpin, LOW);                   // Apago todos los LEDs
      digitalWrite(yellowLEDpin, LOW);
      digitalWrite(redLEDpin, LOW);
      delay(esperaPinDig);

      // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 -----------------------------------------------
      delay(esperaSerial);
      Serial.println("Me voy a dormir...");
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      delay(esperaSerial);
      Serial.println("¡Me he despertado!");
      // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ---------------------------------------------------------

      salCount = 0;                                  
      break;
  }

  delay(50/prescaler);
}
