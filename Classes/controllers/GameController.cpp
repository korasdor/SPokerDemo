#include "GameController.h"


USING_NS_CC;
using namespace rapidjson;

GameController::GameController(RemoteService* remoteService, GameModel* gameModel){
	_remoteService = remoteService;

	_gameModel = gameModel;

	remoteService->onHttpResponse = std::bind(&GameController::onHttpResponse, this, std::placeholders::_1, std::placeholders::_2);
	remoteService->onRandMessage = std::bind(&GameController::onRandMessage, this, std::placeholders::_1);
	remoteService->setUrl(_gameModel->url);
	remoteService->connect();
	remoteService->sendGetBalance();
	remoteService->sendGetRules();

	_gameView = GameView::create();
	_gameView->setupController(this);
	_gameView->setBetsValues(&_gameModel->bets);

	auto scene = GameView::createScene(_gameView);
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.2f, scene));

}

GameController::~GameController(){
}

/*********************************************************************Rand Methods**********************************************************************************/

void GameController::onRandMessage(std::string data){
	Document d;
	d.Parse<0>(data.c_str());

	rapidjson::Value& gameId = d["game_id"];
	rapidjson::Value& balls = d["balls"];
	rapidjson::Value& betTimeout = d["bet_timeout"];
	rapidjson::Value& isFinished = d["finished"];

	_gameId = gameId.GetInt();
	_betTimout = betTimeout.GetInt();
	_isFinished = isFinished.GetBool();

	_balls.erase(_balls.begin(), _balls.end());
	for (unsigned i = 0; i < balls.Size(); i++){
		rapidjson::Value& ball = balls[i];

		_balls.push_back(ball.GetInt());
	}

	if (_isInitRand == true){
		_isInitRand = false;

		_remoteService->senGetBets(std::to_string(_gameId));
	}

	//конец ставок или идет игра
	if (_isFinished == false){
		//конец ставок
		if (_balls.size() == 0){
			clearPrevGame();

			_gameView->endBets();
			_hTickets = _tickets;

			//идет игра
		}else{
			_gameView->endBets();
			_gameView->setBalls(_balls);
			_gameView->setTicketsNum( _balls.at(_balls.size() - 1));			
		}

		_gameView->updateBalance(_gameModel->totalBalance);

	//конец игры, начало ставок
	}else{		
		int tSize = _tickets.size();
		_balls.erase(_balls.begin(), _balls.end());
		_tickets.erase(_tickets.begin(), _tickets.end());
		_isCleared = false;

		if (tSize > 0){
			_remoteService->sendGetWin(std::to_string(_gameId));
		}else{
			clearPrevGame();
			_gameView->endGame(0);
			_gameView->startTimer(_betTimout);
		}
	}
}


/*********************************************************************HTTP Methods**********************************************************************************/

void GameController::onHttpResponse(std::string data, std::string tag){
	if ( tag == RemoteService::GET_BALANCE_TAG ){
		onGetBalanceComplete(data);
	}
	else if (tag == RemoteService::GET_RULES_TAG) {
		onGetRulesComplete(data);
	}
	else if (tag == RemoteService::POST_BET_TAG) {
		onGetBalanceComplete(data);
		ticketAddComplete();
	}
	else if (tag == RemoteService::GET_WIN_TAG){
		onGetWinComplete(data);
	}
	else if (tag == RemoteService::GET_BETS_TAG){
		onGetBetsComplete(data);
	}

}

void GameController::onGetBalanceComplete(std::string data){
	if (_gameView->isActive == false) return;

	Document d;
	d.Parse<0>(data.c_str());

	rapidjson::Value& totalBalanceVal = d["balance"];
	rapidjson::Value& totalBonusVal = d["bonus_balance"];
	
	_gameModel->totalBalance = totalBalanceVal.GetDouble();
	_gameModel->totalBonus = totalBonusVal.GetDouble();


	float totalBalance = (_isBonus == false) ? _gameModel->totalBalance : _gameModel->totalBonus;
	_gameView->updateBalance(totalBalance);
}

