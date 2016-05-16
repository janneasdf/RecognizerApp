#include "AccelerometerCalibrator.h"

AccelerometerCalibrator::AccelerometerCalibrator(){}

AccelerometerCalibrator::~AccelerometerCalibrator(){}

/* ?t?@?C???????????? */
int AccelerometerCalibrator::createCalibrationDataFromFile(const char *filename, SensorOffsetData *dstCalibrationData){
    char lineBuffer[64];
    fstream offsetConfigFile(filename, ios::in);
    if ( offsetConfigFile.fail() ){
        printf("?????x?Z???T??L?????u???[?V?????t?@?C???????????????????: %d\n", filename);
        return -1;
    }
    offsetConfigFile.getline(lineBuffer, 64);
    _snscanf(lineBuffer, 64, "%f %f %f %f", &calibrationData.accelerationOffset.x, &calibrationData.accelerationOffset.y, &calibrationData.accelerationOffset.z, &calibrationData.gravityAccelerationOffset);
    printf("?????x?Z???T??L?????u???[?V?????f?[?^????????????:\n\tOffset(%03.02f %03.02f %03.02f)\tGravity: %03.02f\n", calibrationData.accelerationOffset.x, calibrationData.accelerationOffset.y, calibrationData.accelerationOffset.z, calibrationData.gravityAccelerationOffset);
    offsetConfigFile.close();
    dstCalibrationData->accelerationOffset.x = calibrationData.accelerationOffset.x;
    dstCalibrationData->accelerationOffset.y = calibrationData.accelerationOffset.y;
    dstCalibrationData->accelerationOffset.z = calibrationData.accelerationOffset.z;
    dstCalibrationData->gravityAccelerationOffset = calibrationData.gravityAccelerationOffset;
    isInitialized = 1;
    return 0;
} // createCalibrationDataFromFile

/* ?t?@?C?????????? */
int AccelerometerCalibrator::saveCalibrationDataToFile(const char *filename){
    if ( !isInitialized ){
        printf("?L?????u???[?V?????f?[?^?????????????????????B\n");
        return -1;
    }

    fstream offsetConfigFile(filename, ios::out);
    offsetConfigFile
        << calibrationData.accelerationOffset.x << ' '
        << calibrationData.accelerationOffset.y << ' '
        << calibrationData.accelerationOffset.z << ' '
        << calibrationData.gravityAccelerationOffset << endl;
    offsetConfigFile.close();

    printf("?????x?Z???T??L?????u???[?V?????t?@?C??????????????: %s\n", filename);

    return 0;
} // saveCalibrationDataToFile

/* ?L?????u???[?V?????f?[?^??Z?b?g */
void AccelerometerCalibrator::setCalibrationData(SensorOffsetData srcCalibrationData){
    calibrationData.accelerationOffset = srcCalibrationData.accelerationOffset;
    calibrationData.gravityAccelerationOffset = srcCalibrationData.gravityAccelerationOffset;
} // setCalibrationData
