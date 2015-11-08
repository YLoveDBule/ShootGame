#include "LoginScene.h"
#include "GameData/PlayerMrg.h"
#include "Component/GamingLayer.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/MonsterMrg.h"
bool LoginScene::init()
{
	_nowSate = MenuState_Star;
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bg = CCSprite::spriteWithFile("common/actor_gamingbg.png");
	bg->setPosition(ccp(size.width / 2, size.height / 2));
	addChild(bg);
	//logo
	CCSprite *logo = CCSprite::spriteWithFile("logo.png");
	logo->setPosition(ccp(size.width / 2, size.height / 2 + size.height / 4));
	addChild(logo);

	//chenbao
	CCSprite *chenbao = CCSprite::spriteWithFile("common/actor_controllBg.png");
	chenbao->setAnchorPoint(ccp(0, 0));
	addChild(chenbao);
	//menu
	_pStarMenu = CCMenuItemImage::itemFromNormalImage(
		"kaishi.png",
		NULL,
		this,
		menu_selector(LoginScene::clickStar));
	_pStarMenu->setPosition(ccp(size.width / 2, size.height / 2 - 15));
	_pExitMenu = CCMenuItemImage::itemFromNormalImage(
		"tuichu.png",
		NULL,
		this,
		menu_selector(LoginScene::clickExit));
	_pExitMenu->setPosition(ccp(size.width / 2, size.height / 2  - 20 - _pStarMenu->getContentSize().height));
	CCMenu *pMenu = CCMenu::menuWithItems(_pStarMenu, _pExitMenu, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCLayer::setIsKeypadEnabled(true); 


	//row
	_rowSp = CCSprite::spriteWithFile("shouzi.png");
	_rowSp->setAnchorPoint(ccp(1, 0.5));
	ChangeRowPosition();
	addChild(_rowSp);

	//init data 
	//PlayerMrg::getInstance()->Init();
	return true;
}

CCScene* LoginScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	LoginScene *layer = LoginScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoginScene::keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus iKeyState)
{
	switch (iKeyID)
	{
	case 'w':
	case 'W':
//	case KEY_UP:
		if (iKeyState == EVENT_KEY_DOWN)
		{
			onClickW(iKeyState);
		}
		break;
	case 's':
	case 'S':
//	case KEY_DOWN:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickS(iKeyState);
		break;
	case 'a':
	case 'A':
//	case KEY_LEFT:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickA(iKeyState);
		break;
	case 'd':
	case 'D':
//	case KEY_RIGHT:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickD(iKeyState);
		break;

	case 'i':
	case 'I':
//	case KEY_A:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickI(iKeyState);
		break;
	case 'k':
	case 'K':
//	case KEY_B:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickK(iKeyState);
		break;
	case 'l':
	case 'L':
//	case KEY_X:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickL(iKeyState);
		break;
	case 'j':
	case 'J':
//	case KEY_Y:
		if (iKeyState == EVENT_KEY_DOWN)
		    onClickJ(iKeyState);
		break;

	default:
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		break;
	}

	return true;
}

void LoginScene::onClickA(cocos2d::CCKeypadStatus key_status)
{

}

void LoginScene::onClickS(cocos2d::CCKeypadStatus key_status)
{
	_nowSate = MenuState(_nowSate + 1);
	if (_nowSate == MenuState_End)
	{
		_nowSate = MenuState_Star;
	}
	ChangeRowPosition();
}

void LoginScene::onClickD(cocos2d::CCKeypadStatus key_status)
{

}

void LoginScene::onClickW(cocos2d::CCKeypadStatus key_status)
{
	_nowSate = MenuState(_nowSate - 1);
	if (_nowSate == MenuState_Begin)
	{
		_nowSate = MenuState_Exit;
	}
	ChangeRowPosition();
}

void LoginScene::onClickI(cocos2d::CCKeypadStatus key_status)
{

}

void LoginScene::onClickL(cocos2d::CCKeypadStatus key_status)
{

}

void LoginScene::onClickJ(cocos2d::CCKeypadStatus key_status)
{
	switch (_nowSate)
	{
	case MenuState_Star:
	{
		PlayerMrg::getInstance()->Init();		
		CCScene *scene = CCScene::node();
		GamingLayer*layer = GamingLayer::createGamingLayer();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
		//PlayerMrg::getInstance()->Init();
		/*CCString str = CCString("100");
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);*/
		/*MonsterMrg *monster = MonsterMrg::Create(1001);
		addChild(monster);*/
	}
		break;
	case MenuState_Exit:
	{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
		break;
	default:
		break;
	}
}

void LoginScene::onClickK(cocos2d::CCKeypadStatus key_status)
{

}

void LoginScene::clickStar(CCObject* pSender)
{
	CCLog("sart");
}

void LoginScene::clickExit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void LoginScene::ChangeRowPosition()
{
	switch (_nowSate)
	{
	case MenuState_Star:
	    {
			_rowSp->setPosition(ccp(_pStarMenu->getPosition().x - _pStarMenu->getContentSize().width / 2 - 20, _pStarMenu->getPosition().y));
	    }
		break;
	case MenuState_Exit:
	   {
		   _rowSp->setPosition(ccp(_pExitMenu->getPosition().x - _pExitMenu->getContentSize().width / 2 - 20, _pExitMenu->getPosition().y));
	   }
		break;
	default:
		break;
	}
}
