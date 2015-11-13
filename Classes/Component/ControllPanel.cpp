#include "ControllPanel.h"
#include "cocos2d.h"
#include "Cannon.h"
#include "Config/NotificationNameConfig.h"
#include "Config/BaseConfig.h"
#include "GameData/PlayerMrg.h"
#include <sstream>
USING_NS_CC;

ControllPanel* ControllPanel::createControllPanel()
{
	ControllPanel* pControllPanel = new ControllPanel();
	if (pControllPanel && pControllPanel->initControllPanel())
	{
		return pControllPanel;
	}
	else
	{
		CC_SAFE_DELETE(pControllPanel);
		return NULL;
	}
}

void ControllPanel::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(ControllPanel::makeSkillCD), NOTIFY_BARREL_MAGIC_FIRE, NULL);
}

void ControllPanel::onExit()
{
	CCLayer::onExit();
	delete(this->m_pCannon);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_BARREL_MAGIC_FIRE);
}

ControllPanel::ControllPanel(){}
ControllPanel::~ControllPanel(){}

bool ControllPanel::initControllPanel()
{
	this->initBg();
	this->createAttackButton();
	this->createPauseButton();
	this->createTurnBarrelButton();
	this->initCannon();
	this->setMagicCD(false);
	this->initMagicCDLabel();
	return true;
}

void ControllPanel::initBg()
{
	this->m_pBg = CCSprite::spriteWithFile("common/actor_controllBg.png");
	CCSize bgSize = this->m_pBg->getContentSize();
	this->m_pBg->setPosition(ccp(bgSize.width/2,bgSize.height/2));
	this->addChild(this->m_pBg);
}

void ControllPanel::initCannon()
{
	CCSize bgSize = this->m_pBg->getContentSize();
	this->m_pCannon = Cannon::createCannon();
	if (this->m_pCannon != NULL)
	{
		this->m_pCannon->getConnon()->setPosition(ccp(bgSize.width / 2+40, bgSize.height / 2));
		this->addChild(this->m_pCannon->getConnon());
	}
}

void ControllPanel::initMagicCDLabel()
{
	//添加倒计时Label
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerSkillCd();
	m_lMagicCDLabel = CCLabelTTF::labelWithString(ss.str().c_str(), "Arial", 30);
	m_lMagicCDLabel->setPosition(m_pMagicItem->getParent()->getPosition());
	this->addChild(m_lMagicCDLabel);
	m_lMagicCDLabel->setIsVisible(false);
}

CCPoint ControllPanel::getMuzzleWorldPos()
{
	return this->m_pCannon->getMuzzleWorldPos();
}

float ControllPanel::getConnonBarrelRotation()
{
	return this->m_pCannon->getBarrelRotation();
}

void ControllPanel::createAttackButton()
{
	std::string nameOne = "";
	std::string nameTwo = "";
#if defined LANG_CH
	nameOne = "common/actor_btn_noramlAtt.png";
	nameTwo = "common/actor_btn_magicAtt.png";
#else
	nameOne = "En/actor_btn_noramlAtt.png";
	nameTwo = "En/actor_btn_magicAtt.png";
#endif
	//普通攻击item
	CCMenuItemImage *pNormalItem = CCMenuItemImage::itemFromNormalImage(
		nameOne.c_str(),
		nameOne.c_str(),
		this,
		menu_selector(ControllPanel::normalAttackClick));
	//魔法攻击item
	m_pMagicItem = CCMenuItemImage::itemFromNormalImage(
		nameTwo.c_str(),
		nameTwo.c_str(),
		this,
		menu_selector(ControllPanel::magicAttackClick));

	CCMenu *pNormalAttMenu = CCMenu::menuWithItem(pNormalItem);
	CCMenu *pMagicAttMenu = CCMenu::menuWithItem(m_pMagicItem);

	CCSize bgSize = this->m_pBg->getContentSize();


	pNormalAttMenu->setPosition(ccp(bgSize.width - 200, bgSize.height / 2));
	pMagicAttMenu->setPosition(ccp(pNormalAttMenu->getPosition().x + 120, pNormalAttMenu->getPosition().y));

	this->addChild(pNormalAttMenu);
	this->addChild(pMagicAttMenu);

}

