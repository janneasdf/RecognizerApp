#include "BallCommunicator.h"

BallCommunicator::BallCommunicator(){
	timer = Timer::getInstance();
	receivedRawBallData.ballID = -1;
}

BallCommunicator::~BallCommunicator(){}

/* 初期化 */
int BallCommunicator::initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut){

	/* RS232C初期化 */
	rs232c = new RS232c();
	if ( rs232c->connect(portName, baudRate, 512, 512, readTimeOut, writeTimeOut) < 0 ){
		printf("シリアル通信の初期化に失敗しました。\n");
		return -1;
	}

	//currentBallID = -1;
	currentBallID = 0;					// 今のボールにIDはないので、0としておく
	illegalPacketCounter = 0;

	memset(&receivedRawBallData, 0, sizeof(RawBallData));
	memset(&processedBallData, 0, sizeof(ProcessedBallData));

	return 0;
	
} // initialize

/* 開放 */
void BallCommunicator::finalize(){

	printf("受信に失敗したパケットは%llu個ありました。\n", illegalPacketCounter);
	
	/* 全てのボールを停止状態にする */
	stopAllBalls();
	SDL_Delay(50);

	rs232c->disconnect();
	
} // finalize

/* 送信処理 */
int BallCommunicator::receiveRawBallData(){ 

	//unsigned int receivedSize;
	//unsigned char tmpReceiveBuffer[16];		// payload + header/footer character + '\0'
	//receivedSize = rs232c->receive(tmpReceiveBuffer, 15);
	//if ( receivedSize == 15 ){
	//	//printf("%c %c ", tmpReceiveBuffer[0], tmpReceiveBuffer[14]);
	//	tmpReceiveBuffer[15] = '\0';
	//	return 1;
	//}else{
	//	printf("%u ", receivedSize);
	//}

	unsigned char receiveBuffer[128];			// 十分なサイズ
	char headerCharacter;
	int unreceivedSize = PACKET_SIZE_WITHOUT_HEADER;
	int retryCounter = 100000;
	int receivedSize = 0;
	
	/* 1文字ずつ受信し、頭文字'B'を探す */
	do {	
		receivedSize = rs232c->receive(&headerCharacter, 1);
		//retryCounter--;
		//printf("retryCounter: %d", retryCounter);
		if ( --retryCounter <= 0 ){
			printf("Header Timeout\n");
			return -1;
		}
	} while ( receivedSize != 1 || headerCharacter != 'B' );
	
	/* 残りを受信する */
	retryCounter = 100000;
	do{
		receivedSize = rs232c->receive(&receiveBuffer[PACKET_SIZE_WITHOUT_HEADER - unreceivedSize], unreceivedSize);
		unreceivedSize -= receivedSize;
		retryCounter--;
		if ( retryCounter < 0 ){
			printf("Payload Timeout\n");
			return -1;
		}
	} while ( unreceivedSize > 0 );

	/* 頭とお尻に'B'及び'E'があれば正しく受信できているとみなし、構造体に変換 */
	if ( receiveBuffer[PACKET_SIZE_WITHOUT_HEADER - 1] == 'E' ){

		receivedRawBallData.acceleration.x = ((int)(receiveBuffer[0] << 24 | receiveBuffer[1] << 16)) >> 16;
		receivedRawBallData.acceleration.y = ((int)(receiveBuffer[2] << 24 | receiveBuffer[3] << 16)) >> 16;
		receivedRawBallData.acceleration.z = ((int)(receiveBuffer[4] << 24 | receiveBuffer[5] << 16)) >> 16;
		receivedRawBallData.gyro.x = ((int)(receiveBuffer[6] << 24 | receiveBuffer[7] << 16)) >> 16;
		receivedRawBallData.gyro.y = ((int)(receiveBuffer[8] << 24 | receiveBuffer[9] << 16)) >> 16;
		receivedRawBallData.gyro.z = ((int)(receiveBuffer[10] << 24 | receiveBuffer[11] << 16)) >> 16;
		receivedRawBallData.compass.x = ((int)(receiveBuffer[12] << 24 | receiveBuffer[13] << 16)) >> 16;
		receivedRawBallData.compass.y = ((int)(receiveBuffer[14] << 24 | receiveBuffer[15] << 16)) >> 16;
		receivedRawBallData.compass.z = ((int)(receiveBuffer[16] << 24 | receiveBuffer[17] << 16)) >> 16;

		//processedBallData.accelerationXYZ = sqrtf(receivedRawBallData.acceleration.x * receivedRawBallData.acceleration.x
		//	+ receivedRawBallData.acceleration.y * receivedRawBallData.acceleration.y	+ receivedRawBallData.acceleration.z * receivedRawBallData.acceleration.z);
		//processedBallData.compassXYZ = sqrtf(receivedRawBallData.compass.x * receivedRawBallData.compass.x
		//	+ receivedRawBallData.compass.y * receivedRawBallData.compass.y	+ receivedRawBallData.compass.z * receivedRawBallData.compass.z);
		//processedBallData.gyroXYZ = sqrtf(receivedRawBallData.gyro.x * receivedRawBallData.gyro.x
		//	+ receivedRawBallData.gyro.y * receivedRawBallData.gyro.y	+ receivedRawBallData.gyro.z * receivedRawBallData.compass.z);

		//receivedRawBallData.capacitiveData[0] = receiveBuffer[0] + (receiveBuffer[1] << 8);
		//receivedRawBallData.capacitiveData[1] = receiveBuffer[2] + (receiveBuffer[3] << 8);
		//receivedRawBallData.capacitiveData[2] = receiveBuffer[4] + (receiveBuffer[5] << 8);
		//receivedRawBallData.capacitiveData[3] = receiveBuffer[6] + (receiveBuffer[7] << 8);

		//receivedRawBallData.baselineData[0] = (unsigned int)receiveBuffer[8] * 4;
		//receivedRawBallData.baselineData[1] = (unsigned int)receiveBuffer[9] * 4;
		//receivedRawBallData.baselineData[2] = (unsigned int)receiveBuffer[10] * 4;
		//receivedRawBallData.baselineData[3] = (unsigned int)receiveBuffer[11] * 4;

		//receivedRawBallData.touchResult[0] = (unsigned int)receiveBuffer[18] & 0x01;
		//receivedRawBallData.touchResult[1] = ((unsigned int)receiveBuffer[18] >> 1) & 0x01;
		//receivedRawBallData.touchResult[2] = ((unsigned int)receiveBuffer[18] >> 2) & 0x01;
		//receivedRawBallData.touchResult[3] = ((unsigned int)receiveBuffer[18] >> 3) & 0x01;
		//receivedRawBallData.touchResult[4] = ((unsigned int)receiveBuffer[18] >> 4) & 0x01;
		//receivedRawBallData.touchResult[5] = ((unsigned int)receiveBuffer[18] >> 5) & 0x01;
		//receivedRawBallData.touchResult[6] = ((unsigned int)receiveBuffer[18] >> 6) & 0x01;
		//receivedRawBallData.touchResult[7] = ((unsigned int)receiveBuffer[18] >> 7) & 0x01;
		//receivedRawBallData.touchResult[8] = (unsigned int)receiveBuffer[19] & 0x01;
		//receivedRawBallData.touchResult[9] = ((unsigned int)receiveBuffer[19] >> 1) & 0x01;
		//receivedRawBallData.touchResult[10] = ((unsigned int)receiveBuffer[19] >> 2) & 0x01;
		//receivedRawBallData.touchResult[11] = ((unsigned int)receiveBuffer[19] >> 3) & 0x01;

		//receivedRawBallData.touchResult[12] = (unsigned int)receiveBuffer[20] & 0x01;
		//receivedRawBallData.touchResult[13] = ((unsigned int)receiveBuffer[20] >> 1) & 0x01;
		//receivedRawBallData.touchResult[14] = ((unsigned int)receiveBuffer[20] >> 2) & 0x01;
		//receivedRawBallData.touchResult[15] = ((unsigned int)receiveBuffer[20] >> 3) & 0x01;
		//receivedRawBallData.touchResult[16] = ((unsigned int)receiveBuffer[20] >> 4) & 0x01;
		//receivedRawBallData.touchResult[17] = ((unsigned int)receiveBuffer[20] >> 5) & 0x01;
		//receivedRawBallData.touchResult[18] = ((unsigned int)receiveBuffer[20] >> 6) & 0x01;
		//receivedRawBallData.touchResult[19] = ((unsigned int)receiveBuffer[20] >> 7) & 0x01;
		//receivedRawBallData.touchResult[20] = (unsigned int)receiveBuffer[21] & 0x01;
		//receivedRawBallData.touchResult[21] = ((unsigned int)receiveBuffer[21] >> 1) & 0x01;
		//receivedRawBallData.touchResult[22] = ((unsigned int)receiveBuffer[21] >> 2) & 0x01;
		//receivedRawBallData.touchResult[23] = ((unsigned int)receiveBuffer[21] >> 3) & 0x01;

		//receivedRawBallData.touchResult[24] = (unsigned int)receiveBuffer[22] & 0x01;
		//receivedRawBallData.touchResult[25] = ((unsigned int)receiveBuffer[22] >> 1) & 0x01;
		//receivedRawBallData.touchResult[26] = ((unsigned int)receiveBuffer[22] >> 2) & 0x01;
		//receivedRawBallData.touchResult[27] = ((unsigned int)receiveBuffer[22] >> 3) & 0x01;
		//receivedRawBallData.touchResult[28] = ((unsigned int)receiveBuffer[22] >> 4) & 0x01;
		//receivedRawBallData.touchResult[29] = ((unsigned int)receiveBuffer[22] >> 5) & 0x01;
		//receivedRawBallData.touchResult[30] = ((unsigned int)receiveBuffer[22] >> 6) & 0x01;
		//receivedRawBallData.touchResult[31] = ((unsigned int)receiveBuffer[22] >> 7) & 0x01;
		//receivedRawBallData.touchResult[32] = (unsigned int)receiveBuffer[23] & 0x01;
		//receivedRawBallData.touchResult[33] = ((unsigned int)receiveBuffer[23] >> 1) & 0x01;
		//receivedRawBallData.touchResult[34] = ((unsigned int)receiveBuffer[23] >> 2) & 0x01;
		//receivedRawBallData.touchResult[35] = ((unsigned int)receiveBuffer[23] >> 3) & 0x01;

		//printf("G:%04.01f %04.01f %04.01f\tA1:%04.01f %04.01f %04.01f\n",
		//	receivedRawBallData.gyro.x, receivedRawBallData.gyro.y, receivedRawBallData.gyro.z,
		//	receivedRawBallData.acceleration.x, receivedRawBallData.acceleration.y, receivedRawBallData.acceleration.z);
		return 1;
		//printf("%03.02f\n", receivedRawBallData.micValue);

	}else{

		illegalPacketCounter++;
		printf("Irregular Packet is Skipped\n");
		return -1;
	}

	//printf("接続されていません。\n");
	return 0;
} // receiveRawBallData

