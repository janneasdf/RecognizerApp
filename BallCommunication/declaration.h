#pragma once

/* RS232Cパケットサイズ */
static const int ESB_PACKET_SIZE = 18;
static const int PACKET_SIZE = (ESB_PACKET_SIZE) + 2;								// 頭・終端文字を含む1パケットサイズ
static const int PACKET_SIZE_WITHOUT_HEADER = (PACKET_SIZE - 1);		// ヘッダ文字を除いたパケットサイズ

/* 2次元ベクトル */
typedef struct{
	float x;
	float y;
} Vector2f;

/* 3次元ベクトル */
typedef struct{
	float x;
	float y;
	float z;
} Vector3f;

static const int MAX_ELECTRODES = 32;

/* ボールのデータ */
typedef struct{
	char ballID;
	Vector3f gyro;			// ジャイロセンサの分解能は16bit
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

/* 加速度センサキャリブレーションデータ */
typedef struct{
	Vector3f accelerationOffset;	// 各軸の無負荷時のセンサ値
	Vector3f compassOffset;	// 各軸の無負荷時のセンサ値
	Vector3f gyroOffset;					// 同じくジャイロ
	float gravityAccelerationOffset;		// 重力加速度の測定結果
} SensorOffsetData;

/* グラフの種類 */
typedef enum{
	RESULT_TYPE_UNKNOWN = 0,
	RESULT_TYPE_SENSOR_DATA,
} RESULT_TYPE;