void ControllPanel::createPauseButton()
{
	std::string nameOne = "";
#if defined LANG_CH 
	nameOne = "common/actor_btn_pause.png";
#else 
	nameOne = "En/actor_btn_pause.png";
#endif
	CCMenuItemImage *pPauseItem = CCMenuItemImage::itemFromNormalImage(
		nameOne.c_str(),
		nameOne.c_str(),
		this,
		menu_selector(ControllPanel::pauseBtnClick));

	CCMenu *pPauseMenu = CCMenu::menuWithItem(pPauseItem);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pPauseMenu->setPosition(ccp(winSize.width-50, winSize.height-50));
	this->addChild(pPauseMenu);
}

void ControllPanel::createTurnBarrelButton()
{
	CCMenuItemImage *pTurnLeftItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_turnLeft.png",
		"common/actor_btn_turnLeft.png",
		this,
		menu_selector(ControllPanel::barrelTurnLeftClick));

	CCMenuItemImage *pTurnRightItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_turnRight.png",
		"common/actor_btn_turnRight.png",
		this,
		menu_selector(ControllPanel::barrelTurnRightClick));
	CCMenu *pTurnBarrelMenu = CCMenu::menuWithItems(pTurnLeftItem, pTurnRightItem, NULL);
	
	CCSize bgSize = this->m_pBg->getContentSize();
	pTurnBarrelMenu->alignItemsVertically();
	pTurnBarrelMenu->setPosition(ccp(100, bgSize.height / 2));
	this->addChild(pTurnBarrelMenu);
}


void ControllPanel::makeSkillCD(CCObject *pSender)
{
	CCLog("makeSkillCD");
	//进入CD状态
	this->setMagicCD(true);
	//设置按钮不可用
	m_pMagicItem->setIsEnabled(false);

	//创建技能cd样式
	CCProgressTimer *cd = CCProgressTimer::progressWithFile("common/actor_btn_mask.png");
	cd->setType(kCCProgressTimerTypeRadialCCW);
	cd->setPosition(m_pMagicItem->getParent()->getPosition());
	cd->setPercentage(99.99f);
	this->addChild(cd, 1000);
	//技能冷却动画
	CCProgressTo *to = CCProgressTo::actionWithDuration(PlayerMrg::getInstance()->getPlayer()->getPlayerSkillCd(), 0);
	//冷却完成之后的回调，销毁对象，同时使技能按钮可用
	CCCallFuncND *callfunn = CCCallFuncND::actionWithTarget(this, callfuncND_selector(ControllPanel::endSkillCD), (void*)cd);
	 
	cd->runAction(CCSequence::actions(to, callfunn, NULL));

	m_lMagicCDLabel->setIsVisible(true);
	schedule(schedule_selector(ControllPanel::updateCountDown), 1.0f);

}

void ControllPanel::endSkillCD(CCNode* sender, void* cd)
{
	CCLog("endSkillCD");
	m_pMagicItem->setIsEnabled(true);
	((CCProgressTimer*)cd)->removeFromParentAndCleanup(true);
	this->setMagicCD(false);
	unschedule(schedule_selector(ControllPanel::updateCountDown));
	m_lMagicCDLabel->setIsVisible(false);
	stringstream ss;
	ss << PlayerMrg::getInstance()->getPlayer()->getPlayerSkillCd();
	m_lMagicCDLabel->setString(ss.str().c_str());
}


void ControllPanel::updateCountDown(float dt)
{
	stringstream ss;
	stringstream ss1;
	int time;
	ss << m_lMagicCDLabel->getString();
	ss >> time;
	time = time - 1;
	if (time <= 0)	time = 0;
	ss1 << time;
	m_lMagicCDLabel->setString(ss1.str().c_str());
}

void ControllPanel::barrelTurnLeftClick(CCObject *pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_LEFT);
}

void ControllPanel::barrelTurnRightClick(CCObject *pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_TURN_RIGHT);
}

void ControllPanel::pauseBtnClick(CCObject* pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PAUSE_GAME);
}

void ControllPanel::normalAttackClick(CCObject* pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_FIRE);
}

void ControllPanel::magicAttackClick(CCObject* pSender)
{
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_BARREL_MAGIC_FIRE);
}