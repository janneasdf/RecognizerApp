/*********************************************************************
	UDPClientSessionクラス			「UDPClientSession.h」

	概要:
		UDPソケット通信クラスのクライアント部分

	Date:
		Created: 2009/02/02	By でん
 *********************************************************************/

#ifndef __UDPCLIENTSESSION_H__
#define __UDPCLIENTSESSION_H__

#include "../../Libraries/SDL/include/SDL.h"
#include "../../Libraries/SDL/include/SDL_net.h"

class UDPClientSession{

public:

	/* コンストラクタ */
	UDPClientSession(UDPsocket socket, UDPpacket *packet);

	/* デストラクタ */
	virtual ~UDPClientSession();

	/********************************************************************
												メッセージの送信
	 ********************************************************************/
	int sendMessage(void *sendDataPtr, Uint32 length);
	
protected:
	
	UDPsocket socket;
	UDPpacket *packet;

};
#endif
