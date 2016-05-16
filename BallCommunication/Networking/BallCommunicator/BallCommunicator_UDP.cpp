#include "BallCommunicator_UDP.h"

BallCommunicatorUDP::BallCommunicatorUDP(){
	timer = Timer::getInstance();
	receivedRawBallData.ballID = -1;
}

BallCommunicatorUDP::~BallCommunicatorUDP(){}

/* ������ */
int BallCommunicatorUDP::initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut){
	printf("UDP�łł�RS232C�ł̒ʐM���@�͖��Ή��ł��B\n");
	return -1;
}

int BallCommunicatorUDP::initialize(int portNo){

	/* RS232C������ */
	udpServer = Network::createUDPServerSession(portNo);
	if ( udpServer == NULL ){
		printf("UDP�ʐM�̏������Ɏ��s���܂����B\n");
		return -1;
	}

	memset(&receivedRawBallData, 0, sizeof(RawBallData));
	memset(&processedBallData, 0, sizeof(ProcessedBallData));

	return 0;
	
} // initialize

/* �J�� */
void BallCommunicatorUDP::finalize(){
	
	/* �S�Ẵ{�[�����~��Ԃɂ��� */
	//stopAllBalls();
	SDL_Delay(50);

	delete udpServer;
	
} // finalize

/* ���M���� */
int BallCommunicatorUDP::receiveRawBallData(){ 

	char receiveBuffer[128];			// �\���ȃT�C�Y
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

/* �{�[���f�[�^�̎󂯎�� */
RawBallData BallCommunicatorUDP::getRawBallData(){
	return receivedRawBallData;
} // getRawBallData

/* �{�[���f�[�^�̎󂯎�� */
ProcessedBallData BallCommunicatorUDP::getProcessedBallData(){
	return processedBallData;
} // getProcessedBallData

/* �S�Ẵ{�[�����~��Ԃɂ��� */
void BallCommunicatorUDP::stopAllBalls(){
	//char sendBuffer[7];
	//sendBuffer[0] = 'E';	sendBuffer[1] = 1;	sendBuffer[2] = 'E';	sendBuffer[3] = 2;	sendBuffer[4] = 'E';	sendBuffer[5] = 3;	sendBuffer[6] = 'e';
	//rs232c->send(sendBuffer, 7);
	//currentBallID = -1;
} // stopAllBalls

/* ID���w�肵�Ďg�p����{�[����I������ */
void BallCommunicatorUDP::selectBall(int ballID){
	//stopAllBalls();		// ��[�S�Ẵ{�[�����~������
	//currentBallID = -1;
	//currentBallID = ballID;
	//char sendBuffer[3];
	//sendBuffer[0] = 'B';	sendBuffer[1] = ballID;	sendBuffer[2] = 'e';
	//rs232c->send(sendBuffer, 3);
} // selectBall

/* �g�p���̃{�[���𒲂ׂ� */
int BallCommunicatorUDP::getCurrentBallID(){
	return currentBallID;
} // getCurrentBallID