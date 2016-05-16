#include "Network.h"

/********************************************************************
												初期化 / 解放
 ********************************************************************/

/* 初期化 */
int Network::initialize(){
	if ( SDLNet_Init() < 0 ){
		printf("SDL_netの初期化に失敗: %s\n",SDLNet_GetError());
		return -1;
	}
	return 0;
} // initialize

/* 解放 */
void Network::finalize(){
	SDLNet_Quit();
} // finalize

/********************************************************************
												UDPセッションの作成
 ********************************************************************/
/* クライアント(送信側) */
UDPClientSession *Network::createUDPClientSession(const char *ipAddr, int portNo, int packetSize){

	IPaddress ip;
	UDPsocket socket;
	UDPpacket *packet;

	if( SDLNet_ResolveHost(&ip, ipAddr, portNo) == -1 ){
		printf("ホストの解決に失敗しました: ip:%s port:%d: %s\n", ipAddr, portNo, SDLNet_GetError());
		return NULL;
	}
	if( !( socket = SDLNet_UDP_Open(0) ) ){
		printf("UDPソケットのオープンに失敗しました: %s\n", SDLNet_GetError());
		return NULL;
	}
	if( !( packet = SDLNet_AllocPacket(packetSize) ) ){
		printf("パケットの割り当てに失敗しました: %s\n", SDLNet_GetError());
		return NULL;
	}
	if( SDLNet_UDP_Bind(socket, 0, &ip) == -1 ){
		printf("バインドに失敗しました: %s\n", SDLNet_GetError());
		return NULL;
	}

	UDPClientSession *newSession = new UDPClientSession(socket, packet);

	return newSession;

} // createUDPClientSession

/* サーバ(受信側) */
UDPServerSession *Network::createUDPServerSession(int portNo, int packetSize){

	UDPsocket socket;
	UDPpacket *packet;

	if( !( socket = SDLNet_UDP_Open(portNo) ) ){
		printf("UDPソケットのオープンに失敗しました: %s\n", SDLNet_GetError());
		return NULL;
	}

	if( !( packet = SDLNet_AllocPacket(packetSize) ) ){
		printf("パケットの割り当てに失敗しました: %s\n", SDLNet_GetError());
		return NULL;
	}
	packet->channel = 0;

	UDPServerSession *newSession = new UDPServerSession(socket, packet);

	return newSession;

} // createUDPServerSession
