#pragma once
#ifndef __AboutScene_H__  
#define __AboutScene_H__  

#include "cocos2d.h"  
//����һ��SceneTestLayer��̳���cocos2d��Layer��  
class AboutScene : public cocos2d::Layer
{
public:
	//���캯��  
	AboutScene();
	//��ʼ������  
	bool init();
	//���������溯��  
	void backToMainScene(Ref* sender);
	//����SceneTestLayer���  
	CREATE_FUNC(AboutScene)
};
#endif  