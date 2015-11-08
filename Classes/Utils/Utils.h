#include "cocos2d.h"
USING_NS_CC;
class Utils {
public:
	static bool IsRectCollision(CCNode* obj1, CCNode* obj2);					//Á½ÎïÌå¾ØÐÎÅö×²
	static bool IsRectContianPointCollision(CCNode* obj1, CCNode* obj2);		//Ò»¸öÎïÌåÊÇ·ñ°üº¬ÁíÍâÒ»¸öÎïÌåµÄÖÐÐÄÅö×²
	static float getPointToPointDisatance(CCPoint point1, CCPoint point2);		//Á½¸öµã¼äµÄ¾àÀë¹«Ê½
	static void InitLoadPlist(const char *fileName);
};