#include "ControllPanel.h"
#include "cocos2d.h"
#include "Cannon.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/PlayerMrg.h"
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
	//��ͨ����item
	CCMenuItemImage *pNormalItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_noramlAtt.png",
		"common/actor_btn_noramlAtt.png",
		this,
		menu_selector(ControllPanel::normalAttackClick));
	//ħ������item
	m_pMagicItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_magicAtt.png",
		"common/actor_btn_magicAtt.png",
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
	CCMenuItemImage *pPauseItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_pause.png",
		"common/actor_btn_pause.png",
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
	//����CD״̬
	this->setMagicCD(true);
	//���ð�ť������
	m_pMagicItem->setIsEnabled(false);
	//��������cd��ʽ
	CCProgressTimer *cd = CCProgressTimer::progressWithFile("common/actor_btn_pause.png");
	cd->setType(kCCProgressTimerTypeRadialCCW);
	cd->setPosition(m_pMagicItem->getParent()->getPosition());
	cd->setPercentage(99.99f);
	this->addChild(cd, 1000);
	//������ȴ����
	CCProgressTo *to = CCProgressTo::actionWithDuration(PlayerMrg::getInstance()->getPlayer()->getPlayerSkillCd(), 0);
	//��ȴ���֮��Ļص������ٶ���ͬʱʹ���ܰ�ť����
	CCCallFuncND *callfunn = CCCallFuncND::actionWithTarget(this, callfuncND_selector(ControllPanel::endSkillCD), (void*)cd);
	 
	cd->runAction(CCSequence::actions(to, callfunn, NULL));
}

void ControllPanel::endSkillCD(CCNode* sender, void* cd)
{
	CCLog("endSkillCD");
	m_pMagicItem->setIsEnabled(true);
	((CCProgressTimer*)cd)->removeFromParentAndCleanup(true);
	this->setMagicCD(false);
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