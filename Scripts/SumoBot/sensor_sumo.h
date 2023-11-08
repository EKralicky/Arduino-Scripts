#ifndef SENSOR_SUMO
#define SENSOR_SUMO

#define BUFFER_SIZE 10
#define LIGHT_SENSOR_THRESHOLD 30
#define DISTANCE_SENSOR_THRESHOLD 30

typedef struct {
  int buffer[BUFFER_SIZE]; // Holds data for running average
  int sum; // Current total sum of the running average
  int bp; // Current buffer position in the buffer
  int avg; // Current average value of the sensor
  int min;
  int max;
  int pin;
} Sensor;

void initSensor(Sensor *s, char pin, int min, int max); // Initialize Sensor structure
void updateRunningAverage(Sensor *s, int newValue); // Update running average, called once per clock cycle

#endif
