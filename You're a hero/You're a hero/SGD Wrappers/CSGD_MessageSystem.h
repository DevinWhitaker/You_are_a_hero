//////////////////////////////////////////////////////////////////////////
//	File	:	"CSGD_MessageSystem.h"
//
//	Author	:	David Brown (DB)
//
//	Purpose	:	Handles sending the messages to the specified proc function.
///////////////////////////////////////////////////////////////////////////
#pragma once

#include <queue>

#include "IMessage.h"
#include "IMessageReceiver.h"

class CSGD_MessageSystem
{
private:
	std::queue< IMessage* >		m_MsgQueue;						//	Stores messages.
	IMessageReceiver*			m_pReceiver;					//	Points to the class receiving the messages.

	CSGD_MessageSystem() { m_pReceiver = NULL;	}
	~CSGD_MessageSystem() {}

	CSGD_MessageSystem( const CSGD_MessageSystem& );
	CSGD_MessageSystem& operator= ( const CSGD_MessageSystem& );


public:
	
	static CSGD_MessageSystem* GetInstance( void );

	//	How many messages waiting to be processed.
	inline int GetNumMessages( void ) { return (int)m_MsgQueue.size(); }

	//	Setup the function pointer for our messages.
	void Initialize( IMessageReceiver* pReceiver );

	//	Sends the message into the queue and awaits processing later on through
	//	The ProcessMessages() function.
	void QueueMessage( IMessage* pMsg );

	//	Processes all the messages that are waiting inside of the queue.
	//	Normally you only call this function once per frame.
	void ProcessMessages( void );

	//	Clears any messages that may be remaining
	void ClearMessages( void );

	//	Clears any messages that may be remaining and sets the function pointer to NULL.
	void Terminate( void );
};