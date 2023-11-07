#include <Hummingbird.h>
Hummingbird hummingbird;

/*
Initialize Hummingbird ports
*/


typedef enum {
  ENTRY,
  ESCAPE
} stateCodes;

// State return codes. Once the state function has executed, return one of these codes
typedef enum {
  OK,
  FAIL,
  REPEAT
} stateReturnCodes;

// Defines the structure of transitions. e.g. src, return, dst.
// e.g. If 'src' returns 'return' go to 'dst'
typedef struct {
  stateCodes src;
  stateReturnCodes ret;
  stateCodes dst;
} transition;

void initSensor(Sensor* s) {
  // Initialize all elements of the ra buffer to 0
  for (int i = 0; i < BUFFER_SIZE; i++) {
    s->buffer[i] = 0;
  }
  s->sum = 0;
  s->bp = 0;
  s->avg = 0;
}

void updateRunningAverage(Sensor* s, int newValue) {
  int index = s->bp;

  s->sum -= s->buffer[index]; // Subtract current index from sum
  s->buffer[index] = newValue; // Add new value to buffer (while deleting the old one)
  s->sum += newValue; // Add new value to sum
  s->bp = (s->bp + 1) % BUFFER_SIZE; // Go to next index
  s->avg = s->sum / BUFFER_SIZE; // Update average
}

// ==== DECLARE SENSORS ====
Sensor distanceSensor;
Sensor lightSensor;
// =========================

// // STATE FUNCTIONS

// int entryState() { // Program start
//   hummingbird.setMotor(1, 255);
//   hummingbird.setMotor(2, 255);
//   Serial.println("ENTRY");
//   return OK;
// }

// int exitState() { // Program end
//   delay(1000);
//   hummingbird.setMotor(1, -255);
//   hummingbird.setMotor(2, -255);
//   Serial.println("EXIT");
//   return REPEAT;
// }

// int searchState() {
//   return 1;
// }

// int attackState() {
//   return 1;
// }

// int recoveryState() {
//  return 1;
// }


// END STATE FUNCTIONS

int (*state[])(void) = {entryState, exitState};

// Define state transitions
transition stateTransitions[] = {
  {ENTRY, REPEAT, ENTRY},
  {ENTRY, OK, ESCAPE}
};

stateCodes lookupTransitions(stateCodes currentState, stateReturnCodes returnCode) {
  int length = GET_LENGTH(stateTransitions);
  for (int i = 0; i < length; i++) {
    transition t = stateTransitions[i];
    if ((t.src == currentState) && (t.ret == returnCode)) {
      return t.dst;
    } 
  }
  Serial.write("Undefined state or state");
  return ESCAPE;
}

// Global vars
stateCodes currentState; // Holds the current state
stateReturnCodes currentStateReturn; // Holds return value of current state once the stateFunc has executed
int (* stateFunc)(void); // Holds current state function

void setup()
{
  Serial.begin(9600);
  hummingbird.init();

  // ==== INIT SENSORS ====
  initSensor(&distanceSensor);
  initSensor(&lightSensor);
  // ======================

  currentState = ENTRY;
}

void loop()
{

  // Update sensor values
  updateRunningAverage(&distanceSensor, hummingbird.readSensorValue(0));
  updateRunningAverage(&lightSensor, hummingbird.readSensorValue(1));

  Serial.println()

  // Run state machine
  Serial.write(currentState);
  stateFunc = state[currentState];
  currentStateReturn = stateFunc();

  if (currentState == ESCAPE) {
    return;
  }

  currentState = lookupTransitions(currentState, currentStateReturn);
  

  // Moves the servos in a cascading sequence

  delay(50); //delay by 50 ms
}
