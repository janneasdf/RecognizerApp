/*********************************************************************
	UDPServerSessionクラス			「UDPServerSession.h」

	概要:
		UDPソケット通信クラスのサーバ部分

	Date:
		Created: 2009/02/02	By でん
 *********************************************************************/

#ifndef __UDPSERVERSESSION_H__
#define __UDPSERVERSESSION_H__

#include "../../Libraries/SDL/include/SDL.h"
#include "../../Libraries/SDL/include/SDL_net.h"

class UDPServerSession{

public:

	/* コンストラクタ */
	UDPServerSession(UDPsocket socket, UDPpacket *packet);

	/* デストラクタ */
	virtual ~UDPServerSession();

	/********************************************************************
												メッセージの送信
	 ********************************************************************/
	int receiveMessage(void *receiveDataPtr, Uint32 length);
	
protected:
	
	UDPsocket socket;
	UDPpacket *packet;

};
#endif
