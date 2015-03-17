//To implement: Getting the height + better string code
class Altimeter: public Logable, public Transmitable{
  public:
    SerialWrapper* serialPort;
    Altimeter(SerialWrapper* serialPort);
    int getHeight();
    String toLogText();
    String toTransmitText();
};

Altimeter::Altimeter(SerialWrapper* serialPort){
  this -> serialPort = serialPort;
}

String Altimeter::toLogText(){
  String tbr="Altitude is ";
  tbr+=getHeight();
  return tbr + "feet";
}

String Altimeter::toTransmitText(){
  return toLogText();
}

int getHeight(){
  return 0;
}
