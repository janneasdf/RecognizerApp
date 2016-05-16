/*********************************************************************
	Network�N���X			�uNetwork.h�v

	�T�v:
		udp�\�P�b�g�ʐM�N���X

	Date:
		Created: 2009/02/02	By �ł�
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
													������ / ���
	 ********************************************************************/
	/* ������ */
	static int initialize();

	/* ��� */
	static void finalize();

	/********************************************************************
													UDP�Z�b�V�����̍쐬
	 ********************************************************************/
	/* �N���C�A���g(���M��) */
	static UDPClientSession *createUDPClientSession(const char *ipAddr, int portNo, int packetSize = 1024);
	
	/* �T�[�o(��M��) */
	static UDPServerSession *createUDPServerSession(int portNo, int packetSize = 1024);

protected:

};
#endif
