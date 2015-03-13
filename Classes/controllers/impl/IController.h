#ifndef __I_CONTROLLER_H__
#define __I_CONTROLLER_H__

#include "cocos2d.h"
#include "../../services/RemoteService.h"
#include "../../models/GameModel.h"


class IController
{

public:

	std::function<void(int nextViewIndex)> onViewExitCallback;	

	virtual void onViewExit(int nextViewIndex) = 0;
	virtual void clear() = 0;

protected:

	GameModel* _gameModel;
	RemoteService* _remoteService;

private:
};

#endif // __I_CONTROLLER_H__