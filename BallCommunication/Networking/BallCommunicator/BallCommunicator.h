/**************************************************************************
		ボール通信クラス				「BallCommunicator.h」
		Created 2013.03.06 by 佐藤俊樹
		概要:
			ボールとのシリアル通信を行う。
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

	/* 初期化 */
	virtual int initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut);

	/* 開放 */
	virtual void finalize();

	/* 送信処理 */
    virtual int receiveRawBallData(string& errorMessage);

	/* ボールデータの受け取り */
	virtual RawBallData getRawBallData();

	/* ボールデータの受け取り */
	virtual ProcessedBallData getProcessedBallData();

	/* 全てのボールを停止状態にする */
	virtual void stopAllBalls();

	/* IDを指定して使用するボールを選択する */
	virtual void selectBall(int ballID);

	/* 使用中のボールを調べる */
	virtual int getCurrentBallID();

protected:

	RS232c *rs232c;

	RawBallData receivedRawBallData;
	ProcessedBallData processedBallData;
	int currentBallID;

	ULONGLONG illegalPacketCounter;

};

#endif
