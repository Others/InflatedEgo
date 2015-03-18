//Define the states for the state machine
  #define RISING_STATE 0
  #define PLANNING_DETONATION_STATE 1
  #define DETONATION_STATE 2
  #define FAILED_TO_DETONATE_STATE 3
  #define FALLING_STATE 4
  #define GROUND_STATE 5
  
int currentState = RISING_STATE;
int lastSwitch = 60;

int loc = 0;
int count = 0;
int zeros = 0;
int reset = 0;

bool alt = false;

void singStarSpangledBanner(){
}

void warnGroundDetonation(){
}

boolean isFalling(){
  return false;
}

boolean shouldDetonate(){
  return false;
}

boolean groundCancelled(){
  int input = analogRead(A0);
  if (input > 500 & input < 800) { //First tone
    if (!alt) {
      alt = true;
      reset = 0;
    } else {
      count++;
      reset++;
      if (reset > 3) {
        zeros = 0;
      }
    }
  } else if (count > 0 && input < 500) { //Second tone
    if (alt) {
      alt = false;
      zeros++;
    }
  }
  if (zeros > 120 && count > 1000) { //Part of the sound
    loc++;
    count = 0;
    zeros = 0;
    if (loc == 3) { //The full sound!
      loc = 0;
      return true;
    }
  }
  if ((zeros > 300 && count > 10) || count > 1300) { //Not the sound
    zeros = 0;
    count = 0;
    loc = 0;
  }
  return false;
}

int runRisingState(){
  if(CLOCK.loops % 3 == 0 && CLOCK.loops - lastSwitch > 10){
    if(isFalling() || shouldDetonate()){
      logSensors();
      warnGroundDetonation();
      return PLANNING_DETONATION_STATE;
    }
  }
  logSensors();
  if(CLOCK.loops % 2 == 0){
    saySensors();
  }else{
    delay(MINIMUM_DELAY);
  }
  return RISING_STATE;
}

int runPlanningDetonationState(){
  int startTime=CLOCK.nowSeconds();
  loc = 0;
  count = 0;
  zeros = 0;
  reset = 0;
  while(CLOCK.nowSeconds()-startTime < 600){
    if(groundCancelled()){
      return RISING_STATE;
    }
  }
  return DETONATION_STATE;
}

int runDetonationState(){
  int lastHeight = ALTIMETER.getHeight();
  DETONATOR.detonate();
  if(ALTIMETER.getHeight() > lastHeight){
    return FAILED_TO_DETONATE_STATE;
  }
  return FALLING_STATE;
}

int runFailedDetonationState(){
  if(isFalling()){
    return FALLING_STATE;
  }
  logSensors();
  if(CLOCK.loops % 2 == 0){
    saySensors();
  }else{
    delay(MINIMUM_DELAY);
  }
  return FAILED_TO_DETONATE_STATE;
}

int runFallingState(){
  int firstHeight=ALTIMETER.getHeight();
  delay(10000);
  int secondHeight=ALTIMETER.getHeight();
  if(firstHeight-secondHeight < 5  && firstHeight - secondHeight > -5){
    return GROUND_STATE;
  }
  logSensors();
  if(CLOCK.loops % 2){
    saySensors();
  }else{
    delay(MINIMUM_DELAY);
  }
  return FALLING_STATE;
}

int runGroundState(){
  if(CLOCK.loops % 3 == 0){
    singStarSpangledBanner();
  }
  logSensors();
  delay(MINIMUM_DELAY);
  return GROUND_STATE;
}

void runState(){
  int originalState = currentState;
  switch(originalState){
    case(RISING_STATE):
      currentState=runRisingState();
      break;
    case(PLANNING_DETONATION_STATE):
      currentState=runPlanningDetonationState();
      break;
    case(DETONATION_STATE):
      currentState=runDetonationState();
      break;
    case(FAILED_TO_DETONATE_STATE):
      currentState=runFailedDetonationState();
      break;
    case(FALLING_STATE):
      currentState=runFallingState();
      break;
    case(GROUND_STATE):
      currentState=runGroundState();
      break;
    default:
      currentState=FALLING_STATE;
      break;
  }
  if(originalState!=currentState){
    lastSwitch = CLOCK.loops;
  }
}
