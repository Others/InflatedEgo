Intersema::BaroPressure_MS5607B baro(true);

class Altimeter{
  public:
    Altimeter(int pin);
    int getHeight();
    void logText();
    void transmitText();
};

Altimeter::Altimeter(int pin){}

void Altimeter::logText(){
  String tbr="Altitude is ";
  tbr+=getHeight();
  LOGGER.logLine(tbr + "feet");
}

void Altimeter::transmitText(){
  String tbr="Altitude is ";
  tbr+=getHeight();
  SPEECH_SYNTH.transmit(tbr + "feet");
}

int Altimeter::getHeight(){
  return (int) ((baro.getHeightCentiMeters() - 7391.4) / 30.48);
}
