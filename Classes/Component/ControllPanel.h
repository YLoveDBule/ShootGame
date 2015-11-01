#pragma once
#include "cocos2d.h"
#include "Cannon.h"

USING_NS_CC;

class ControllPanel : public CCLayer {
	
public:
	static ControllPanel* createControllPanel();
	virtual ~ControllPanel();
private:
	CCSprite* m_pBg;		//操作台背景
	Cannon* m_pCannon;		//操作台加农炮
	CCMenu* m_pNormalAttack;	//操作台普通攻击按钮
	CCMenu* m_pMagicAttack;		//操作台魔法攻击按钮
	
	ControllPanel();
	bool initControllPanel();
	void initBg();
	void initCannon();
	void createAttackButton();
	virtual void normalAttackClick(CCObject* pSender);
	virtual void magicAttackClick(CCObject* pSender);
};