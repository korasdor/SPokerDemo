#ifndef __REMOTE_SERVICE_H__
#define __REMOTE_SERVICE_H__

#include "cocos2d.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "WSService.h"
#include "../models/GameModel.h"
#include "../models/data/TicketData.h"

class RemoteService
{

public:	

	RemoteService();
	~RemoteService();

private:

};

#endif // __REMOTE_SERVICE_H__