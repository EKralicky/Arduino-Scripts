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

#endif