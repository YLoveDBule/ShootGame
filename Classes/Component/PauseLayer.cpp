#include "PauseLayer.h"
#include "cocos2d.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/PlayerMrg.h"
#include "GamingLayer.h"

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
	this->setContentSize(winSize);
	CCLayerColor *maskLayer = CCLayerColor::node();
	maskLayer->initWithColorWidthHeight(ccc4f(0x00,0x00,0x00,0x80),335,350);
	//maskLayer->setOpacity(200);
	maskLayer->setAnchorPoint(ccp(0.5, 0.5));
	maskLayer->setPosition(ccp(winSize.width/2-maskLayer->getContentSize().width/2, winSize.height/2-maskLayer->getContentSize().height/2));
	this->addChild(maskLayer);

	CCMenuItemImage *continueItem = CCMenuItemImage::itemFromNormalImage("common/actor_btn_continue.png", "common/actor_btn_continue.png", this, menu_selector(PauseLayer::continueGame));
	CCMenuItemImage *restartItem = CCMenuItemImage::itemFromNormalImage("common/actor_btn_restart.png", "common/actor_btn_restart.png", this, menu_selector(PauseLayer::restartGame));
	CCMenuItemImage *exitItem = CCMenuItemImage::itemFromNormalImage("common/actor_btn_exit.png", "common/actor_btn_exit.png", this, menu_selector(PauseLayer::exitGame));
	CCMenu *menu = CCMenu::menuWithItems(continueItem, restartItem, exitItem, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	CCLayer::setIsKeypadEnabled(true);
	return true;
}

PauseLayer::PauseLayer(){};
PauseLayer::~PauseLayer(){};

void PauseLayer::onEnter()
{
	CCLayer::onEnter();
	
}

void PauseLayer::onExit()
{
	CCLayer::onExit();
}


void PauseLayer::continueGame(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_RESUME_GAME);
}

void PauseLayer::restartGame(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
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
	
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_EXIT_GAME);

	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool PauseLayer::keyAllClicked(int iKeyID, CCKeypadStatus key_status)
{
	switch (iKeyID)
	{
	case 'w':
	case 'W':
		//	case KEY_UP:
		onClickW(key_status);
		break;
	case 's':
	case 'S':
		//	case KEY_DOWN:
		onClickS(key_status);
		break;
	case 'a':
	case 'A':
		//	case KEY_LEFT:
		onClickA(key_status);
		break;
	case 'd':
	case 'D':
		//	case KEY_RIGHT:
		onClickD(key_status);
		break;

	case 'i':
	case 'I':
		//	case KEY_A:
		onClickI(key_status);
		break;
	case 'k':
	case 'K':
		//	case KEY_B:
		onClickK(key_status);
		break;
	case 'l':
	case 'L':
		//	case KEY_X:
		onClickL(key_status);
		break;
	case 'j':
	case 'J':
		//	case KEY_Y:
		onClickJ(key_status);
		break;
	default:
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, key_status);
		break;
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