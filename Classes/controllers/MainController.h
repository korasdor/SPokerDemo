#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include "../views/MainView.h"
#include "json/document.h"
#include "impl/IController.h"

class MainController : public IController
{

public:

	MainController(RemoteService* remoteService, GameModel* gameModel);
	~MainController();

	void onViewExit(int nextViewIndex);
	void clear();

private:
	MainView* _mainView;
	
};

#endif // __MAIN_CONTROLLER_H__