/* ボールデータの受け取り */
RawBallData BallCommunicator::getRawBallData(){
	return receivedRawBallData;
} // getRawBallData

/* ボールデータの受け取り */
ProcessedBallData BallCommunicator::getProcessedBallData(){
	return processedBallData;
} // getProcessedBallData

/* 全てのボールを停止状態にする */
void BallCommunicator::stopAllBalls(){
	char sendBuffer[7];
	sendBuffer[0] = 'E';	sendBuffer[1] = 1;	sendBuffer[2] = 'E';	
	sendBuffer[3] = 2;	sendBuffer[4] = 'E';	sendBuffer[5] = 3;	sendBuffer[6] = 'e';
	rs232c->send(sendBuffer, 7);
	currentBallID = -1;
} // stopAllBalls

/* IDを指定して使用するボールを選択する */
void BallCommunicator::selectBall(int ballID){
	stopAllBalls();		// 一端全てのボールを停止させる
	currentBallID = -1;
	currentBallID = ballID;
	char sendBuffer[3];
	sendBuffer[0] = 'B';	sendBuffer[1] = ballID;	sendBuffer[2] = 'e';
	rs232c->send(sendBuffer, 3);
} // selectBall

/* 使用中のボールを調べる */
int BallCommunicator::getCurrentBallID(){
	return currentBallID;
} // getCurrentBallID