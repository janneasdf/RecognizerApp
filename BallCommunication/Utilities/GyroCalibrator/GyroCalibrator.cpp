#include "GyroCalibrator.h"

GyroCalibrator::GyroCalibrator(){}

GyroCalibrator::~GyroCalibrator(){}

/* �t�@�C������ǂݍ��� */
int GyroCalibrator::createCalibrationDataFromFile(const char *filename, SensorOffsetData *dstCalibrationData){
	char lineBuffer[64];
	fstream offsetConfigFile(filename, ios::in);
	if ( offsetConfigFile.fail() ){
		printf("�W���C���Z���T�̃L�����u���[�V�����t�@�C�����ǂݍ��߂܂���ł���: %d\n", filename);
		return -1;
	}
	offsetConfigFile.getline(lineBuffer, 64);
	_snscanf(lineBuffer, 64, "%f %f %f", &calibrationData.gyroOffset.x, &calibrationData.gyroOffset.y, &calibrationData.gyroOffset.z);
	printf("�W���C���Z���T�̃L�����u���[�V�����f�[�^��ǂݍ��݂܂���:\n\tOffset(%03.02f %03.02f %03.02f)\n", calibrationData.gyroOffset.x, calibrationData.gyroOffset.y, calibrationData.gyroOffset.z);
	offsetConfigFile.close();
	dstCalibrationData->gyroOffset.x = calibrationData.gyroOffset.x;
	dstCalibrationData->gyroOffset.y = calibrationData.gyroOffset.y;
	dstCalibrationData->gyroOffset.z = calibrationData.gyroOffset.z;
	isInitialized = 1;
	return 0;
} // createCalibrationDataFromFile

/* �t�@�C���ɕۑ����� */
int GyroCalibrator::saveCalibrationDataToFile(const char *filename){
	if ( !isInitialized ){
		printf("�L�����u���[�V�����f�[�^������������Ă��܂���B\n");
		return -1;
	}

	fstream offsetConfigFile(filename, ios::out);
	offsetConfigFile 
		<< calibrationData.gyroOffset.x << ' ' 
		<< calibrationData.gyroOffset.y << ' ' 
		<< calibrationData.gyroOffset.z << endl;
	offsetConfigFile.close();

	printf("�W���C���Z���T�̃L�����u���[�V�����t�@�C����ۑ����܂���: %s\n", filename);

	return 0;
} // saveCalibrationDataToFile
	
/* �L�����u���[�V�����f�[�^�̃Z�b�g */
void GyroCalibrator::setCalibrationData(SensorOffsetData srcCalibrationData){
	calibrationData.gyroOffset = srcCalibrationData.gyroOffset;
} // setCalibrationData