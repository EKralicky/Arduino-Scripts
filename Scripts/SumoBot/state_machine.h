#ifndef STATE_MACHINE
#define STATE_MACHINE

typedef enum {
  // defined states for the robot to be in
  // START: set at the beginning to start
  // SEARCH: state to search for other robots
  // ATTACK: state to attack other robots
  // STOP: never really called, ending state
  START,
  SEARCH,
  ATTACK,
  STOP
} stateCodes;

typedef enum {
  // output of the state functions and if
  // the task is accomplished
  PASS,
  FAIL
} stateReturnCodes;

typedef struct {
  // define each transition for the state diagram
  stateCodes source;
  stateReturnCodes output;
  stateCodes dest;
} transition;

transition stateTransitions[] = {
  // transitions of the finite state machine
  // defined by the state diagram

  // if the current state is the first element 
  // and the return code is the second element,
  // change the state code to the third element
  {START, FAIL, STOP},
  {START, PASS, SEARCH},
  {SEARCH, FAIL, SEARCH},
  {SEARCH, PASS, ATTACK},
  {ATTACK, FAIL, SEARCH},
  {ATTACK, PASS, ATTACK}
}

// lookup function for the transitions of the state machine
stateCodes lookupTransitions(stateCodes currentState, stateReturnCodes returnCode);

#endif