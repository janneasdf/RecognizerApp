#include "UDPServerSession.h"

/* �R���X�g���N�^ */
UDPServerSession::UDPServerSession(UDPsocket socket, UDPpacket *packet){
	this->socket = socket;
	this->packet = packet;
} // Network

/* �f�X�g���N�^ */
UDPServerSession::~UDPServerSession(){	
	SDLNet_UDP_Close(socket);
	SDLNet_FreePacket(packet);
} // Network

/********************************************************************
											���b�Z�[�W�̑��M
 ********************************************************************/
int UDPServerSession::receiveMessage(void *receiveDataPtr, Uint32 length){

	int numRecv;
	numRecv = SDLNet_UDP_Recv(socket, packet);

	/* ��M�Ȃ� */
	if ( numRecv == 0 ){
		return 0;
	
	/* �G���[ */
	}else if ( numRecv == -1 ){
		printf("��M�Ɏ��s���܂����B");
		return 0;
	}

	memcpy(receiveDataPtr, packet->data, length);

	return 1;
} // receiveMessage
