/**************************************************************************
		ボール通信クラスUDP版				「BallCommunicator_UDP.h」
		Created 2015.04.06 by 佐藤俊樹
		概要:
			ボールとのUDP通信を行う。
 **************************************************************************/
#pragma once

#include "BallCommunicator.h"

#include "../Network/Network.h"

class BallCommunicatorUDP : public BallCommunicator{

public:

	BallCommunicatorUDP();
	virtual ~BallCommunicatorUDP();

	/* 初期化 */
	virtual int initialize(const char *portName, int baudRate, int readTimeOut, int writeTimeOut);		// rs232cはUDP版では未対応
	virtual int initialize(int portNo);

	/* 開放 */
	virtual void finalize();

	/* 送信処理 */
	virtual int receiveRawBallData();

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

	UDPServerSession *udpServer;

};
