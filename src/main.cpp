/* **********************************************************************************************************************
SALERO MAR DE NIEBLA v1 - Carmen: aditamento para saleros que indica por medio de un switch de inclinación con LEDs
cuántas veces se ha echado sal a la comida con un máximo de tres veces. Cada vez que se use, los LEDs quedarán encendidos
durante una hora y, posteriormente, se entrará en sleep mode de forma indeterminada. Cuando el botón por inclinación se
cierre durante el sleep mode, provocará una interrupción que despertará al dispositivo y lo llevará de nuevo al estado
inicial de la máquina de estados. El consumo se ha estudiado para que se consuman 10 microamperios durante el sleep mode
y unos 70 microamperios en funcionamiento, conseguido por medio de bajar la velocidad del reloj del Atmel a 1MHz, la
implemen tación del sleep mode y la desconexión del LED de PWR tras quitar su resistencia.
********************************************************************************************************************** */

// Inclusión de librerías -----------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <LowPower.h>                                        // Librería para echar a dormir el Arduino de forma muy sencilla

// Pin number declarations ----------------------------------------------------------------------------------------------
const uint8_t  greenLEDpin    = 3;
const uint8_t  yellowLEDpin   = 4;
const uint8_t  redLEDpin      = 5;
const uint8_t  incbutPin      = 2;                           // SWITCH DE INCLINACIÓN AL D2 PORQUE ADMITE INTERRUPCIÓN

// Declaración e inicialización de constantes ---------------------------------------------------------------------------
const bool     debug          = true;                        // Toggle para activar o desactivar el serial
const uint8_t  prescaler      = 16;                          // Factor de división del prescaler
const uint16_t bloqueo        = 2000/prescaler;              // Tiempo de bloqueo entre aplicaciones de sal - RECOMENDADO 5 SEGUNDOS
const uint16_t espera         = 30000/prescaler;             // Intervalo de espera entre usos del salero -  RECOMENDADO 1 HORA
const uint16_t esperaSerial   = 100/prescaler;               // Intevalo de espera antes de un serial print
const uint16_t esperaPinDig   = 100/prescaler;               // Intervalo de espera después de cambio de estado de pin digital

// Declaración e inicialización de variables ----------------------------------------------------------------------------
uint8_t        salCount       = 0;                           // Indicador de cuántas veces se ha echado sal
unsigned long  previousMillis = 0;                           // Variable para guardar el estado previo de la función millis

// SUBRUTINA DE LA INTERRUPCIÓN =========================================================================================
void incbutAct(){
}                                                            // Vacía porque sólo quiero que despierte el micro

