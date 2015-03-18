//To implement: Better string code
float readFloat(String s) {
  float ans = 0;
  for (int i=0;i<s.length();i++) {
    if (s[i]=='.') continue;
    ans*=10;
    ans+=s[i]-'0';
  }
  return ans;
}

int finding(String s, char c) {
  for (int i=1;i<=s.length();i++) if (s[i]==c) return i;
  return -1;
}

class GPS{
  public:
    float timeCoordsGroundspeed[4] = {0,0,0,0};
    SoftwareSerial* gpsTest;
    GPS(SoftwareSerial* serial);
    float* getTimeCoordinatesAndSpeed();
    void logText();
    void transmitText();
};

GPS::GPS(SoftwareSerial* gpsTest){
  this -> gpsTest = gpsTest;
}

float* GPS::getTimeCoordinatesAndSpeed(){
  String data = "";
  String gpgga = "";
  String gprmc = "";
  while (gpgga.length()==0 || gprmc.length()==0) {
    while(true) {
      char gpsByte = gpsTest -> read();
      if (gpsByte==-1) continue;
      data += gpsByte;
      if(gpsByte == 13){
        if (data[5]=='G') {
          gpgga = data;
          data = "";
          break;
        }
        if (data[5]=='M') {
          gprmc = data;
          data = "";
          break;
        }
        data = "";
      }
    }
  }
  
  // parse gpgga
  int where = finding(gpgga,',');
  String stuff[10];
  for (int i=0;i<10;i++) {
    gpgga[where] = '$';
    int next = finding(gpgga,',');
    stuff[i] = gpgga.substring(where+1,next);
    where = next;
  }
  float time = readFloat(stuff[0])/100;
  float lat = readFloat(stuff[1])/10000000;
  float lon = readFloat(stuff[3])/10000000;
  
  // parse gprmc
  where = finding(gprmc,',');
  String stuff2[10];
  for (int i=0;i<10;i++) {
    gprmc[where] = '$';
    int next = finding(gprmc,',');
    stuff2[i] = gprmc.substring(where+1,next);
    where = next;
  }
  if (time<100000 || time>10000000) time = readFloat(stuff[0])/100;
  if (lat<10 || lat>100) lat = readFloat(stuff2[2])/10000000;
  if (lon<50 || lon>180) lon = readFloat(stuff2[4])/10000000;
  float spd = readFloat(stuff2[6])/1000;
  timeCoordsGroundspeed[0]=time;
  timeCoordsGroundspeed[1]=lat;
  timeCoordsGroundspeed[2]=lon;
  timeCoordsGroundspeed[3]=spd;
  return timeCoordsGroundspeed;
}

void GPS::logText(){
  float time=timeCoordsGroundspeed[0];
  float lat=timeCoordsGroundspeed[1];
  float lon=timeCoordsGroundspeed[2];
  float spd=timeCoordsGroundspeed[3];
  String transmitText = "We are at ";
  transmitText+=lat;
  transmitText+=" degrees latitude ";
  transmitText+=lon;
  transmitText+=" degrees longitude. It is ";
  transmitText+=time;
  transmitText+=" and our groundspeed is ";
  transmitText+=spd; 
  LOGGER.logLine(transmitText);
}

void GPS::transmitText(){
  float time=timeCoordsGroundspeed[0];
  float lat=timeCoordsGroundspeed[1];
  float lon=timeCoordsGroundspeed[2];
  float spd=timeCoordsGroundspeed[3];
  String transmitText = "We are at ";
  transmitText+=lat;
  transmitText+=" degrees latitude ";
  transmitText+=lon;
  transmitText+=" degrees longitude. It is ";
  transmitText+=time;
  transmitText+=" and our groundspeed is ";
  transmitText+=spd;
  SPEECH_SYNTH.transmit(transmitText);
}
