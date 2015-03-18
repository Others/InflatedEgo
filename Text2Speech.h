String newLine="\n";
String emptyString="";
String s="S";
String volume="V18\n";

class TextTransmitter{
  public:
    int talkPort;
    SoftwareSerial* serialPort;
    TextTransmitter(SoftwareSerial* serialPort, int talkPort);
    TextTransmitter();
    void transmit(String text);
    void sendRawLine(String text);
};
TextTransmitter::TextTransmitter(){}
TextTransmitter::TextTransmitter(SoftwareSerial* serialPort, int talkPort){
  Serial.println("Constructer called!");
  this -> serialPort = serialPort;
  this -> talkPort = talkPort;
  Serial.println("Ports set");
  pinMode(talkPort, OUTPUT);
  Serial.println("Pin mode set");
  serialPort -> print('\n');             // Send a CR in case the system is already up
  while (serialPort -> read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  serialPort -> flush();                 // Flush the receive buffer
  serialPort -> print("V18\n");
  while (serialPort -> read() != ':');
  Serial.println("Transmitter constructed:");
}

void TextTransmitter::sendRawLine(String text){
  Serial.println("RAW TEXT SENT:");
  Serial.println(text);
  digitalWrite(talkPort, HIGH);
  delay(100);
  serialPort -> print(text);
  serialPort -> print(newLine);
  while (serialPort -> read() != ':');
  delay(100);
  digitalWrite(talkPort, LOW);
  Serial.println("Finished raw test:");
}

void TextTransmitter::transmit(String text){
  Serial.println(text);
  digitalWrite(talkPort, HIGH);
  delay(100);
  serialPort -> print(s);
  serialPort -> print(text);
  serialPort -> print(newLine);
  while (serialPort -> read() != ':');
  delay(100);
  digitalWrite(talkPort, LOW);
}
