#ifndef _D_SPRITE_H_
#define _D_SPRITE_H_

#include "cocos2d.h"
#include "../../utils/PixelCollision.h"

USING_NS_CC;

class DSprite : public Sprite
{

	

public:
	DSprite(void);
	virtual ~DSprite(void);

	static DSprite* create(std::string filename);

	std::function<void(cocos2d::Node* target, cocos2d::Touch* touch)> onTouchBeganCallback;
	std::function<void(cocos2d::Node* target, cocos2d::Touch* touch)> onTouchMoveCallback;
	std::function<void(cocos2d::Node* target, cocos2d::Touch* touch)> onTouchEndedCallback;

	void addEvents();
	void removeEvents();

	Rect getRect();	
	bool hitTest(cocos2d::Sprite* sprite);
	bool containsTouchLocation(Touch* touch);

	void setNormalState();
	void setHitState();

private:
	cocos2d::Vec2 _touchOffset;
	cocos2d::EventListenerTouchOneByOne* _listener;

	void onTouchBegan(cocos2d::Touch* touch);
	void onTouchEnded(cocos2d::Touch* touch);
};

#endif
