#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "json/document.h"
#include "../scenes/GameView.h"
#include "../models/data/TicketData.h"
#include "impl/IController.h"

class GameController : public IController
{

public:
	

	GameController(RemoteService* remoteService, GameModel* gameModel);
	~GameController();

	bool changeBonusState();

	void addTicketData(std::vector<int> nums, int bet);
	void onRepeatBets();
	void onViewExit(int nextViewIndex);
	void clearPrevGame();
	void clear();

private:
	GameView* _gameView;

	std::vector<int> _balls;

	int _gameId;
	int _betTimout;
	bool _isFinished;

	int _totalBets = 0;
	int _totalBalance = 0;
	float _totalWin = 0;
	bool _isCleared = true;
	bool _isInitRand = true;


	std::vector<TicketData> _tickets;
	std::vector<TicketData> _hTickets;
	bool _isBonus = false;

	void ticketAddComplete();

	void onHttpResponse(std::string data, std::string tag);
	void onRandMessage(std::string data);
	
	void onGetBalanceComplete(std::string data);
	void onGetBetsComplete(std::string data);
	void onGetRulesComplete(std::string data);	
	void onGetWinComplete(std::string data);

	
};

#endif // __GAME_CONTROLLER_H__
