#include "TipLayer.h"
#include "cocos2d.h"
#include "GameData/PlayerMrg.h"
#include "Config/BaseConfig.h"
#include "Config/NotificationNameConfig.h"
#include "../LoginScene.h"

USING_NS_CC;

TipLayer* TipLayer::Create()
{
	TipLayer *pTipLayer = new TipLayer();
	if (pTipLayer && pTipLayer->initTipLayer())
	{
		return pTipLayer;
	}
	else
	{
		CC_SAFE_DELETE(pTipLayer);
		return NULL;
	}
}

bool TipLayer::initTipLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor *maskLayer = CCLayerColor::node();
	maskLayer->initWithColorWidthHeight(ccc4f(0x00,0x00,0x00,0x80),335,350);
	//maskLayer->setOpacity(200);
	maskLayer->setAnchorPoint(ccp(0.5, 0.5));
	maskLayer->setPosition(ccp(winSize.width/2-maskLayer->getContentSize().width/2, winSize.height/2-maskLayer->getContentSize().height/2));
	this->addChild(maskLayer);
	/*CCSprite *bgSprite = CCSprite::spriteWithFile("actor_pause_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));*/

	
	std::string stdNameOne = "";
	std::string stdNameTwo = "";
	std::string contentImageName = "";
	stdNameOne = s_touchfile + s_language + "actor_btn_cancel.png";
	stdNameTwo = s_touchfile + s_language + "actor_btn_confirm.png";
	contentImageName = s_language + "actor_img_tipContent.png";
	//content
	CCSprite *pContentSprite = CCSprite::spriteWithFile(contentImageName.c_str());
	this->addChild(pContentSprite);
	pContentSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2 +100));

	CCMenuItemImage *cancelItem = CCMenuItemImage::itemFromNormalImage(stdNameOne.c_str(), stdNameOne.c_str(), this, menu_selector(TipLayer::cancel));
	CCMenuItemImage *confirmItem = CCMenuItemImage::itemFromNormalImage(stdNameTwo.c_str(), stdNameTwo.c_str(), this, menu_selector(TipLayer::confirm));
	CCMenu *menu = CCMenu::menuWithItems(confirmItem,cancelItem,NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 50));
	this->addChild(menu);

	CCLayer::setIsKeypadEnabled(true);
	return true;
}

TipLayer::TipLayer() {};
TipLayer::~TipLayer() {};

void TipLayer::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -128, true);
	CCLayer::onEnter();

}

void TipLayer::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool TipLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}


void TipLayer::cancel(CCObject *pSender)
{
	this->removeFromParentAndCleanup(true);
	/*CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_RESUME_GAME);*/
}


void TipLayer::confirm(CCObject *pSender)
{

	/*CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_EXIT_GAME);

	CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif*/
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool TipLayer::keyAllClicked(int iKeyID, CCKeypadStatus iKeyState)
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

void TipLayer::onClickA(CCKeypadStatus key_status)
{

}

void TipLayer::onClickS(CCKeypadStatus key_status)
{
}

void TipLayer::onClickW(CCKeypadStatus key_status)
{

}

void TipLayer::onClickD(CCKeypadStatus key_status)
{

}

void TipLayer::onClickJ(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		this->confirm(NULL);
	}
}

void TipLayer::onClickK(CCKeypadStatus key_status)
{

}

void TipLayer::onClickL(CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		this->cancel(NULL);
	}
}

void TipLayer::onClickI(CCKeypadStatus key_status)
{

}