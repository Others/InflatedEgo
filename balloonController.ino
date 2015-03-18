
//Dependancies
  #include "Arduino.h"
  #include "Time.h"
  #include "SoftwareSerial.h"
  #include "Wire.h"
  #include "OneWire.h"
  #include "IntersemaBaro.h"
  #include "SerialWrapper.h"

//Setup binary ports
  #define TALK_PIN 4
  #define TEMP_PIN 9
  #define ALTIMETER_PIN 5 //DO NOT CHANGE (Analog pin!)
  #define SELF_DESTRUCT_PIN 10
  #define MINIMUM_DELAY 6000
  
//Setup serial ports
  SoftwareSerial GPS_SERIAL = SoftwareSerial(2, 3);
  SoftwareSerial TEXT_SERIAL = SoftwareSerial(5, 6);
  SoftwareSerial LOGGER_SERIAL = SoftwareSerial(7, 8);

//Setup global control systems
  #include "Logger.h"
  #include "Text2Speech.h"
  #include "Detenator.h"
  Logger LOGGER;
  TextTransmitter SPEECH_SYNTH;
  Detonator DETONATOR;

//Include the sensor code
  #include "Altimeter.h"
  #include "Clock.h"
  #include "Gps.h"
  #include "Thermometer.h"
  
//Setup the various loggable sensors
  Clock CLOCK;
  Thermometer THERMOMETER;
  GPS GPS_SENSOR;
  Altimeter ALTIMETER;
  
  void logSensors() {
    CLOCK.logText();
    ALTIMETER.logText();
    THERMOMETER.logText();
    GPS_SENSOR.logText();
  }
  
  void saySensors() {
    CLOCK.transmitText();
    ALTIMETER.transmitText();
    THERMOMETER.transmitText();
    GPS_SENSOR.transmitText();
  }
  
//Setup the various state machines
#include "State.h"

void setup() {
  Serial.begin(9600);
  GPS_SERIAL.begin(9600);
  TEXT_SERIAL.begin(9600);
  LOGGER_SERIAL.begin(9600);
  LOGGER = Logger(&LOGGER_SERIAL);
  SPEECH_SYNTH = TextTransmitter(&TEXT_SERIAL, TALK_PIN);
  DETONATOR = Detonator(SELF_DESTRUCT_PIN);
  CLOCK = Clock();
  THERMOMETER = Thermometer(TEMP_PIN);
  GPS_SENSOR = GPS(&GPS_SERIAL);
  ALTIMETER = Altimeter(ALTIMETER_PIN);
  CLOCK.init();
  Serial.println("Some string");
}


void stateMode(){
  //runState();
}

void testMode(){
//  logSensors();
//  saySensors();
//  delay(MINIMUM_DELAY);
}

void loop() {
  delay(1000);
  Serial.println("Loop ran");
//  CLOCK.incrementLoop();
//  testMode();
}
