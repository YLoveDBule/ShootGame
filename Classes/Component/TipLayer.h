#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TipLayer : public CCLayer
{
public:
	static TipLayer* Create();
	virtual ~TipLayer();
	virtual bool keyAllClicked(int iKeyID, CCKeypadStatus key_status);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
protected:
	void onClickA(cocos2d::CCKeypadStatus key_status);
	void onClickS(cocos2d::CCKeypadStatus key_status);
	void onClickD(cocos2d::CCKeypadStatus key_status);
	void onClickW(cocos2d::CCKeypadStatus key_status);

	void onClickI(cocos2d::CCKeypadStatus key_status);
	void onClickL(cocos2d::CCKeypadStatus key_status);
	void onClickJ(cocos2d::CCKeypadStatus key_status);
	void onClickK(cocos2d::CCKeypadStatus key_status);
private:
	TipLayer();
	bool initTipLayer();
	void cancel(CCObject *pSender);
	void confirm(CCObject *pSender);
};