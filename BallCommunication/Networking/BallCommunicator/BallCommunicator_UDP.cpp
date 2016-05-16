#include "BallCommunicator_UDP.h"

BallCommunicatorUDP::BallCommunicatorUDP(){
	timer = Timer::getInstance();
	receivedRawBallData.ballID = -1;
}

BallCommunicatorUDP::~BallCommunicatorUDP(){}

/* 初期化 */
int BallCommunicatorUDP::initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut){
	printf("UDP版ではRS232Cでの通信方法は未対応です。\n");
	return -1;
}

int BallCommunicatorUDP::initialize(int portNo){

	/* RS232C初期化 */
	udpServer = Network::createUDPServerSession(portNo);
	if ( udpServer == NULL ){
		printf("UDP通信の初期化に失敗しました。\n");
		return -1;
	}

	memset(&receivedRawBallData, 0, sizeof(RawBallData));
	memset(&processedBallData, 0, sizeof(ProcessedBallData));

	return 0;
	
} // initialize

/* 開放 */
void BallCommunicatorUDP::finalize(){
	
	/* 全てのボールを停止状態にする */
	//stopAllBalls();
	SDL_Delay(50);

	delete udpServer;
	
} // finalize

/* 送信処理 */
int BallCommunicatorUDP::receiveRawBallData(){ 

	char receiveBuffer[128];			// 十分なサイズ
	int isReceived = 0;

	while ( udpServer->receiveMessage(receiveBuffer, 48) ){

		//receivedRawBallData.photoSensor1 = *((int*)&receiveBuffer[0]);
		//receivedRawBallData.pressure = (float)*((int*)&receiveBuffer[4]);
		//receivedRawBallData.micValue = *((float*)&receiveBuffer[8]);

		receivedRawBallData.acceleration.x = *((float*)&receiveBuffer[12]);
		receivedRawBallData.acceleration.y = *((float*)&receiveBuffer[16]);
		receivedRawBallData.acceleration.z = *((float*)&receiveBuffer[20]);

		receivedRawBallData.compass.x = *((float*)&receiveBuffer[24]);
		receivedRawBallData.compass.y = *((float*)&receiveBuffer[28]);
		receivedRawBallData.compass.z = *((float*)&receiveBuffer[32]);

		receivedRawBallData.gyro.x = *((float*)&receiveBuffer[36]);
		receivedRawBallData.gyro.y = *((float*)&receiveBuffer[40]);
		receivedRawBallData.gyro.z = *((float*)&receiveBuffer[44]);
		isReceived = 1;
	
	} // while
	
	return isReceived;
} // receiveRawBallData

/* ボールデータの受け取り */
RawBallData BallCommunicatorUDP::getRawBallData(){
	return receivedRawBallData;
} // getRawBallData

/* ボールデータの受け取り */
ProcessedBallData BallCommunicatorUDP::getProcessedBallData(){
	return processedBallData;
} // getProcessedBallData

/* 全てのボールを停止状態にする */
void BallCommunicatorUDP::stopAllBalls(){
	//char sendBuffer[7];
	//sendBuffer[0] = 'E';	sendBuffer[1] = 1;	sendBuffer[2] = 'E';	sendBuffer[3] = 2;	sendBuffer[4] = 'E';	sendBuffer[5] = 3;	sendBuffer[6] = 'e';
	//rs232c->send(sendBuffer, 7);
	//currentBallID = -1;
} // stopAllBalls

/* IDを指定して使用するボールを選択する */
void BallCommunicatorUDP::selectBall(int ballID){
	//stopAllBalls();		// 一端全てのボールを停止させる
	//currentBallID = -1;
	//currentBallID = ballID;
	//char sendBuffer[3];
	//sendBuffer[0] = 'B';	sendBuffer[1] = ballID;	sendBuffer[2] = 'e';
	//rs232c->send(sendBuffer, 3);
} // selectBall

/* 使用中のボールを調べる */
int BallCommunicatorUDP::getCurrentBallID(){
	return currentBallID;
} // getCurrentBallID