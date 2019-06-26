#pragma once
#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Config.h"
USING_NS_CC;

using namespace cocos2d::ui;
//游戏场景类定义
class GameScene : public cocos2d::Layer
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	// 加载地图
	void loadMap(std::string mapPath);

	// 显示人物
	void addPlayer(Vec2 pos);

	// 添加触屏侦听
	void addTouchListener();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	//添加键盘监听
	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);

	// 游戏逻辑
	void update(float t);

	void gameOver();
	void success();
	Armature* getArmature() { return m_armature; }

	bool m_gameOver; // 游戏是否结束
	Dir m_jumpDir;   // 表示精灵的方向 1，up 2 down
	bool m_inAir;//精灵是否在空中
	int m_jumpSpeed; // 跳跃速度
	bool m_isJump;   // 表示是否精灵在跳跃，如果跳跃不处理屏幕的触摸（个人觉得没必要，但是先留着）

	//骨骼动画
	Armature* m_armature;
};

#endif // __HELLOWORLD_SCENE_H__