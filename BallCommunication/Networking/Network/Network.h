/*********************************************************************
	Networkクラス			「Network.h」

	概要:
		udpソケット通信クラス

	Date:
		Created: 2009/02/02	By でん
 *********************************************************************/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdlib.h>
#include <stdio.h>

#include "../../Libraries/SDL/include/SDL.h"
#include "../../Libraries/SDL/include/SDL_net.h"

#include "UDPClientSession.h"
#include "UDPServerSession.h"

class Network{

public:

	/********************************************************************
													初期化 / 解放
	 ********************************************************************/
	/* 初期化 */
	static int initialize();

	/* 解放 */
	static void finalize();

	/********************************************************************
													UDPセッションの作成
	 ********************************************************************/
	/* クライアント(送信側) */
	static UDPClientSession *createUDPClientSession(const char *ipAddr, int portNo, int packetSize = 1024);
	
	/* サーバ(受信側) */
	static UDPServerSession *createUDPServerSession(int portNo, int packetSize = 1024);

protected:

};
#endif
