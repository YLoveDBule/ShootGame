#include "ResulitLayer.h"
#include <sstream>
#include "GameData\PlayerMrg.h"
#include "Config\NotificationNameConfig.h"
ResulitLayer * ResulitLayer::create()
{
	ResulitLayer *pResulitLayer = new ResulitLayer();
	if (pResulitLayer && pResulitLayer->initResulitLayer())
	{
		return pResulitLayer;
	}
	else
	{
		CC_SAFE_DELETE(pResulitLayer);
		return NULL;
	}
}

ResulitLayer::~ResulitLayer()
{

}

bool ResulitLayer::initResulitLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(winSize);

	CCSprite *bg = CCSprite::spriteWithFile("tongji.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(bg);
	float bgheight = bg->getContentSize().height;
	//grade 
	CCSprite *nowGrade = CCSprite::spriteWithFile("score.png");
	nowGrade->setPosition(ccp(50, bgheight - 180));
	nowGrade->setAnchorPoint(ccp(0, 0));
	bg->addChild(nowGrade);

	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerGrade();
	CCLabelTTF* gradeLabel = CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	gradeLabel->setAnchorPoint(ccp(0, 0));
	gradeLabel->setPosition(ccp(50 + nowGrade->getContentSize().width + 5, bgheight - 180));
	bg->addChild(gradeLabel); 
    //lastHightGrade 
	CCSprite *lastGrade = CCSprite::spriteWithFile("topscore.png");
	lastGrade->setPosition(ccp(50, bgheight - 240));
	lastGrade->setAnchorPoint(ccp(0, 0));
	bg->addChild(lastGrade);

	ss.str("");
	ss.clear();
	ss << PlayerMrg::getInstance()->getPlayerLastHightGrade();
	CCLabelTTF* lastgradeLabel = CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	lastgradeLabel->setPosition(ccp(50 + lastGrade->getContentSize().width + 5, bgheight - 240));
	lastgradeLabel->setAnchorPoint(ccp(0, 0));
	bg->addChild(lastgradeLabel);
	ss.str("");
	ss.clear();

	if (PlayerMrg::getInstance()->getPlayer()->getPlayerGrade() > PlayerMrg::getInstance()->getPlayerLastHightGrade())
	{
		PlayerMrg::getInstance()->setPlayerLastHightGrade(PlayerMrg::getInstance()->getPlayer()->getPlayerGrade());
	}

	//chongxin kaishi 
	CCMenuItemImage *pContinue = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_restart.png",
		NULL,
		this,
		menu_selector(ResulitLayer::restartGame));
	pContinue->setPosition(ccp(bg->getContentSize().width / 2 - pContinue->getContentSize().width / 2 + 30, bgheight - 320));
	pContinue->setAnchorPoint(ccp(0, 0));
	pContinue->setScale(0.75);
	CCMenuItemImage *pExit = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_exit.png",
		NULL,
		this,
		menu_selector(ResulitLayer::menuExitCallBack));
	pExit->setPosition(ccp(bg->getContentSize().width / 2 - pExit->getContentSize().width / 2 + 30, bgheight - 390));
	pExit->setScale(0.75);
	pExit->setAnchorPoint(CCPointZero);
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pContinue, pExit, NULL);
	pMenu->setPosition(CCPointZero);
	bg->addChild(pMenu);

	return true;
}

void ResulitLayer::restartGame(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_RESTART_GAME);
}

void ResulitLayer::menuExitCallBack(CCObject *pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_EXIT_GAME);

	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool ResulitLayer::keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus iKeyState)
{
	switch (iKeyID)
	{
	case 'w':
	case 'W':
		//	case KEY_UP:
		{
			onClickW(iKeyState);
		}
		break;
	case 's':
	case 'S':
		//	case KEY_DOWN:
			onClickS(iKeyState);
		break;
	case 'a':
	case 'A':
		//	case KEY_LEFT:
			onClickA(iKeyState);
		break;
	case 'd':
	case 'D':
		//	case KEY_RIGHT:
			onClickD(iKeyState);
		break;

	case 'i':
	case 'I':
		//	case KEY_A:
			onClickI(iKeyState);
		break;
	case 'k':
	case 'K':
		//	case KEY_B:
			onClickK(iKeyState);
		break;
	case 'l':
	case 'L':
		//	case KEY_X:
			onClickL(iKeyState);
		break;
	case 'j':
	case 'J':
		//	case KEY_Y:
			onClickJ(iKeyState);

	default:
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		break;
	}

	return true;
}

void ResulitLayer::onClickA(cocos2d::CCKeypadStatus key_status)
{

}

void ResulitLayer::onClickS(cocos2d::CCKeypadStatus key_status)
{

}

void ResulitLayer::onClickD(cocos2d::CCKeypadStatus key_status)
{

}

void ResulitLayer::onClickW(cocos2d::CCKeypadStatus key_status)
{

}

void ResulitLayer::onClickI(cocos2d::CCKeypadStatus key_status)
{
	CCLog("onClickI");
	if (key_status == EVENT_KEY_DOWN){
		this->restartGame(NULL);
	}
}

void ResulitLayer::onClickL(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		this->menuExitCallBack(NULL);
	}
}

void ResulitLayer::onClickJ(cocos2d::CCKeypadStatus key_status)
{

}

void ResulitLayer::onClickK(cocos2d::CCKeypadStatus key_status)
{

}

ResulitLayer::ResulitLayer()
{

}

