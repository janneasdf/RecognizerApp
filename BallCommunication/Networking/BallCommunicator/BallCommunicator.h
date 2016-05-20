/**************************************************************************
		�{�[���ʐM�N���X				�uBallCommunicator.h�v
		Created 2013.03.06 by �����r��
		�T�v:
			�{�[���Ƃ̃V���A���ʐM���s���B
 **************************************************************************/
#ifndef __BALL_COMMUNICATOR_H__
#define __BALL_COMMUNICATOR_H__

#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

#include "../../declaration.h"
#include <string>

#include "../RS232C/RS232c.h"
#include "../Timer/Timer.h"

class BallCommunicator{

public:

	BallCommunicator();
	virtual ~BallCommunicator();

	/* ������ */
	virtual int initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut);

	/* �J�� */
	virtual void finalize();

	/* ���M���� */
    virtual int receiveRawBallData(string& errorMessage);

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

	RS232c *rs232c;

	RawBallData receivedRawBallData;
	ProcessedBallData processedBallData;
	int currentBallID;

	ULONGLONG illegalPacketCounter;

};

#endif
