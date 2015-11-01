#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Cannon : public CCObject{
public:

	static Cannon* createCannon();

	void rotateToPoint(CCPoint pt);

	void fire();

	virtual ~Cannon();

	CCLayer* getConnon();

	static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);

private:
	Cannon();

	float m_fRotation;
	CCSprite *m_pBarrel;		//ÅÚ¹Ü
	CCSprite *m_pPedestal;		//µ××ù
	CCLayer *m_pCannon;
	CCPoint m_pDirection;
	void  setRotationLeft(CCObject *pSender);
	void  setRotationRight(CCObject *pSender);
	void setRotation(float rotation);
	bool initCannon();
	
};