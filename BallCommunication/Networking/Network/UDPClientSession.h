/*********************************************************************
	UDPClientSession�N���X			�uUDPClientSession.h�v

	�T�v:
		UDP�\�P�b�g�ʐM�N���X�̃N���C�A���g����

	Date:
		Created: 2009/02/02	By �ł�
 *********************************************************************/

#ifndef __UDPCLIENTSESSION_H__
#define __UDPCLIENTSESSION_H__

#include "../../Libraries/SDL/include/SDL.h"
#include "../../Libraries/SDL/include/SDL_net.h"

class UDPClientSession{

public:

	/* �R���X�g���N�^ */
	UDPClientSession(UDPsocket socket, UDPpacket *packet);

	/* �f�X�g���N�^ */
	virtual ~UDPClientSession();

	/********************************************************************
												���b�Z�[�W�̑��M
	 ********************************************************************/
	int sendMessage(void *sendDataPtr, Uint32 length);
	
protected:
	
	UDPsocket socket;
	UDPpacket *packet;

};
#endif
