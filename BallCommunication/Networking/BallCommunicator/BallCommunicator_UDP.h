/**************************************************************************
		�{�[���ʐM�N���XUDP��				�uBallCommunicator_UDP.h�v
		Created 2015.04.06 by �����r��
		�T�v:
			�{�[���Ƃ�UDP�ʐM���s���B
 **************************************************************************/
#pragma once

#include "BallCommunicator.h"

#include "../Network/Network.h"

class BallCommunicatorUDP : public BallCommunicator{

public:

	BallCommunicatorUDP();
	virtual ~BallCommunicatorUDP();

	/* ������ */
	virtual int initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut);		// rs232c��UDP�łł͖��Ή�
	virtual int initialize(int portNo);

	/* �J�� */
	virtual void finalize();

	/* ���M���� */
	virtual int receiveRawBallData();

	/* �{�[���f�[�^�̎󂯎�� */
	virtual RawBallData getRawBallData();

	/* �{�[���f�[�^�̎󂯎�� */
	virtual ProcessedBallData getProcessedBallData();

	/* �S�Ẵ{�[�����~��Ԃɂ��� */
	virtual void stopAllBalls();

	/* ID���w�肵�Ďg�p����{�[����I������ */
	virtual void selectBall(int ballID);

	/* �g�p���̃{�[���𒲂ׂ� */
	virtual int getCurrentBallID();

protected:

	UDPServerSession *udpServer;

};
