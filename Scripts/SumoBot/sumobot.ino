#include <Hummingbird.h>
#include "state_machine.h"
#include "sensor_sumo.h"
#include "utils_sumo.h"

Hummingbird hummingbird;

// ==== DECLARE SENSORS ====
Sensor distanceSensor;
Sensor lightSensor;
// =========================

// ==== DECLARE STATE MACHINE VARIABLES ===
stateCodes currentState; // Holds the current state
stateReturnCodes currentStateReturn; // Holds return value of current state once the stateFunc has executed
int (* stateFunc)(void); // Holds current state function
int (*state[])(void) = {entryState, exitState}; // Holds all state functions
// ========================================


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
