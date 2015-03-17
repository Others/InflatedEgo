//To implement: Knowing when to send dispatch, knowing how to attempt to warn
class Comms{
  public:
    TextTransmitter* transmitter;
    Comms(TextTransmitter* transmitter);
    boolean attemptConfirmDetonation(); //Should return true if it has already warned, and recived no cancel order
    boolean shouldSendDispatch();
    void transmit(Transmitable transmitable);
};

Comms::Comms(TextTransmitter* transmitter){
  this -> transmitter = transmitter;
}

void Comms::transmit(Transmitable transmitable){
  transmitter -> transmit(transmitable);
}

boolean Comms::attemptConfirmDetonation(){
  return false;
}

boolean Comms::shouldSendDispatch(){
  return false;
}
