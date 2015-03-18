String newLine="\n";
String emptyString="";
String s="S";
String volume="V18\n";
int colon=':';

class TextTransmitter{
  public:
    int talkPort;
    SoftwareSerial* serialPort;
    TextTransmitter(SoftwareSerial* serialPort, int talkPort);
    void transmit(String text);
    void sendRawLine(String text);
};

TextTransmitter::TextTransmitter(SoftwareSerial* serialPort, int talkPort){
  this -> serialPort = serialPort;
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
