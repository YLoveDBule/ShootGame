#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PauseLayer : public CCLayer
{
public:
	static PauseLayer* Create();
	virtual ~PauseLayer();
	virtual bool keyAllClicked(int iKeyID, CCKeypadStatus key_status);
	virtual void onEnter();
	virtual void onExit();
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
	PauseLayer();
	bool initPauseLayer();
	void continueGame(CCObject *pSender);
	void restartGame(CCObject *pSender);
	void exitGame(CCObject *pSender);
};