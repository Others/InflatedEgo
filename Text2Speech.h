String newLine="\n";
String emptyString="";
String s="S";
String volume="V18\n";
int colon=':';

class Transmitable{
  public:
    virtual String toTransmitText();
};

class TextTransmitter{
  public:
    int talkPort;
    SerialWrapper* serialPort;
    TextTransmitter(SerialWrapper* serialPort, int talkPort);
    void transmit(String text);
    void transmit(Transmitable toTransmit);
    void sendRawLine(String text);
};

TextTransmitter::TextTransmitter(SerialWrapper* serialPort, int talkPort){
  this -> serialPort = serialPort;
  if(serialPort -> baud != 9600){
    //throw "Incorrect baud on serial port!";
  }
  this -> talkPort = talkPort;
  pinMode(talkPort, OUTPUT);
  this -> sendRawLine(emptyString);
  delay(10);
  this -> serialPort -> flush();
  this -> sendRawLine(volume);
}

void TextTransmitter::sendRawLine(String text){
  digitalWrite(talkPort, HIGH);
  delay(100);
  serialPort -> print(text);
  serialPort -> print(newLine);
  while (serialPort -> read() != colon);
  delay(100);
  digitalWrite(talkPort, LOW);
}

void TextTransmitter::transmit(String text){
  digitalWrite(talkPort, HIGH);
  delay(100);
  serialPort -> print(s);
  serialPort -> print(text);
  serialPort -> print(newLine);
  while (serialPort -> read() != colon);
  delay(100);
  digitalWrite(talkPort, LOW);
}

void TextTransmitter::transmit(Transmitable transmitable){
  this -> transmit(transmitable.toTransmitText());
}
