#ifndef __GAME_UTILS_H__
#define __GAME_UTILS_H__

#include "cocos2d.h"
#include <iomanip>

class GameUtils
{
public:
	~GameUtils();

	static GameUtils* getInstance();

	void shuffle(int arr[], int size);
	std::string toFixed(float num, int precision);
	std::string formatToTimeString(int val);

private:
	GameUtils();

	void swap(int *a, int *b);
};

#endif // __GAME_UTILS_H__
