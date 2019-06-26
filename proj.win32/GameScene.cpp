#include "GameScene.h"
#include "Config.h"
//#include "AnimationScene/AnimationScene.h"
Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_isJump = false;
	//m_jumpDir = Dir::STOP;
	m_jumpSpeed = PLAYER_JUMP_SPEED;
	m_gameOver = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 加载地图
	loadMap(MAP_TMX_FILE_PATH);

	// 添加玩家
	addPlayer(Vec2(80, 40));

	// 游戏逻辑
	this->scheduleUpdate();

	// 添加触屏侦听
	addTouchListener();

	return true;
}
void GameScene::update(float t)
{
	auto player = this->getChildByTag(PLAYER_TAG);
	auto map = (TMXTiledMap *)getChildByTag(MAP_TAG);

	// 玩家相对于屏幕的坐标
	float player_screen_x = player->getPositionX();
	float player_screen_y = player->getPositionY() - player->getContentSize().height / 2;

	// 地图相对于屏幕的x坐标
	float map_screen_x = abs(map->getPositionX());
	float map_screen_y = 0;

	// 玩家相对于地图的坐标
	float player_map_x = player_screen_x + map_screen_x;
	float player_map_y = player_screen_y + map_screen_y;

	// 不跳动时遇到非地面图块自动下落
	if ((int)(player_map_y / map->getTileSize().width) >= 0)
	{
		int playerTiledID = map->getLayer(MAP_BG_LAYER_NAME)->getTileGIDAt(Vec2((int)(player_map_x / map->getTileSize().width), (int)(map->getMapSize().height - 1 - player_map_y / map->getTileSize().height)));
		if ((m_isJump == false) && (m_jumpDir == Dir::STOP) && (playerTiledID != 8) && (playerTiledID != 7)
			&& (playerTiledID != 151) && (playerTiledID != 170) && (playerTiledID != 171) && (playerTiledID != 172) && (playerTiledID != 149) && (playerTiledID != 133)) {
			m_isJump = true;
			m_jumpDir = Dir::DOWN;
			m_jumpSpeed = 2;
		}
	}

	// 处理玩家的跳跃
	if (m_isJump) {
		if (m_jumpDir == Dir::UP) {
			player->setPositionY(player->getPositionY() + m_jumpSpeed);
			m_jumpSpeed -= 2;
			if (m_jumpSpeed <= 0)
			{
				m_jumpDir = Dir::DOWN;
			}
		}
		else if (m_jumpDir == Dir::DOWN)
		{
			// 用于记录玩家是否落到地面上
			bool check = false;

			for (int i = 0; i < m_jumpSpeed; i += 2) {

				// 计算当前玩家相对于地图的坐标
				float player_screen_x = player->getPositionX();
				float player_screen_y = player->getPositionY() - player->getContentSize().height / 2 + i;

				// 地图相对于屏幕的x坐标
				float map_screen_x = abs(map->getPositionX());
				float map_screen_y = 0;

				// 玩家相对于地图的坐标
				float player_map_x = player_screen_x + map_screen_x;
				float player_map_y = player_screen_y + map_screen_y;

				// 获取玩家脚下的地图块的编号
				if (player_map_y / map->getTileSize().width >= 0) {

					int tiledID = map->getLayer(MAP_BG_LAYER_NAME)->getTileGIDAt(Vec2((int)(player_map_x / map->getTileSize().width), (int)(map->getMapSize().height - 1 - player_map_y / map->getTileSize().height)));
					if (tiledID == 8 || tiledID == 7 || tiledID == 151 || tiledID == 170 || tiledID == 171 || tiledID == 172 || tiledID == 149 || tiledID == 133) {
						check = true;
						player->setPositionY((int)(player_screen_y + player->getContentSize().height / 2 - 6));
						m_jumpSpeed = PLAYER_JUMP_SPEED;
						m_jumpDir = Dir::STOP;
						m_isJump = false;
						break;
					}
				}
				if (!check)
				{
					player->setPositionY(player->getPositionY() - m_jumpSpeed);
					m_jumpSpeed += 2;
					if (m_jumpSpeed > PLAYER_JUMP_SPEED)
					{
						m_jumpSpeed = PLAYER_JUMP_SPEED;
					}
				}
			}
		}
		this->getChildByTag(MAP_TAG)->setPositionX(this->getChildByTag(MAP_TAG)->getPositionX() - 3);
		// 滚动背景地图
		int mapWidth = map->getMapSize().width*map->getTileSize().width;
		int visibleWidth = Director::getInstance()->getWinSize().width;
		if (map->getPositionX() < -(mapWidth - visibleWidth))
		{
			map->setPositionX(-(mapWidth - visibleWidth));
			// 地图静止后移动角色
			player->setPositionX(player->getPositionX() + 3);
			if (player->getPositionX() > visibleWidth)
			{
				player->setPositionX(visibleWidth);
				this->unscheduleUpdate();
				this->removeChildByTag(PLAYER_TAG);
				success();
				return;
			}
		}
	}
}

	void GameScene::addPlayer(Vec2 pos)//似乎是不需要的？hero.cpp可以实现吧
	{
		// 玩家跑动动画
		ArmatureDataManager::getInstance()->addArmatureFileInfo("resources/animation/Hero.ExportJson");
		m_armature = Armature::create("Hero");
		if (m_armature == NULL)
		{
			CCLOG("hero load error!");
		}
		m_armature->getAnimation()->play("stand");//三个动作为stand,walk,air
		// 添加玩家
		auto hero = Sprite::create();
		hero->setTag(HERO_TAG);
		this->addChild(hero, LAYER_2);
		hero->setPosition(pos);
	}

//加载地图
	void GameScene::loadMap(std::string mapPath)
	{
		// 加载地图
		auto map = TMXTiledMap::create(mapPath);
		if (map != NULL)
		{
			this->addChild(map, 2);
			map->setTag(MAP_TAG);
			map->setPosition(Vec2(0, 0));
		}
		else
		{
			CCLOG("load map failed!");
			return;
		}
	}


//触摸监听
void GameScene::addTouchListener()
{
		// 加入触摸的处理
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

//键盘监听
void addKeyboardListener()
{
	//auto *listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	//这是示范
	//键盘按下的操作
	if (keycode == EventKeyboard::KeyCode::KEY_R)
	{
		CCLOG("R pressed\n");
	}
}