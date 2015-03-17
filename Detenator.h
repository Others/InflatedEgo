class Detonator{
  public:
    int detonationPort;
    Detonator(int detonationPort);
    boolean checkDetonationConditions();
    void detonate();
};

Detonator::Detonator(int detonationPort){
  this -> detonationPort = detonationPort;
  pinMode(detonationPort, OUTPUT);
}

boolean Detonator::checkDetonationConditions(){
  return false;
}

void Detonator::detonate(){
  digitalWrite(detonationPort, HIGH);
}
