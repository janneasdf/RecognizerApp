#pragma once

/* RS232C�p�P�b�g�T�C�Y */
static const int ESB_PACKET_SIZE = 18;
static const int PACKET_SIZE = (ESB_PACKET_SIZE) + 2;								// ���E�I�[�������܂�1�p�P�b�g�T�C�Y
static const int PACKET_SIZE_WITHOUT_HEADER = (PACKET_SIZE - 1);		// �w�b�_�������������p�P�b�g�T�C�Y

/* 2�����x�N�g�� */
typedef struct{
	float x;
	float y;
} Vector2f;

/* 3�����x�N�g�� */
typedef struct{
	float x;
	float y;
	float z;
} Vector3f;

static const int MAX_ELECTRODES = 32;

/* �{�[���̃f�[�^ */
typedef struct{
	char ballID;
	Vector3f gyro;			// �W���C���Z���T�̕���\��16bit
	Vector3f acceleration;
	Vector3f compass;
	//unsigned int capacitiveData[MAX_ELECTRODES];
	//unsigned int baselineData[MAX_ELECTRODES];
	//int touchResult[MAX_ELECTRODES];
	unsigned int t;
} RawBallData;

typedef struct{
	float accelerationXYZ;
	float compassXYZ;
	float accelerationXYZNoG;
	float compassXYZNoG;
	float gyroXYZ;
	unsigned int t;
} ProcessedBallData;

/* �����x�Z���T�L�����u���[�V�����f�[�^ */
typedef struct{
	Vector3f accelerationOffset;	// �e���̖����׎��̃Z���T�l
	Vector3f compassOffset;	// �e���̖����׎��̃Z���T�l
	Vector3f gyroOffset;					// �������W���C��
	float gravityAccelerationOffset;		// �d�͉����x�̑��茋��
} SensorOffsetData;

/* �O���t�̎�� */
typedef enum{
	RESULT_TYPE_UNKNOWN = 0,
	RESULT_TYPE_SENSOR_DATA,
} RESULT_TYPE;
