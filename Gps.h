//To implement: Everything...
class GPS: public Logable, public Transmitable{
  double getLatitude();
  double getLongitude();
  String getRawString();
  String toLogText();
  String toTransmitText();
};

double GPS::getLatitude(){
  return 0;
}
double GPS::getLongitude(){
  return 0;
}

String GPS::getRawString(){
  return "";
}

String GPS::toLogText(){
  return getRawString(); 
}
String GPS::toTransmitText(){
  String transmitText = "We are at ";
  transmitText+=getLatitude();
  transmitText+=" degrees latitude ";
  transmitText+=getLongitude();
  transmitText+=" degrees longitude";
  return transmitText;
}
