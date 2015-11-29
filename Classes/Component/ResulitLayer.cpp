#include "ResulitLayer.h"
#include <sstream>
#include "GameData/PlayerMrg.h"
#include "Config/NotificationNameConfig.h"
#include "GamingLayer.h"
#include "Config/BaseConfig.h"
#include "TipLayer.h"
#include "../LoginScene.h"
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

void ResulitLayer::onEnter()
{	
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -128, true);
	CCLayer::onEnter();
}

void ResulitLayer::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool ResulitLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}


bool ResulitLayer::initResulitLayer()
{
	CCLayer::setIsKeypadEnabled(true);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(winSize);
	std::string strName = "";
	strName = s_language + "tongji.png";
	CCSprite *bg = CCSprite::spriteWithFile(strName.c_str());
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(bg);
	float bgheight = bg->getContentSize().height;
	//grade 
	std::string StrOne = "";
	StrOne = s_language + "score.png";
	CCSprite *nowGrade = CCSprite::spriteWithFile(StrOne.c_str());
	nowGrade->setPosition(ccp(50, bgheight - 180));
	nowGrade->setAnchorPoint(ccp(0, 0));
	bg->addChild(nowGrade);

	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerGrade();
	CCLabelAtlas* gradeLabel = CCLabelAtlas::labelWithString(ss.str().c_str(), "grade.png", 32, 45, '/');//CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	gradeLabel->setAnchorPoint(ccp(0, 0));
	gradeLabel->setPosition(ccp(50 + nowGrade->getContentSize().width + 5, bgheight - 180));
	gradeLabel->setScale(0.75);
	bg->addChild(gradeLabel); 
    //lastHightGrade 
	std::string stdName = "";
	stdName = s_language + "topscore.png";
	CCSprite *lastGrade = CCSprite::spriteWithFile(stdName.c_str());
	lastGrade->setPosition(ccp(50, bgheight - 220));
	lastGrade->setAnchorPoint(ccp(0, 0.5));
	bg->addChild(lastGrade);

	ss.str("");
	ss.clear();
	ss << PlayerMrg::getInstance()->getPlayerLastHightGrade();
	CCLabelAtlas* lastgradeLabel = CCLabelAtlas::labelWithString(ss.str().c_str(), "grade.png", 32, 45, '/');//CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	lastgradeLabel->setScale(0.75);
	lastgradeLabel->setPosition(ccp(50 + lastGrade->getContentSize().width + 5, bgheight - 220));
	lastgradeLabel->setAnchorPoint(ccp(0, 0.5));
	bg->addChild(lastgradeLabel);
	ss.str("");
	ss.clear();

	if (PlayerMrg::getInstance()->getPlayer()->getPlayerGrade() > PlayerMrg::getInstance()->getPlayerLastHightGrade())
	{
		PlayerMrg::getInstance()->setPlayerLastHightGrade(PlayerMrg::getInstance()->getPlayer()->getPlayerGrade());
	}

	//chongxin kaishi
	std::string nameOne = "";
	nameOne = s_touchfile + s_language + "actor_btn_restart.png";
	CCMenuItemImage *pContinue = CCMenuItemImage::itemFromNormalImage(
		nameOne.c_str(),
		NULL,
		this,
		menu_selector(ResulitLayer::restartGame));
	pContinue->setPosition(ccp(bg->getContentSize().width / 2 - pContinue->getContentSize().width / 2 + 30, bgheight - 320));
	pContinue->setAnchorPoint(ccp(0, 0));
	pContinue->setScale(0.75);
	std::string str = s_touchfile + s_language + "actor_btn_exit.png";
	CCMenuItemImage *pExit = CCMenuItemImage::itemFromNormalImage(
		str.c_str(),
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

void ResulitLayer::menuExitCallBack(CCObject *pSender)
{
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->getRunningScene()->removeAllChildrenWithCleanup(true);
	PlayerMrg::getInstance()->Delete();
//	PlayerMrg::getInstance()->Init();
	CCScene *secen = LoginScene::scene();
	CCDirector::sharedDirector()->replaceScene(secen);
}

bool ResulitLayer::keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus iKeyState)
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

