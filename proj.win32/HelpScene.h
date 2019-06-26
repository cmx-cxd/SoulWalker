#pragma once
#ifndef __HelpScene_H__  
#define __HelpScene_H__  

#include "cocos2d.h"  
//创建一个SceneTestLayer类继承自cocos2d的Layer类  
class HelpScene : public cocos2d::Layer
{
public:
	//构造函数  
	HelpScene();
	//初始化函数  
	bool init();
	//返回主界面函数  
	void backToMainScene(Ref* sender);
	//创建SceneTestLayer层宏  
	CREATE_FUNC(HelpScene)
};
#endif  