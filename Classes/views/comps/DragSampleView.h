#ifndef __DRAG_SAMPLE_VIEW_H__
#define __DRAG_SAMPLE_VIEW_H__

#include "cocos2d.h"
#include "utils/poker_eval_lib/poker.h"
#include "ui/sprites/DSprite.h"

class DragSampleView : public cocos2d::Node
{

public:

	DragSampleView();
	~DragSampleView();

	virtual bool init();

	CREATE_FUNC(DragSampleView);
private:
	std::vector<DSprite*> _cards;
	DSprite* _currentCard;
	bool _isDragging = false;

	void onTimer(float dt);

	void onCardTouchBegan(cocos2d::Node* target, cocos2d::Touch* touch);
	void onCardTouchMove(cocos2d::Node* target, cocos2d::Touch* touch);
	void onCardTouchEnded(cocos2d::Node* target, cocos2d::Touch* touch);

	void checkCollision();

};

#endif // __DRAG_SAMPLE_VIEW_H__