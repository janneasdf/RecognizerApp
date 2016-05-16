#include "UDPClientSession.h"

/* コンストラクタ */
UDPClientSession::UDPClientSession(UDPsocket socket, UDPpacket *packet){
	this->socket = socket;
	this->packet = packet;
} // Network

/* デストラクタ */
UDPClientSession::~UDPClientSession(){
	SDLNet_UDP_Close(socket);
	SDLNet_FreePacket(packet);
} // Network

/********************************************************************
											メッセージの送信
 ********************************************************************/
int UDPClientSession::sendMessage(void *sendDataPtr, Uint32 length){

	packet->len = length;
	memcpy(packet->data, sendDataPtr, length);

	if ( !SDLNet_UDP_Send(socket, 0, packet) ){
		printf("UDPパケットの送信に失敗しました: %s\n", SDLNet_GetError());
		return 0;
	}

	return 1;
} // sendMessage
