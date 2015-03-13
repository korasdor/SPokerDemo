#ifndef __MAIN_VIEW_H__
#define __MAIN_VIEW_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "views/comps/DragSampleView.h"

class MainController;

class MainView : public cocos2d::Layer
{


public:
	static cocos2d::Scene* createScene(MainView* gameView);

	virtual bool init();

	CREATE_FUNC(MainView);

	void setupController(MainController* controller);

private:
	MainController* _controller;

	
};

#endif // __MAIN_VIEW_H__