/*********************************************************************
	UDPServerSession�N���X			�uUDPServerSession.h�v

	�T�v:
		UDP�\�P�b�g�ʐM�N���X�̃T�[�o����

	Date:
		Created: 2009/02/02	By �ł�
 *********************************************************************/

#ifndef __UDPSERVERSESSION_H__
#define __UDPSERVERSESSION_H__

#include "../../Libraries/SDL/include/SDL.h"
#include "../../Libraries/SDL/include/SDL_net.h"

class UDPServerSession{

public:

	/* �R���X�g���N�^ */
	UDPServerSession(UDPsocket socket, UDPpacket *packet);

	/* �f�X�g���N�^ */
	virtual ~UDPServerSession();

	/********************************************************************
												���b�Z�[�W�̑��M
	 ********************************************************************/
	int receiveMessage(void *receiveDataPtr, Uint32 length);
	
protected:
	
	UDPsocket socket;
	UDPpacket *packet;

};
#endif
