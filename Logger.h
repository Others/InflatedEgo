class Logger{
  public:
    SoftwareSerial* serialPort;
    Logger(SoftwareSerial* serialPort);
    void logLine(String line);
    void logString(String string);
};

Logger::Logger(SoftwareSerial* serialPort){
  this -> serialPort = serialPort;
}

void Logger::logLine(String line){
  this -> serialPort -> println(line);
}


void Logger::logString(String line){
  this -> serialPort -> print(line);
}