// SETUP ================================================================================================================
void setup() {
  // Clock prescaler - [0x00 16 MHz] [0x01 8 MHz] [0x02 4 MHz] [0x03 2 MHz] [0x04 1 MHz] --------------------------------
  CLKPR = 0x80;
  CLKPR = 0x04;                                              // Prescaler del reloj dividiendo la velocidad entre 16, ahora a 1 MHz

  if(debug){
    Serial.begin(1200*prescaler);                            // Poner serial monitor a 1200*prescaler. 1200 PORQUE ES LO MÁS RÁPIDO CON LO QUE FUNCIONA AL FUNCIONAR A 1 MHz
    delay(esperaSerial);                                     // Delay para que el serial se sincronice dada la bajada de velocidad del reloj
  }

  // Pin modes ----------------------------------------------------------------------------------------------------------
  pinMode(greenLEDpin, OUTPUT);
  pinMode(yellowLEDpin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(incbutPin, INPUT_PULLUP);                          // Uso INPUT_PULLUP para simplificar el circuito, LÓGICA INVERTIDA

  // Modo de inicio de los pines ----------------------------------------------------------------------------------------
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(yellowLEDpin, LOW);
  digitalWrite(redLEDpin, LOW);
  delay(esperaPinDig);                                       // Delay de cortesía para cambiar estados digitales por la bajada de velocidad del reloj

  // Interrupción por input en pin digital ------------------------------------------------------------------------------
  attachInterrupt(0, incbutAct, FALLING);                    // Añado la interrupción al pin 2, referido como INT0, para que ejectute la Interruption Service Routine (ISR) cuando haya un flanco descendente (por ser INPUT_PULLUP, al presionar pasa de 1 a 0)

  delay(esperaSerial);
  Serial.println("Salero MdN inicializado");
}

// LOOP =================================================================================================================
void loop() {
  unsigned long currentMillis = millis();                    // Variable que guarda el valor actual en milisegundos desde que se inició el Arduino

  // Máquina de estados Salero Mar de Niebla ----------------------------------------------------------------------------
  switch(salCount){

    // Caso 0: Aún no se ha echado sal ninguna vez ----------------------------------------------------------------------
    case 0:
      if(digitalRead(incbutPin) == !HIGH){                   // RECUERDA, todo lo referido al switch de inclinación va con lógica invertida
        Serial.println("Primera vez echada");
        delay(esperaSerial);

        digitalWrite(greenLEDpin, HIGH);
        delay(esperaPinDig);                                 // Con pequeño delay para estabilizar el pin

        salCount++;                                          // Se aumenta la variable para el cambio de estado
        delay(bloqueo);                                      // Delay para bloquear que se cuente echar sal más de una vez a cada una de las veces
      }
      break;

    // Caso 1: Se ha echado sal una vez ---------------------------------------------------------------------------------
    case 1:
      if(currentMillis - previousMillis >= espera){          // Si despues de echar sal una vez pasa 1h, se vuelve al estado inicial
        previousMillis = currentMillis;
        
        Serial.println("Me voy a dormir...");
        delay(esperaSerial);

        digitalWrite(greenLEDpin, LOW);                      // Apago el LED (o LEDs acumulados posteriormente)
        delay(esperaPinDig);

        // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        Serial.println("¡Me he despertado!");
        delay(esperaSerial);
        // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        salCount = 0;                                        // Reinicio la máquina de estados
      }
      else if(digitalRead(incbutPin) == !HIGH){              // Si por el contrario, se detecta el switch de inclinación en !HIGH, es que le eché sal
        Serial.println("Segunda vez echada");
        delay(esperaSerial);

        digitalWrite(yellowLEDpin, HIGH);                    // Añado ahora el segundo LED
        delay(esperaPinDig);

        salCount++;
        delay(bloqueo);
      }
      break;

    // Caso 2: Se ha echado sal dos veces -------------------------------------------------------------------------------
    case 2:
      if(currentMillis - previousMillis >= espera){          // Si despues de echar sal dos veces pasa 1h, se vuelve al estado inicial. Igual que en el estado anterior, pero ahora se apagan los LEDs acumulados
        previousMillis = currentMillis;

        Serial.println("Me voy a dormir...");
        delay(esperaSerial);

        digitalWrite(greenLEDpin, LOW);
        digitalWrite(yellowLEDpin, LOW);
        delay(esperaPinDig);

        // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        Serial.println("¡Me he despertado!");
        delay(esperaSerial);
        // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        salCount = 0;
      }
      else if(digitalRead(incbutPin) == !HIGH){
        Serial.println("Tercera vez echada");
        delay(esperaSerial);

        digitalWrite(redLEDpin, HIGH);
        delay(esperaPinDig);

        salCount++;
        delay(bloqueo);
      }
      break;

    // Caso 3: Se ha echado sal tres veces -----------------------------------------------------------------------------
    case 3:
      if(currentMillis - previousMillis >= espera){          // Después de echar sal tres veces mantengo el sistema como está 1h
        previousMillis = currentMillis;

        Serial.println("Me voy a dormir...");
        delay(esperaSerial);

        digitalWrite(greenLEDpin, LOW);                      // Apago todos los LEDs
        digitalWrite(yellowLEDpin, LOW);
        digitalWrite(redLEDpin, LOW);
        delay(esperaPinDig);

        // ME VOY A DEEP SLEEP HASTA QUE HAYA UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        delay(esperaSerial);
        Serial.println("¡Me he despertado!");
        // ME DESPIERTO PORQUE HUBO UNA INTERRUPCIÓN EN EL PIN 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        salCount = 0;
      }                                
      break;
      
  }

  delay(50/prescaler);                                       // Delay de cortesía de la función loop
}
