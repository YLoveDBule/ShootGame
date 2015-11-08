#include "cocos2d.h"
USING_NS_CC;
class Utils {
public:
	static bool IsRectCollision(CCNode* obj1, CCNode* obj2);					//两物体矩形碰撞
	static bool IsRectContianPointCollision(CCNode* obj1, CCNode* obj2);		//一个物体是否包含另外一个物体的中心碰撞
	static float getPointToPointDisatance(CCPoint point1, CCPoint point2);		//两个点间的距离公式
};