#pragma once
#include "cocos2d.h"
#include "Cannon.h"

USING_NS_CC;

class ControllPanel : public CCLayer {
	
public:
	static ControllPanel* createControllPanel();
	virtual ~ControllPanel();
	CCPoint getMuzzleWorldPos();
	float getConnonBarrelRotation();
	virtual void onEnter();
	virtual void onExit();
	CC_SYNTHESIZE(bool, m_bMagicCDing, MagicCD)
private:
	CCSprite* m_pBg;		//����̨����
	Cannon* m_pCannon;		//����̨��ũ��
	CCMenuItemImage *m_pMagicItem;
	
	ControllPanel();
	bool initControllPanel();
	void initBg();
	void initCannon();
	void createAttackButton();
	void createPauseButton();
	void createTurnBarrelButton();	//�ƶ��ڹܰ�ť
	void barrelTurnLeftClick(CCObject *pSender);
	void barrelTurnRightClick(CCObject *pSender);
	virtual void normalAttackClick(CCObject* pSender);
	virtual void magicAttackClick(CCObject* pSender);
	virtual void pauseBtnClick(CCObject* pSender);

	void makeSkillCD(CCObject *pSender); //������ȴ
	void endSkillCD(CCNode* sender, void *item);
};