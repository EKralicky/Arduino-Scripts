#include "state_machine.h"
#include "UTILS_SUMO.h"

stateCodes lookupTransitions(stateCodes currentState, stateReturnCodes returnCode) {
  // lookup function for the transitions of the state machine.
  // takes the currentState as an input and returns a stateReturnCode (PASS/FAIL)
  int length = GET_LENGTH(stateTransitions);
  for (int i = 0; i < length; i++) {
    // iterate through the all possible states of the finite state machine
    transition t = stateTransitions[i];
    if ((t.source == currentState) && (t.output == returnCode)) {
      // return valid match if exists
      return t.dest;
    } 
  }
  // otherwise, return STOP
  return STOP;
}