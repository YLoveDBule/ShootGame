#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ResulitLayer : public CCLayer, public CCKeypadDelegate
{
public:
	static ResulitLayer *create();
	~ResulitLayer();
	bool initResulitLayer();
	void restartGame(CCObject *pSender);
	void menuExitCallBack(CCObject *pSender);
	virtual bool keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus key_status);

	void onClickA(cocos2d::CCKeypadStatus key_status);
	void onClickS(cocos2d::CCKeypadStatus key_status);
	void onClickD(cocos2d::CCKeypadStatus key_status);
	void onClickW(cocos2d::CCKeypadStatus key_status);

	void onClickI(cocos2d::CCKeypadStatus key_status);
	void onClickL(cocos2d::CCKeypadStatus key_status);
	void onClickJ(cocos2d::CCKeypadStatus key_status);
	void onClickK(cocos2d::CCKeypadStatus key_status);

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
	ResulitLayer();
};