#include "ControllPanel.h"
#include "cocos2d.h"
#include "Cannon.h"
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
}

void ControllPanel::onExit()
{
	CCLayer::onExit();
	delete(this->m_pCannon);
}

ControllPanel::ControllPanel(){}
ControllPanel::~ControllPanel(){}

bool ControllPanel::initControllPanel()
{
	this->initBg();
	this->createAttackButton();
	this->initCannon();
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
	//ÆÕÍ¨¹¥»÷item
	CCMenuItemImage *pNormalItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_noramlAtt.png",
		"common/actor_btn_noramlAtt.png",
		this,
		menu_selector(ControllPanel::normalAttackClick));
	//ÆÕÍ¨¹¥»÷item
	CCMenuItemImage *pMagicItem = CCMenuItemImage::itemFromNormalImage(
		"common/actor_btn_magicAtt.png",
		"common/actor_btn_magicAtt.png",
		this,
		menu_selector(ControllPanel::magicAttackClick));
	CCMenu *pAttackMenu = CCMenu::menuWithItems(pNormalItem, pMagicItem, NULL);
	
	CCSize bgSize = this->m_pBg->getContentSize();

	pAttackMenu->alignItemsHorizontally();
	pAttackMenu->setPosition(ccp(bgSize.width - 200, bgSize.height / 2 - pNormalItem->getContentSize().height / 2 - 30));
	this->addChild(pAttackMenu);

}

void ControllPanel::normalAttackClick(CCObject* pSender)
{
	CCLog("normalAttackClick!!");
}

void ControllPanel::magicAttackClick(CCObject* pSender)
{
	CCLog("magicAttackClick!!");

}