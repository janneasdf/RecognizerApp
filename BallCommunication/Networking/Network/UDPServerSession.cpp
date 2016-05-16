#include "UDPServerSession.h"

/* コンストラクタ */
UDPServerSession::UDPServerSession(UDPsocket socket, UDPpacket *packet){
	this->socket = socket;
	this->packet = packet;
} // Network

/* デストラクタ */
UDPServerSession::~UDPServerSession(){	
	SDLNet_UDP_Close(socket);
	SDLNet_FreePacket(packet);
} // Network

/********************************************************************
											メッセージの送信
 ********************************************************************/
int UDPServerSession::receiveMessage(void *receiveDataPtr, Uint32 length){

	int numRecv;
	numRecv = SDLNet_UDP_Recv(socket, packet);

	/* 受信なし */
	if ( numRecv == 0 ){
		return 0;
	
	/* エラー */
	}else if ( numRecv == -1 ){
		printf("受信に失敗しました。");
		return 0;
	}

	memcpy(receiveDataPtr, packet->data, length);

	return 1;
} // receiveMessage
