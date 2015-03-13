#include "MainController.h"


USING_NS_CC;
using namespace rapidjson;

MainController::MainController(RemoteService* remoteService, GameModel* gameModel){
	_remoteService = remoteService;
	_gameModel = gameModel;


	_mainView = MainView::create();
	_mainView->setupController(this);
	
	auto scene = MainView::createScene(_mainView);
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.2f, scene));
}

void MainController::onViewExit(int nextViewIndex){
	if (onViewExitCallback){
		onViewExitCallback(nextViewIndex);
	}
}

void MainController::clear(){
	/*_remoteService->disconnect();*/
}

MainController::~MainController(){
}