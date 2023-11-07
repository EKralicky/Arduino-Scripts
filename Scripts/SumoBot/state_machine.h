#ifndef STATE_MACHINE
#define STATE_MACHINE

typedef enum {
  START,
  SEARCH,
  ATTACK,
  STOP
} stateCodes;

typedef enum {
  PASS,
  FAIL
} stateReturnCodes;

typedef struct {
  stateCodes source;
  stateReturnCodes output;
  stateCodes dest;
} transition;

transition stateTransitions[] = {
  {START, FAIL, STOP},
  {START, PASS, SEARCH},
  {SEARCH, FAIL, SEARCH},
  {SEARCH, PASS, ATTACK},
  {ATTACK, FAIL, SEARCH},
  {ATTACK, PASS, ATTACK}
}

stateCodes lookupTransitions(stateCodes currentState, stateReturnCodes returnCode);

#endif