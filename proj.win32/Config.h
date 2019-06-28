#pragma once
//游戏的各种参数设置
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;
USING_NS_CC;

//图层？当作ps的图层就好了
#define LAYER_0 0//背景
#define LAYER_1 1//按钮等
#define LAYER_2 2//hero?
#define LAYER_3 3
#define LAYER_4 4
#define LAYER_5 5

#define HERO_TAG 100
#define AIM_TAG 101
#define SOUL_TAG 102
#define BRICK_TILE 432//大概id是431？

static const int PLAYER_TAG = 110;  // player tag
static const int MAP_TAG = 111;     // map tag
static int PLAYER_WIDTH = 100;		// player img width
static int PLAYER_HEIGHT = 100;	    // player img height
static int PLAYER_JUMP_SPEED = 30;  // player jump speed

static string MAP_TMX_FILE_PATH = "resources/level1.tmx";
static string MAP_BG_LAYER_NAME = "back";  // map background layer name

static int MAP_FLOUR_NUM = 6;
static int MAP_FLOUR[] = { 7,8,151,170,171,172 };

// player img path

enum Dir
{
	STOP,
	UP,
	DOWN
};

enum State
{
	STAND,
	WALK,
    AIR
};

#endif