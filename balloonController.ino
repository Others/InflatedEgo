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
  #define LOOP_DELAY 10000
  
//Setup serial ports
  SoftwareSerial GPS_SERIAL = SoftwareSerial(2, 3);
  SoftwareSerial TEXT_SERIAL = SoftwareSerial(5, 6);
  SoftwareSerial LOGGER_SERIAL = SoftwareSerial(7, 8);
  
//Setup global control systems
  #include "Logger.h"
  #include "Text2Speech.h"
  #include "Detenator.h"
  Logger LOGGER = Logger(&LOGGER_SERIAL);
  TextTransmitter SPEECH_SYNTH = TextTransmitter(&TEXT_SERIAL, TALK_PIN);
  Detonator DETONATOR = Detonator(SELF_DESTRUCT_PIN);
  
//Include the sensor code
  #include "Altimeter.h"
  #include "Clock.h"
  #include "Gps.h"
  #include "Thermometer.h"
  //Setup the various loggable sensors
  Clock CLOCK = Clock();
  Thermometer THERMOMETER = Thermometer(TEMP_PIN);
  GPS GPS_SENSOR = GPS(&GPS_SERIAL);
  Altimeter ALTIMETER = Altimeter(ALTIMETER_PIN);
  
  
void setup() {
  GPS_SERIAL.begin(9600);
  TEXT_SERIAL.begin(9600);
  LOGGER_SERIAL.begin(9600);
}

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

void loop() {
  logSensors();
  saySensors
  CLOCK.incrementLoop();
  delay(LOOP_DELAY);
}
