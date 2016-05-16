#include "Network.h"

/********************************************************************
												������ / ���
 ********************************************************************/

/* ������ */
int Network::initialize(){
	if ( SDLNet_Init() < 0 ){
		printf("SDL_net�̏������Ɏ��s: %s\n",SDLNet_GetError());
		return -1;
	}
	return 0;
} // initialize

/* ��� */
void Network::finalize(){
	SDLNet_Quit();
} // finalize

/********************************************************************
												UDP�Z�b�V�����̍쐬
 ********************************************************************/
/* �N���C�A���g(���M��) */
UDPClientSession *Network::createUDPClientSession(const char *ipAddr, int portNo, int packetSize){

	IPaddress ip;
	UDPsocket socket;
	UDPpacket *packet;

	if( SDLNet_ResolveHost(&ip, ipAddr, portNo) == -1 ){
		printf("�z�X�g�̉����Ɏ��s���܂���: ip:%s port:%d: %s\n", ipAddr, portNo, SDLNet_GetError());
		return NULL;
	}
	if( !( socket = SDLNet_UDP_Open(0) ) ){
		printf("UDP�\�P�b�g�̃I�[�v���Ɏ��s���܂���: %s\n", SDLNet_GetError());
		return NULL;
	}
	if( !( packet = SDLNet_AllocPacket(packetSize) ) ){
		printf("�p�P�b�g�̊��蓖�ĂɎ��s���܂���: %s\n", SDLNet_GetError());
		return NULL;
	}
	if( SDLNet_UDP_Bind(socket, 0, &ip) == -1 ){
		printf("�o�C���h�Ɏ��s���܂���: %s\n", SDLNet_GetError());
		return NULL;
	}

	UDPClientSession *newSession = new UDPClientSession(socket, packet);

	return newSession;

} // createUDPClientSession

/* �T�[�o(��M��) */
UDPServerSession *Network::createUDPServerSession(int portNo, int packetSize){

	UDPsocket socket;
	UDPpacket *packet;

	if( !( socket = SDLNet_UDP_Open(portNo) ) ){
		printf("UDP�\�P�b�g�̃I�[�v���Ɏ��s���܂���: %s\n", SDLNet_GetError());
		return NULL;
	}

	if( !( packet = SDLNet_AllocPacket(packetSize) ) ){
		printf("�p�P�b�g�̊��蓖�ĂɎ��s���܂���: %s\n", SDLNet_GetError());
		return NULL;
	}
	packet->channel = 0;

	UDPServerSession *newSession = new UDPServerSession(socket, packet);

	return newSession;

} // createUDPServerSession
