class Logable{
  public:
    virtual String toLogText();
};

class Logger{
  public:
    SerialWrapper* serialPort;
    Logger(SerialWrapper* serialPort);
    void logLine(String line);
    void logString(String string);
    void logLogable(Logable logable);
};

Logger::Logger(SerialWrapper* serialPort){
  this -> serialPort = serialPort;
  if(serialPort -> baud != 9600){
    //throw "Incorrect baud on serial port!";
  }
}

void Logger::logLine(String line){
  this -> serialPort -> println(line);
}


void Logger::logString(String line){
  this -> serialPort -> print(line);
}

void Logger::logLogable(Logable line){
  this -> serialPort -> print(line.toLogText());
}

