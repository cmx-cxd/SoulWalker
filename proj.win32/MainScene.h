#pragma once
#ifndef __MainScene_H__  
#define __MainScene_H__  

#include "cocos2d.h"  


//����һ��MainScene��̳���cocos2d��Layer��  
class MainScene : public cocos2d::Layer
{
public:
	//��ʼ���������������������  
	virtual bool init();
	//����һ������  
	static cocos2d::Scene* createScene();
	//ת����Ϸ����  
	void onPushSceneGame(Ref* pSender);
	//ת����������  
	void onPushSceneHelp(Ref* pSender);
	//ת�����ڽ���
	void onPushSceneAbout(Ref* pSender);
	//�رշ���  
	void menuCloseCallback(Ref* pSender);
	//����������  
	CREATE_FUNC(MainScene);
};
#endif // __HELLOWORLD_SCENE_H__