#ifndef STATE_MACHINE_SENSOR    // include guard
#define STATE_MCAHINE_SENSOR    // #func is called  
                                // preprocessor instructions
// include guards are used to prevent the processor
// from defining multiple header files
#include <Arduino.h>

#define BUFFER_SIZE 10
#define MAP(N, MIN, MAX, NMIN, NMAX) (N-MIN) * (NMAX-NMIN) / (MAX-MIN) + NMIN

typedef struct {
    int buffer[BUFFER_SIZE];
    int sum;
    int bp;
    int avg;
    int min;
    int max;
    char pin;
    bool normS;
} Sensor;

typedef enum {
    ENTRY,
    ESCAPE
} stateCodes;

typedef enum {
    OK,
    FAIL,
    REPEAT
} stateReturnCodes;

typedef struct {
    stateCodes src;
    stateReturnCodes ret;
    stateCodes dst;
} transition;

void initSensor(Sensor *s, char pin, int min, int max, bool normS);
void updateRunningAverage(Sensor *s, int newValue);

#endif