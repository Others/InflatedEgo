//Define the states for the state machine
  #define RISING_STATE 0
  #define PLANNING_DETONATION_STATE 1
  #define DETONATION_STATE 2
  #define FAILED_TO_DETONATE_STATE 3
  #define FALLING_STATE 4
  #define GROUND_STATE 5
  
int currentState = RISING_STATE;
int lastSwitch = 60;
float heights[20];
int row = 0;

void singStarSpangledBanner(){
}

void warnGroundDetonation(){
}

boolean isFalling(){
  for (int i=0;i<19;i++) heights[i] = heights[i+1];
  heights[19] = ALTIMETER.getHeight();
  if (heights[19]<heights[0]) row+=1;
  else row = 0;
  if (row==5) return true;
  return false;
  
}

boolean shouldDetonate(){
  return false;
}

boolean groundCancelled(){
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
  while(CLOCK.nowSeconds()-startTime < 600){
    if(groundCancelled()){
      return RISING_STATE;
    }
    delay(10);
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
