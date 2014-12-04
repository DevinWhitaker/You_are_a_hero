//////////////////////////////////////////////////////////////////////////
//	File	:	"Messages.h"
//
//	Author	:	David Brown (DB)
//
//	Purpose	:	Base class for messages sent to the MessageProc registered
//				in CSGD_MessageSystem.
//
//				Derived classes may add their own data members to be 
//				attached to the message.
///////////////////////////////////////////////////////////////////////////
#pragma once

typedef int MSGID;

enum eMsgTypes {	MSG_NULL = 0,
					MSG_DESTROY_INVADER,
					MSG_DESTROY_LASER,
					//...
					MSG_MAX 
};
 
class IMessage
{
private:
	MSGID	m_msgID;

public:
	IMessage(MSGID msgID)			// Constructor MUST be sent the message type
	{
		m_msgID = msgID;
	}

	virtual ~IMessage(void) {}

	MSGID GetMsgID(void)	{ return m_msgID; }
};