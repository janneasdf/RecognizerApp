#ifndef SENSORDATAFRAME_H
#define SENSORDATAFRAME_H

typedef struct {
    float timestamp;
    float acceleration;
    float gyro;
} SensorDataFrame;

#endif // SENSORDATAFRAME_H
