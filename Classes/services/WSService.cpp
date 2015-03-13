#include "WSService.h"

USING_NS_CC;
using namespace cocos2d::network;

WSService* WSService::create(std::string url)
{
	WSService* ws = new WSService(url);

	return ws;
}

WSService::WSService(std::string url)
{
	_url = url;
}

WSService::~WSService(){
	_webSocket->close();
}

void WSService::connect()
{
	_webSocket = new WebSocket();
	_webSocket->init(*this, _url.c_str());
}

void WSService::send(std::string message)
{
	if (_webSocket->getReadyState() == WebSocket::State::OPEN){
		_webSocket->send(message);
	}
}

void WSService::onOpen(WebSocket* ws)
{
	CCLOG("WebSocket connection opened: %s", _url.c_str());
	if ( onConnectionOpened ){
		onConnectionOpened();
	}
}

void WSService::onMessage(WebSocket* ws, const WebSocket::Data &data)
{
	if (onMessageReceived)
	{
		onMessageReceived(data.bytes);
	}
}

void WSService::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
	if (onErrorOccurred){
		onErrorOccurred(error);
	}
}

void WSService::onClose(WebSocket* ws)
{
	if (onConnectionClosed){
		onConnectionClosed();
	}
}

void WSService::close()
{
	if (_webSocket->getReadyState() == WebSocket::State::OPEN){
		_webSocket->close();
	}
}