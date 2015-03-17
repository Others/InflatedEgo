class SerialWrapper{
  public:
    int baud;
  
    virtual void print(String data) = 0;
    
    virtual void println(String data) = 0;
    
    virtual void write(byte data) = 0;
    
    virtual int read() = 0;
    
    virtual void flush() = 0;
};

class Hardware_Serial: public SerialWrapper{
  public:
    Hardware_Serial(int baud);
    
    virtual void print(String data);
    
    virtual void println(String data);
    
    virtual void write(byte data);
    
    virtual int read();
    
    virtual void flush();
};

Hardware_Serial::Hardware_Serial(int baud){
  Serial.begin(baud);
  this -> baud = baud;
}

void Hardware_Serial::println(String data){
  Serial.println(data);
}

void Hardware_Serial::print(String data){
  Serial.print(data);
}

void Hardware_Serial::write(byte data){
  Serial.write(data);
}

int Hardware_Serial::read(){
  return Serial.read();
}

void Hardware_Serial::flush(){
  return Serial.flush();
}

class Software_Serial: public SerialWrapper{
 
  public:
    SoftwareSerial* port;
    
    Software_Serial(SoftwareSerial* softwareSerial, int baud);
    
    virtual void print(String data);
    
    virtual void println(String data);
    
    virtual void write(byte data);
    
    virtual int read();
    
    virtual void flush();
};

Software_Serial::Software_Serial(SoftwareSerial* softwareSerial, int baud){
  port=softwareSerial;
  port -> begin(baud);
  this -> baud = baud;
}

void Software_Serial::println(String data){
  port -> println(data);
}

void Software_Serial::print(String data){
  port -> print(data);
}

void Software_Serial::write(byte data){
  port -> write(data);
}

int Software_Serial::read(){
  return port -> read();
}

void Software_Serial::flush(){
  port -> flush();
}
