#ifndef __TICKET_DATA_H__
#define __TICKET_DATA_H__

#include "cocos2d.h"

struct  TicketData
{
	int bet;
	int ticketType;
	std::vector<int> nums;
	bool isChecked = false;
	cocos2d::Color3B betLabelColor;
};

#endif // __TICKET_DATA_H__
