#ifndef __WS_SERVICE_H__
#define __WS_SERVICE_H__

#include "cocos2d.h"
#include "network/WebSocket.h"

class WSService : public cocos2d::network::WebSocket::Delegate{

public:
	
	std::function<void()> onConnectionClosed;
	std::function<void(std::string message)> onMessageReceived;
	std::function<void(const cocos2d::network::WebSocket::ErrorCode &error)> onErrorOccurred;
	std::function<void()> onConnectionOpened;

	WSService(std::string);
	~WSService();

	void connect();
	
	static WSService* create(std::string url);

	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
	virtual void onClose(cocos2d::network::WebSocket* ws);

	void close();
	void send(std::string);

private:
	std::string _url;
	cocos2d::network::WebSocket* _webSocket;

};

#endif