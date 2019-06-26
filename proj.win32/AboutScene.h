#pragma once
#ifndef __AboutScene_H__  
#define __AboutScene_H__  

#include "cocos2d.h"  
//创建一个SceneTestLayer类继承自cocos2d的Layer类  
class AboutScene : public cocos2d::Layer
{
public:
	//构造函数  
	AboutScene();
	//初始化函数  
	bool init();
	//返回主界面函数  
	void backToMainScene(Ref* sender);
	//创建SceneTestLayer层宏  
	CREATE_FUNC(AboutScene)
};
#endif  