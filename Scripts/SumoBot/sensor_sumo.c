#include "sensor_sumo.h"

void initSensor(Sensor *s, char pin, int min, int max) {
    // Initialize Sensor structure with builtin rolling average for low pass filter effects
    // to remove high frequency noise
    for (int i=0; i < BUFFER_SIZE; i++) { // could use memset() from <string.h>
        s->buffer[i] = 0;
    }
    s->sum = 0;
    s->bp = 0;
    s->avg = 0;
    s->min = min; // Minimum range to map
    s->max = max; // Maximum range to map
    s->pin = pin; // Pin number the sensor is attached to. Uses Hummingbird conventions
}

void updateRunningAverage(Sensor *s, int newValue) {
  int index = s->bp;

  s->sum -= s->buffer[index]; // Subtract current index from sum
  s->buffer[index] = newValue; // Add new value to buffer (while deleting the old one)
  s->sum += newValue; // Add new value to sum
  s->bp = (s->bp + 1) % BUFFER_SIZE; // Go to next index
  s->avg = s->sum / BUFFER_SIZE; // Update average

  s->avg = MAP(s->avg, s->min, s->max, 0, 100);
}
