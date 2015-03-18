//To implement: better string code
class Clock{
  public:
    int loops=0;
    int nowSeconds();
    void incrementLoop();
    void logText();
    void transmitText();
};

int Clock::nowSeconds(){
  return now();
}

void Clock::logText(){
  String timeString = "Time:";
  timeString +=  hour();
  timeString += ":";
  timeString += minute();
  timeString += "-";
  timeString += day();
  timeString += "/";
  timeString += month();
  timeString += "/";
  timeString += year();
  timeString += ". This information gathered after ";
  timeString += loops;
  timeString += " loops!";
  LOGGER.logLine(timeString);
}

void Clock::transmitText(){
  String timeString = "It is ";
  timeString += hour();
  timeString += " ";
  timeString += minute();
  SPEECH_SYNTH.transmit(timeString);
}

void Clock::incrementLoop(){
  loops++;
}
