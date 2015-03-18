//Define the states for the state machine
  #define RISING_STATE 0
  #define PLANNING_DETONATION_STATE 1
  #define DETONATION_STATE 2
  #define FAILED_TO_DETONATE_STATE 3
  #define DETONATION_CANCELLED_STATE 4
  #define FALLING_STATE 5
  #define GROUND_STATE 6
  
int currentState = RISING_STATE;
int lastSwitch = 0;

int runRisingState(){
  return 0;
}

int runPlanningDetonationState(){
  return 0;
}

int runDetonationState(){
  return 0;
}

int runFailedDetonationState(){
  return 0;
}

int runDetonationCancelledState(){
  return 0;
}

int runFallingState(){
  return 0;
}

int runGroundState(){
  return 0;
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
    case(DETONATION_CANCELLED_STATE):
      currentState=runDetonationCancelledState();
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
