#pragma once
#ifndef __MainScene_H__  
#define __MainScene_H__  

#include "cocos2d.h"  


//创建一个MainScene类继承自cocos2d的Layer类  
class MainScene : public cocos2d::Layer
{
public:
	//初始化函数，我用来定义组件  
	virtual bool init();
	//创建一个场景  
	static cocos2d::Scene* createScene();
	//转场游戏界面  
	void onPushSceneGame(Ref* pSender);
	//转场帮助界面  
	void onPushSceneHelp(Ref* pSender);
	//转场关于界面
	void onPushSceneAbout(Ref* pSender);
	//关闭方法  
	void menuCloseCallback(Ref* pSender);
	//创建场景宏  
	CREATE_FUNC(MainScene);
};
#endif // __HELLOWORLD_SCENE_H__