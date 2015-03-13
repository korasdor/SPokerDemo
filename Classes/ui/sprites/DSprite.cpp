#include "DSprite.h"

USING_NS_CC;

DSprite::DSprite() {}

DSprite::~DSprite() {
	/*if (_listener){
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
	}*/

	removeEvents();
}


/*************************************************************************Create and Init Methods*****************************************************************************/


DSprite* DSprite::create(std::string filename)
{
	DSprite* pSprite = new DSprite();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}


Rect DSprite::getRect()
{
	auto s = getTexture()->getContentSize();
	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool DSprite::containsTouchLocation(Touch* touch)
{
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}


bool DSprite::hitTest(cocos2d::Sprite* sprite){
	if (PixelCollision::getInstance()->collidesWithSprite(this, sprite, false) == true){
		return PixelCollision::getInstance()->collidesWithSprite(this, sprite, true);
	}
	else{
		return false;
	}	
}

void DSprite::addEvents(){
	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);

	_listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{			
			_touchOffset = Vec2(abs(p.x - rect.origin.x), abs(p.y - rect.origin.y));
			
			if (onTouchBeganCallback){
				onTouchBeganCallback(this, touch);
			}

			return true;
		}

		return false;
	};

	_listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{

		auto touchPoint = touch->getLocation();
		setPosition(Vec2(touchPoint.x - _touchOffset.x, touchPoint.y - _touchOffset.y));

		if (onTouchMoveCallback){
			onTouchMoveCallback(this, touch);
		}
	};

	_listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if (onTouchEndedCallback){
			onTouchEndedCallback(this, touch);
		}		
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

void DSprite::removeEvents(){
	if (_listener){
		Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	}
}


void DSprite::setNormalState(){
	setOpacity(255);
}
void DSprite::setHitState(){
	setOpacity(125);
}