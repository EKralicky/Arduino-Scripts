#include "state_machine.h"

stateCodes lookupTransitions(stateCodes currentState, stateReturnCodes returnCode) {
  int length = GET_LENGTH(stateTransitions);
  for (int i = 0; i < length; i++) {
    transition t = stateTransitions[i];
    if ((t.source == currentState) && (t.output == returnCode)) {
      return t.dest;
    } 
  }
  return STOP;
}
