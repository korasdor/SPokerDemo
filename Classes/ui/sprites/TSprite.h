#ifndef _TSPRITE_H_
#define _TSPRITE_H_

#include "cocos2d.h"

class TSprite : public cocos2d::Sprite
{
public:
	
	std::string normalState;
	std::string pressedState;
	std::function<void(cocos2d::Node* target, cocos2d::Touch* touch)> onTouchBeganCallback;
	std::function<void(cocos2d::Node* target, cocos2d::Touch* touch)> onTouchEndedCallback;

	TSprite();
	~TSprite();

	void addEvents();
	void removeEvents();

	static TSprite* create(std::string normalState, std::string pressedState);
	static TSprite* create(std::string filename);

	void activateToggle(bool isActivatedToggle);
	
	void setNormalState();
	void setPressedState();

	void setLabel(cocos2d::TTFConfig ttfConfig, cocos2d::Color3B color, std::string text);
	void updateLabelValue(std::string labelValue);
	std::string getLabelValue();

private:
	std::string _labelValue;
	bool _isToggle = false;
	bool _isActivatedToggle = false;
	cocos2d::Label* _buttonLabel;

	cocos2d::EventListenerTouchOneByOne* _listener;

	void onTouchBegan(cocos2d::Touch* touch);
	void onTouchEnded(cocos2d::Touch* touch);

};

#endif // _TSPRITE_H_