#include "DragSampleView.h"


USING_NS_CC;

DragSampleView::DragSampleView(){
}

DragSampleView::~DragSampleView(){
}

bool DragSampleView::init(){

	for (int i = 0; i < 52; i++){
		int rw = rand() % 1000;
		int rh = rand() % 500;

		auto card = DSprite::create("cards/" + std::to_string(i + 1) + ".png");
		card->addEvents();
		card->setPosition(Vec2(rw, rh));
		card->setAnchorPoint(Vec2(0.0f, 0.0f));
		card->setScale(0.5f);
		card->onTouchBeganCallback = std::bind(&DragSampleView::onCardTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
		card->onTouchMoveCallback = std::bind(&DragSampleView::onCardTouchMove, this, std::placeholders::_1, std::placeholders::_2);
		card->onTouchEndedCallback = std::bind(&DragSampleView::onCardTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
		this->addChild(card);

		_cards.push_back(card);
	}

	int rw = rand() % 1000;
	int rh = rand() % 500;

	auto piece = DSprite::create("color_piece_red_active.png");
	piece->addEvents();
	piece->setPosition(Vec2(rw, rh));
	piece->setAnchorPoint(Vec2(0.0f, 0.0f));
	piece->setScale(0.5f);
	piece->onTouchBeganCallback = std::bind(&DragSampleView::onCardTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
	piece->onTouchMoveCallback = std::bind(&DragSampleView::onCardTouchMove, this, std::placeholders::_1, std::placeholders::_2);
	piece->onTouchEndedCallback = std::bind(&DragSampleView::onCardTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
	this->addChild(piece);

	_cards.push_back(piece);

	this->schedule(schedule_selector(DragSampleView::onTimer), 0.1f);

	return true;
}

void DragSampleView::onTimer(float dt){
	if (_isDragging == true){
		checkCollision();
	}
}

void DragSampleView::onCardTouchBegan(cocos2d::Node* target, cocos2d::Touch* touch){
	_currentCard = static_cast<DSprite*>(target);
	_isDragging = true;
}

void DragSampleView::onCardTouchMove(cocos2d::Node* target, cocos2d::Touch* touch){
}

void DragSampleView::onCardTouchEnded(cocos2d::Node* target, cocos2d::Touch* touch){
	_isDragging = false;
}

void DragSampleView::checkCollision(){
	bool isCollide = false;
	for (unsigned i = 0; i < _cards.size(); i++){
		if (_currentCard->hitTest(_cards.at(i)) && _currentCard != _cards.at(i)){
			isCollide = true;
			_cards.at(i)->setHitState();
		}
		else{
			_cards.at(i)->setNormalState();
		}
	}

	if (isCollide == true){
		_currentCard->setHitState();
	}
	else{
		_currentCard->setNormalState();
	}
}