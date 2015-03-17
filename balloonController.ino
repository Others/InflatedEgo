//Depandancies
  //Include serial code
  #include "Arduino.h"
  #include "Time.h"
  #include "SoftwareSerial.h"
  #include "SerialWrapper.h"
  //Include the logger and text 2 speech code
  #include "Logger.h"
  #include "Text2Speech.h"
  //Include the sensor code
  #include "Altimeter.h"
  #include "Clock.h"
  #include "Gps.h"
  #include "Thermometer.h"
  //Include the logic code
  #include "Detenator.h"
  #include "Comms.h"
  
//Setup predefined constants
  //Setup binary ports
  #define TALK_PIN 9
  #define SELF_DESTRUCT_PIN 10
  #define LOOP_DELAY 10000
  //Setup serial ports
  SerialWrapper* GPS_SERIAL = new Hardware_Serial(9600);
  SerialWrapper* TEXT_SERIAL = new Software_Serial(new SoftwareSerial(5, 6), 9600); 
  SerialWrapper* LOGGER_SERIAL = new Software_Serial(new SoftwareSerial(7, 8), 9600);
  
//Setup sensors and data interpreters
  //Setup logger and transmitter 
  TextTransmitter* SPEECH_SYNTH = new TextTransmitter(TEXT_SERIAL, TALK_PIN);
  Logger* logger = new Logger(LOGGER_SERIAL);
  //Setup the various loggable sensors
  Clock* clock = new Clock();
  //Setup the sensors that need logged and sensors that need transmitted
  const int NUM_LOG = 0;
  Logable* TO_LOG [] = {};
  
  const int NUM_TRANSMIT = 0;
  Transmitable* TO_TRANSMIT [] = {};

//Setup the logic systems
  Detonator* detonator = new Detonator(SELF_DESTRUCT_PIN);
  Comms* comms = new Comms(SPEECH_SYNTH);
  
void setup() {}

void loop() {
  if(detonator -> allowDetonation() && comms -> attemptConfirmDetonation()){
    detonator -> detonate();
  }
  
  if(comms -> shouldSendDispatch()){
    for(int i=0; i < NUM_TRANSMIT; i++){
      comms -> transmit(*TO_TRANSMIT[i]);
    }
  }
   
  for(int i=0; i < NUM_LOG; i++){
    logger -> logLogable(*TO_LOG[i]);
  }
  
  clock -> incrementLoop();
  delay(LOOP_DELAY);
}
