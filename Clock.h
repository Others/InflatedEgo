//To implement: better string code
class Clock: public Logable, public Transmitable{
  public:
    int loops=0;
    int nowSeconds();
    void incrementLoop();
    String toLogText();
    String toTransmitText();
};

int Clock::nowSeconds(){
  return now();
}

String Clock::toLogText(){
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
  return timeString;
}

String Clock::toTransmitText(){
  String timeString = "It is ";
  timeString += hour();
  timeString += " ";
  timeString += minute();
  return timeString;
}

void Clock::incrementLoop(){
  loops++;
}
