class Logger{
  public:
    SoftwareSerial* serialPort;
    Logger(SoftwareSerial* serialPort);
    Logger();
    void logLine(String line);
    void logString(String string);
};
Logger::Logger(){}
Logger::Logger(SoftwareSerial* serialPort){
  Serial.begin(9600);
  delay(1000);
  Serial.println("Logger constructed!");
  this -> serialPort = serialPort;
}

void Logger::logLine(String line){
  this -> serialPort -> println(line);
}


void Logger::logString(String line){
  this -> serialPort -> print(line);
}

