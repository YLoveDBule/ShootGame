#pragma once
#include "cocos2d.h"
#include "Cannon.h"

USING_NS_CC;

class ControllPanel : public CCLayer {
	
public:
	static ControllPanel* createControllPanel();
	virtual ~ControllPanel();
private:
	CCSprite* m_pBg;		//����̨����
	Cannon* m_pCannon;		//����̨��ũ��
	CCMenu* m_pNormalAttack;	//����̨��ͨ������ť
	CCMenu* m_pMagicAttack;		//����̨ħ��������ť
	
	ControllPanel();
	bool initControllPanel();
	void initBg();
	void initCannon();
	void createAttackButton();
	virtual void normalAttackClick(CCObject* pSender);
	virtual void magicAttackClick(CCObject* pSender);
};