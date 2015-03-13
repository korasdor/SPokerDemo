#include "MainView.h"
#include "../controllers/MainController.h"

USING_NS_CC;

Scene* MainView::createScene(MainView* layer)
{
	auto scene = Scene::create();

	scene->addChild(layer);

	return scene;
}

bool MainView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();		

	srand(time(NULL));

	int deck[52];
	init_deck(deck);

	auto dragSample = DragSampleView::create();
	dragSample->setAnchorPoint(Vec2(0.0f, 0.0f));
	dragSample->setPosition(Vec2(0.0f, 0.0f));
	this->addChild(dragSample);


	int index = find_card(Deuce, HEART, deck);
	CCLOG("%d",index);

	
	return true;
}

void MainView::setupController(MainController* controller){
	_controller = controller;
}
