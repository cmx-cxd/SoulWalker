#pragma once
#ifndef __HelpScene_H__  
#define __HelpScene_H__  

#include "cocos2d.h"  
//����һ��SceneTestLayer��̳���cocos2d��Layer��  
class HelpScene : public cocos2d::Layer
{
public:
	//���캯��  
	HelpScene();
	//��ʼ������  
	bool init();
	//���������溯��  
	void backToMainScene(Ref* sender);
	//����SceneTestLayer���  
	CREATE_FUNC(HelpScene)
};
#endif  