void GameController::onGetRulesComplete(std::string data){
	if (_gameView->isActive == false) return;

	_gameModel->coefs.erase(_gameModel->coefs.begin(), _gameModel->coefs.end());

	Document d;
	d.Parse<0>(data.c_str());

	std::vector<std::vector<float>> coefs;
	for (SizeType i = 0; i < d.Size(); i++){
		std::vector<float> rows;

		rapidjson::Value& rowVal = d[i];

		for (SizeType j = 0; j < rowVal.Size(); j++){
			rapidjson::Value& digVal = rowVal[j];

			rows.push_back((float)digVal.GetDouble());
		}
		_gameModel->coefs.push_back(rows);
	}

	_gameView->setCoefs(&_gameModel->coefs);
}

void GameController::onGetBetsComplete(std::string data){
	if (_gameView->isActive == false) return;

	Document d;
	d.Parse<0>(data.c_str());

	if (d.Size() == 0) return;

	
	for (unsigned i = 0; i < d.Size(); i++){
		std::vector<int> nums;

		rapidjson::Value& betObjVal = d[i];
		rapidjson::Value& betVal = betObjVal["bet_sum"];
		rapidjson::Value& numsVal = betObjVal["content"];

		for (unsigned j = 0; j < numsVal.Size(); j++){
			nums.push_back(numsVal[j].GetInt());
		}

		TicketData ticketData;
		ticketData.bet = betVal.GetInt();
		ticketData.nums = nums;
		ticketData.isChecked = true;
		_tickets.push_back(ticketData);

		_gameView->showTicket(&ticketData);

		_totalBets += ticketData.bet;
	}
	
	_gameView->updateHeader(_totalBets, _tickets.size());

	for (unsigned i = 0; i < _balls.size(); i++){
		_gameView->setTicketsNum(_balls.at(i));
	}
}

void GameController::onGetWinComplete(std::string data){
	if (_gameView->isActive == false) return;

	Document d;
	d.Parse<0>(data.c_str());

	rapidjson::Value& totalWinVal = d["total_win"];

	_totalWin = totalWinVal.GetDouble();

	_gameView->endGame(_totalWin);
}


/*********************************************************************Common Methods**********************************************************************************/


bool GameController::changeBonusState(){
	_isBonus = !_isBonus;

	float totalBalance = (_isBonus == false) ? _gameModel->totalBalance : _gameModel->totalBonus;
	_gameView->updateBalance(totalBalance);

	return _isBonus;
}

void GameController::addTicketData(std::vector<int> nums, int bet){

	TicketData ticketData;
	ticketData.bet = bet;
	ticketData.nums = nums;	
	
	if (_tickets.size() <= TICKETS_MAX_COUNT){
		_tickets.push_back(ticketData);

		_remoteService->sendPostBet(ticketData.bet, &ticketData.nums, _isBonus, _gameModel->gameToken);
	}
	else{
		//TODO show notif dialog
	}
}

void GameController::ticketAddComplete(){

	_totalBets = 0;
	for (unsigned i = 0; i < _tickets.size(); i++)
	{
		TicketData* ticketData = &_tickets.at(i);
		if (ticketData->isChecked == false){
			ticketData->isChecked = true;
			_gameView->showTicket(ticketData);
		}

		_totalBets += ticketData->bet;
	}

	_gameView->updateHeader(_totalBets, _tickets.size());
}


void GameController::onRepeatBets() {
	int hTicketsCount = _hTickets.size();
	int cTicketsCount = _tickets.size();

	if ((hTicketsCount + cTicketsCount) <= TICKETS_MAX_COUNT){
		for (unsigned i = 0; i < _hTickets.size(); i++){
			TicketData ticketData = _hTickets.at(i);
			ticketData.isChecked = false;

			_tickets.push_back(ticketData);
		}

		_remoteService->sendPostBet(&_tickets, _isBonus, _gameModel->gameToken);
	}
	else{
		//TODO show error
	}
}

void GameController::onViewExit(int nextViewIndex){
	if (onViewExitCallback){
		onViewExitCallback(nextViewIndex);
	}
}

void GameController::clearPrevGame(){
	if (_isCleared == false){
		_isCleared = true;
		_gameView->clearAll();

		_totalWin = 0;
	}
	
}

void GameController::clear(){
	_remoteService->disconnect();
}