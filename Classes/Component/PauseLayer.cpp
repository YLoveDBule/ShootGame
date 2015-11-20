#include "PauseLayer.h"
#include "cocos2d.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/PlayerMrg.h"
#include "GamingLayer.h"
#include "Config/BaseConfig.h"
#include "../LoginScene.h"
#include "Component/TipLayer.h"

USING_NS_CC;

PauseLayer* PauseLayer::Create()
{
	PauseLayer *pPauseLayer = new PauseLayer();
	if (pPauseLayer && pPauseLayer->initPauseLayer())
	{
		return pPauseLayer;
	}
	else
	{
		CC_SAFE_DELETE(pPauseLayer);
		return NULL;
	}
}

bool PauseLayer::initPauseLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCLayerColor *maskLayer = CCLayerColor::node();
	//maskLayer->initWithColorWidthHeight(ccc4f(0x00,0x00,0x00,0x80),335,350);
	////maskLayer->setOpacity(200);
	//maskLayer->setAnchorPoint(ccp(0.5, 0.5));
	//maskLayer->setPosition(ccp(winSize.width/2-maskLayer->getContentSize().width/2, winSize.height/2-maskLayer->getContentSize().height/2));
	//this->addChild(maskLayer);
	CCSprite *bgSprite = CCSprite::spriteWithFile("actor_pause_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	std::string stdNameOne = "";
	std::string stdNameTwo = "";
	std::string stdNameThree = "";
	stdNameOne = s_language + "actor_btn_continue.png";
	stdNameTwo = s_language + "actor_btn_restart.png";
	stdNameThree = s_language + "actor_btn_exit.png";
	CCMenuItemImage *continueItem = CCMenuItemImage::itemFromNormalImage(stdNameOne.c_str(), stdNameOne.c_str(), this, menu_selector(PauseLayer::continueGame));
	CCMenuItemImage *restartItem = CCMenuItemImage::itemFromNormalImage(stdNameTwo.c_str(), stdNameTwo.c_str(), this, menu_selector(PauseLayer::restartGame));
	CCMenuItemImage *exitItem = CCMenuItemImage::itemFromNormalImage(stdNameThree.c_str(), stdNameThree.c_str(), this, menu_selector(PauseLayer::exitGame));
	CCMenu *menu = CCMenu::menuWithItems(continueItem, restartItem, exitItem, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	//CCLayer::setIsKeypadEnabled(true);
	this->setKeyPadEnable(NULL);
	return true;
}

PauseLayer::PauseLayer(){};
PauseLayer::~PauseLayer(){};

void PauseLayer::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -128, true);
	CCLayer::onEnter();
	//CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(PauseLayer::setKeyPadEnable), NOTIFY_LAYER_KEYPAD_ENABLED, NULL);
}




void PauseLayer::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
	//CCNotificationCenter::sharedNotifCenter()->removeObserver(this,NOTIFY_LAYER_KEYPAD_ENABLED);
}

bool PauseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	return true;
}

void PauseLayer::setKeyPadEnable(CCObject *pSender)
{
	this->setIsKeypadEnabled(true);
}

void PauseLayer::setKeyPadDisable(CCObject *pSender)
{
	this->setIsKeypadEnabled(false);
}

void PauseLayer::continueGame(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_RESUME_GAME);
}

void PauseLayer::restartGame(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
	/*CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_RESTART_GAME);*/
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->getRunningScene()->removeAllChildrenWithCleanup(true);
	PlayerMrg::getInstance()->Delete();
	PlayerMrg::getInstance()->Init();
	GamingLayer*layer = GamingLayer::createGamingLayer();
	CCScene *scene = CCScene::node();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void PauseLayer::exitGame(CCObject *pSender)
{
	
	/*CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_EXIT_GAME);

	CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif*/
	/*CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->getRunningScene()->removeAllChildrenWithCleanup(true);
	PlayerMrg::getInstance()->Delete();
	PlayerMrg::getInstance()->Init();
	CCScene *secen = LoginScene::scene();
	CCDirector::sharedDirector()->replaceScene(secen);*/
	CCDirector::sharedDirector()->getRunningScene()->addChild(TipLayer::Create());
	this->removeFromParentAndCleanup(true);
}

bool PauseLayer::keyAllClicked(int iKeyID, CCKeypadStatus iKeyState)
{

	if (iKeyID == 'w' || iKeyID == 'W' || iKeyID == HANDSET_UP || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_UP)
	{
		onClickW(iKeyState);
	}
	else if (iKeyID == 's' || iKeyID == 'S' || iKeyID == HANDSET_DOWN || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_DOWN)
	{
		onClickS(iKeyState);
	}
	else if (iKeyID == 'a' || iKeyID == 'A' || iKeyID == HANDSET_LEFT || iKeyID == HANDSET_LEFT_ || iKeyID == KEY_LEFT)
	{
		onClickA(iKeyState);
	}
	else if (iKeyID == 'd' || iKeyID == 'D' || iKeyID == HANDSET_RIGHT || iKeyID == HANDSET_RIGHT_ || iKeyID == KEY_RIGHT)
	{
		onClickD(iKeyState);
	}
	else if (iKeyID == 'j' || iKeyID == 'J' || iKeyID == HANDSET_Y || iKeyID == HANDSET_Y_ || iKeyID == KEY_Y)
	{
		onClickJ(iKeyState);
	}
	else if (iKeyID == 'i' || iKeyID == 'I' || iKeyID == HANDSET_A || iKeyID == HANDSET_A_ || iKeyID == KEY_A)
	{
		onClickI(iKeyState);
	}
	else if (iKeyID == 'k' || iKeyID == 'K' || iKeyID == HANDSET_B || iKeyID == HANDSET_B_ || iKeyID == KEY_B)
	{
		onClickK(iKeyState);
	}
	else if (iKeyID == 'l' || iKeyID == 'L' || iKeyID == HANDSET_X || iKeyID == HANDSET_X_ || iKeyID == KEY_X)
	{
		onClickL(iKeyState);
	}
	else
	{
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		return false;
	}
	return true;
}

void PauseLayer::onClickA(CCKeypadStatus key_status)
{
	
}

void PauseLayer::onClickS(CCKeypadStatus key_status)
{
}

void PauseLayer::onClickW(CCKeypadStatus key_status)
{

}

void PauseLayer::onClickD(CCKeypadStatus key_status)
{

}

void PauseLayer::onClickJ(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		this->continueGame(NULL);
	}
}

void PauseLayer::onClickK(CCKeypadStatus key_status)
{

}

void PauseLayer::onClickL(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		this->exitGame(NULL);
	}
}

void PauseLayer::onClickI(CCKeypadStatus key_status)
{
	CCLog("onClickI");
	if (key_status == EVENT_KEY_DOWN){
		this->restartGame(NULL);
	}
}