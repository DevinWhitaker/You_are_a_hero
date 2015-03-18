#pragma once

//Forward Declaration
class IMessage;

class IMessageReceiver
{
public:
	IMessageReceiver(){};
	virtual ~IMessageReceiver(){};
	virtual void MessageProc(IMessage*) = 0;
};