#include "MonsterMrg.h"
#include <sstream>
#include "Config\NotificationNameConfig.h"

MonsterMrg::MonsterMrg()
{
	InitMonsterData();
}

MonsterMrg::~MonsterMrg()
{

}

void MonsterMrg::DestroyMonster()
{
	removeFromParentAndCleanup(true);
	//֪ͨ
	stringstream stream;
	stream >> _SkillGrade;
	CCString str = CCString(stream.str().c_str());
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);
	stream.str("");
	stream.clear();
	if (_SkillReward != 0)
	{
		stream >> _SkillReward;
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATENOWHP, &str);
	}
	stream.str("");
	stream.clear();
}


////////////               A      ////////////

