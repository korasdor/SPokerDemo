#include "GameUtils.h"

USING_NS_CC;

static GameUtils* _instance;

GameUtils::GameUtils(){
}

GameUtils::~GameUtils(){
}


GameUtils* GameUtils::getInstance(){	
	if (!_instance){
		_instance = new GameUtils();
	}

	return _instance;
}

std::string GameUtils::toFixed(float num, int precision)
{
	std::stringstream ret;

	ret << std::fixed << std::setprecision(precision) << num;
	std::string val = ret.str();

	//TODO dirty
	if (precision == 1){
		if (val.at(val.length() - 1) == '0'){
			val = val.substr(0, val.length() - 2);
		}
	}

	val = (val == "0") ? "" : val;

	return val;
}


void GameUtils::shuffle(int arr[], int size){
	int i = size;

	for (int i = size - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);

		swap(&arr[i], &arr[j]);
	}
}

void GameUtils::swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

std::string GameUtils::formatToTimeString(int val){
	std::string sVal = std::to_string(val);

	sVal = (sVal.length() > 1) ? sVal : "0" + sVal;

	return sVal;
}
