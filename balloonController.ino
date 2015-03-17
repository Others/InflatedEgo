//Depandancies
  //Include serial code
  #include "Arduino.h"
  #include "SoftwareSerial.h"
  #include "SerialWrapper.h"
  //Include the logger and text 2 speech code
  #include "Logger.h"
  #include "Text2Speech.h"
  //Include the sensor code
  #include "Altimeter.h"
  #include "Gps.h"
  #include "Thermometer.h"
  //Include the logic code
  #include "Detenator.h"
  #include "Comms.h"
  
//Setup predefined constants
  //Setup binary ports
  #define TALK_PIN 9
  #define SELF_DESTRUCT_PIN 10
  //Setup serial ports
  SerialWrapper* GPS_SERIAL = new Hardware_Serial(9600);
  SerialWrapper* TEXT_SERIAL = new Software_Serial(new SoftwareSerial(5, 6), 9600); 
  SerialWrapper* LOGGER_SERIAL = new Software_Serial(new SoftwareSerial(7, 8), 9600);
  
//Setup sensors and data interpreters
  //Setup logger and transmitter 
  TextTransmitter* speech = new TextTransmitter(TEXT_SERIAL);
  Logger* logger = new Logger(LOGGER_SERIAL);
  //Setup the various loggable sensors
  Logable* SENSORS [] = {};

//Setup the logic systems
  Detonator* detonator = new Detonator(SELF_DESTRUCT_PIN);
  Comms* comms = new Comms();

void setup() {}

void loop() {
  if(detonator -> checkDetonationConditions()){
    detonator -> detonate();
  }
}
