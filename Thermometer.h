//To implement: Getting tempature, better string code
class Thermometer: public Logable, public Transmitable{
  public:
    SerialWrapper* serialPort;
    Thermometer(SerialWrapper* serialPort);
    int getFarenhight();
    String toLogText();
    String toTransmitText();
};

Thermometer::Thermometer(SerialWrapper* serialPort){
  this -> serialPort = serialPort;
}

int Thermometer::getFarenhight(){
  return 0;
}

String Thermometer::toLogText(){
  String tempatureString = "It is ";
  tempatureString+=getFarenhight();
  tempatureString+=" degrees farenhight";
  return tempatureString;
}

String Thermometer::toTransmitText(){
  return toLogText();
}
