class TextTransmitter{
  public:
    SerialWrapper* serialPort;
    TextTransmitter(SerialWrapper* serialPort);
    void sendLine(String text);
    void sendRawLine(String text);
    void sendLogable(Logable logable);
};

TextTransmitter::TextTransmitter(SerialWrapper* serialPort){
  this -> serialPort = serialPort;
  if(serialPort -> baud != 9600){
    //throw "Incorrect baud on serial port!";
  }
  this -> sendRawLine("");
  delay(10);
  this -> serialPort -> flush();
  this -> sendRawLine("V18\n");
}

void TextTransmitter::sendRawLine(String text){
  serialPort -> print(text);
  serialPort -> print("\n");
  while (serialPort -> read() != ':');
}

void TextTransmitter::sendLine(String text){
  serialPort -> print("S");
  this -> sendRawLine(text);
}

void TextTransmitter::sendLogable(Logable logable){
  this -> sendLine(logable.toString());
}
