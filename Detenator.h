////To implement: Knowing when we should detonate based on sensor data
class Detonator{
  public:
    int detonationPort;
    boolean hasDetonated = false;
    boolean detonationSequenceComplete = false;
    Detonator();
    Detonator(int detonationPort);
    boolean allowDetonation();
    boolean atDetonationConditions();
    void detonate();
    void cancelDetonator();
};
Detonator::Detonator(){}
Detonator::Detonator(int detonationPort){
  this -> detonationPort = detonationPort;
  pinMode(detonationPort, OUTPUT);
}

boolean Detonator::allowDetonation(){
  return (!hasDetonated) && atDetonationConditions();
}

void Detonator::detonate(){
  digitalWrite(detonationPort, HIGH);
  hasDetonated = true;
  delay(10000);
  digitalWrite(detonationPort, LOW);
}

boolean Detonator::atDetonationConditions(){
  return false;
}
