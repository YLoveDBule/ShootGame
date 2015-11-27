#pragma once

#include "cocos2d.h"
USING_NS_CC;

enum MenuTag
{
	MenuTag_Parent = 100,
	MenuTag_Star = 101,
	MenuTag_Exit = 102,
};

enum MenuState
{
	MenuState_Begin = 0,
    MenuState_Star = 1,
	MenuState_Exit = 2,
	MenuState_End = 3,
};

#define ROW_TAG 200
class LoginScene : public cocos2d::CCLayer ,public CCKeypadDelegate
	               
{
public:
	virtual bool init();
	static CCScene* scene();

	virtual bool keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus key_status);
	LAYER_NODE_FUNC(LoginScene);
	virtual void onEnter();
	virtual void onExit();
	void resumeGame(CCObject *pSender);
protected:
	void onClickA(cocos2d::CCKeypadStatus key_status);
	void onClickS(cocos2d::CCKeypadStatus key_status);
	void onClickD(cocos2d::CCKeypadStatus key_status);
	void onClickW(cocos2d::CCKeypadStatus key_status);

	void onClickI(cocos2d::CCKeypadStatus key_status);
	void onClickL(cocos2d::CCKeypadStatus key_status);
	void onClickJ(cocos2d::CCKeypadStatus key_status);
	void onClickK(cocos2d::CCKeypadStatus key_status);

	virtual void clickStar(CCObject* pSender);
	virtual void clickExit(CCObject* pSender);


	void ChangeRowPosition();
	void musicBtnClick(CCObject *pSender);
	void setMusicBtnState();
private:
	CCMenuItemImage *_pStarMenu;
	CCMenuItemImage *_pExitMenu;
	CCMenuItemSprite *m_pMusicItem;
	MenuState _nowSate;
	CCSprite *_rowSp;
};