#pragma once
#include "../SGD Wrappers/IMessage.h"

class MSG_GoToState : public IMessage
{
public:
	MSG_GoToState( int id ) {m_nMessageId = id;}
	virtual ~MSG_GoToState( void ) {}
	virtual MSGID	GetMessageID( void ){return m_nMessageId;}

private:
	int m_nMessageId;
};