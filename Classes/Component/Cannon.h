#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Cannon : public CCObject{
public:

	static Cannon* createCannon();

	void rotateToPoint(CCPoint pt);

	virtual ~Cannon();

	CCLayer* getConnon();

	float getBarrelRotation();

	CCPoint getMuzzleWorldPos();		//�ڿڵ���������

	//static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);

private:
	Cannon();

	float m_fRotation;
	CCSprite *m_pBarrel;		//�ڹ�
	CCSprite *m_pPedestal;		//����
	CCLayer *m_pCannon;
	CCPoint m_pDirection;
	void  setRotationLeft(CCObject *pSender);
	void  setRotationRight(CCObject *pSender);
	void fire(CCObject *pSender);
	void magicFire(CCObject *pSender);
	void setRotation(float rotation);
	bool initCannon();	
	void barrelToZero(CCObject *pSender);
};