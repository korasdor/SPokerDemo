#include "TSprite.h"

USING_NS_CC;

TSprite::TSprite() {}

TSprite::~TSprite() {
	/*if (_listener){
		Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
	}*/

	removeEvents();
}


/*************************************************************************Create and Init Methods*****************************************************************************/

TSprite* TSprite::create(std::string normalState, std::string pressedState){
	TSprite* pSprite = TSprite::create(normalState);

	if (pSprite != NULL){
		pSprite->normalState = normalState;
		pSprite->pressedState = pressedState;

		return pSprite;
	}

	return NULL;
}

TSprite* TSprite::create(std::string filename)
{
	TSprite* pSprite = new TSprite();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		//pSprite->addEvents();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void TSprite::setLabel(TTFConfig ttfConfig, Color3B color, std::string text){
	_labelValue = text;
	
	_buttonLabel = Label::createWithTTF(ttfConfig, text);
	_buttonLabel->setTextColor(Color4B(color.r, color.g, color.b, 50));
	_buttonLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	_buttonLabel->setPosition(Vec2(62.0f, 30.0f));
	this->addChild(_buttonLabel);
}

void TSprite::updateLabelValue(std::string labelValue){
	_labelValue = labelValue;

	_buttonLabel->setString(labelValue);
}

std::string TSprite::getLabelValue(){
	return _labelValue;
}


/*************************************************************************Toggle Methods*****************************************************************************/

void TSprite::activateToggle(bool isActivatedToggle){
	_isActivatedToggle = isActivatedToggle;
}

void TSprite::setNormalState(){
	if (_buttonLabel){
		Color4B color = _buttonLabel->getTextColor();
		_buttonLabel->setTextColor(Color4B(color.r, color.g, color.b, 50));
	}

	this->setTexture(normalState);
}

void TSprite::setPressedState(){
	if (_buttonLabel){
		Color4B color = _buttonLabel->getTextColor();
		_buttonLabel->setTextColor(Color4B(color.r, color.g, color.b, 255));
	}	

	this->setTexture(pressedState);
}


/*************************************************************************Event Methods*****************************************************************************/

void TSprite::addEvents()
{
	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);

	_listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocation();
		cocos2d::Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			onTouchBegan(touch);

			return true;
		}

		return false;
	};

	_listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		onTouchEnded(touch);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

void TSprite::removeEvents(){
	if (_listener){
		Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	}
}


void TSprite::onTouchBegan(cocos2d::Touch* touch)
{
	if (_isActivatedToggle){
		_isToggle = !_isToggle;

		std::string currentState = (_isToggle) ? pressedState : normalState;

		this->setTexture(currentState);
	}
	

	if (onTouchBeganCallback){
		onTouchBeganCallback(this, touch);
	}
}




void TSprite::onTouchEnded(cocos2d::Touch* touch)
{
	if (_isActivatedToggle){
		std::string currentState = (_isToggle) ? pressedState : normalState;

		this->setTexture(currentState);
	}

	if (onTouchEndedCallback){
		onTouchEndedCallback(this, touch);
	}
}