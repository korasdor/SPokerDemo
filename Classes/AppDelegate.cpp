#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("UITest");
        director->setOpenGLView(glview);
    }

	//glview->setFrameSize(1024, 768);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	
	glview->setDesignResolutionSize(1200, 800, ResolutionPolicy::SHOW_ALL);

	_remoteService = new RemoteService();
	_gameModel = new GameModel();

	_controller = new MainController(_remoteService, _gameModel);
	_controller->onViewExitCallback = std::bind(&AppDelegate::onViewExitCallback, this, std::placeholders::_1);

    return true;
}

void AppDelegate::onViewExitCallback(int nextViewIndex){
	if (nextViewIndex == 0){
		_controller->onViewExitCallback = nullptr;
		_controller->clear();
		delete _controller;

		_controller = new MainController(_remoteService, _gameModel);
		_controller->onViewExitCallback = std::bind(&AppDelegate::onViewExitCallback, this, std::placeholders::_1);
	}
	else if (nextViewIndex == 5){
		_controller->onViewExitCallback = nullptr;
		/*_controller->clear();*/
		delete _controller;

		/*_controller = new GameController(_remoteService, _gameModel);
		_controller->onViewExitCallback = std::bind(&AppDelegate::onViewExitCallback, this, std::placeholders::_1);*/
	}
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
