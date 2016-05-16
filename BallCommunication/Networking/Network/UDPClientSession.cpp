#include "UDPClientSession.h"

/* �R���X�g���N�^ */
UDPClientSession::UDPClientSession(UDPsocket socket, UDPpacket *packet){
	this->socket = socket;
	this->packet = packet;
} // Network

/* �f�X�g���N�^ */
UDPClientSession::~UDPClientSession(){
	SDLNet_UDP_Close(socket);
	SDLNet_FreePacket(packet);
} // Network

/********************************************************************
											���b�Z�[�W�̑��M
 ********************************************************************/
int UDPClientSession::sendMessage(void *sendDataPtr, Uint32 length){

	packet->len = length;
	memcpy(packet->data, sendDataPtr, length);

	if ( !SDLNet_UDP_Send(socket, 0, packet) ){
		printf("UDP�p�P�b�g�̑��M�Ɏ��s���܂���: %s\n", SDLNet_GetError());
		return 0;
	}

	return 1;
} // sendMessage
