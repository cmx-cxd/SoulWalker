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

	// ���ص�ͼ
	loadMap(MAP_TMX_FILE_PATH);

	// ������
	addPlayer(Vec2(80, 40));

	// ��Ϸ�߼�
	this->scheduleUpdate();

	// ��Ӵ�������
	addTouchListener();

	return true;
}
void GameScene::update(float t)
{
	auto player = this->getChildByTag(PLAYER_TAG);
	auto map = (TMXTiledMap *)getChildByTag(MAP_TAG);

	// ����������Ļ������
	float player_screen_x = player->getPositionX();
	float player_screen_y = player->getPositionY() - player->getContentSize().height / 2;

	// ��ͼ�������Ļ��x����
	float map_screen_x = abs(map->getPositionX());
	float map_screen_y = 0;

	// �������ڵ�ͼ������
	float player_map_x = player_screen_x + map_screen_x;
	float player_map_y = player_screen_y + map_screen_y;

	// ������ʱ�����ǵ���ͼ���Զ�����
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

	// ������ҵ���Ծ
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
			// ���ڼ�¼����Ƿ��䵽������
			bool check = false;

			for (int i = 0; i < m_jumpSpeed; i += 2) {

				// ���㵱ǰ�������ڵ�ͼ������
				float player_screen_x = player->getPositionX();
				float player_screen_y = player->getPositionY() - player->getContentSize().height / 2 + i;

				// ��ͼ�������Ļ��x����
				float map_screen_x = abs(map->getPositionX());
				float map_screen_y = 0;

				// �������ڵ�ͼ������
				float player_map_x = player_screen_x + map_screen_x;
				float player_map_y = player_screen_y + map_screen_y;

				// ��ȡ��ҽ��µĵ�ͼ��ı��
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
		// ����������ͼ
		int mapWidth = map->getMapSize().width*map->getTileSize().width;
		int visibleWidth = Director::getInstance()->getWinSize().width;
		if (map->getPositionX() < -(mapWidth - visibleWidth))
		{
			map->setPositionX(-(mapWidth - visibleWidth));
			// ��ͼ��ֹ���ƶ���ɫ
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

	void GameScene::addPlayer(Vec2 pos)//�ƺ��ǲ���Ҫ�ģ�hero.cpp����ʵ�ְ�
	{
		// ����ܶ�����
		ArmatureDataManager::getInstance()->addArmatureFileInfo("resources/animation/Hero.ExportJson");
		m_armature = Armature::create("Hero");
		if (m_armature == NULL)
		{
			CCLOG("hero load error!");
		}
		m_armature->getAnimation()->play("stand");//��������Ϊstand,walk,air
		// ������
		auto hero = Sprite::create();
		hero->setTag(HERO_TAG);
		this->addChild(hero, LAYER_2);
		hero->setPosition(pos);
	}

//���ص�ͼ
	void GameScene::loadMap(std::string mapPath)
	{
		// ���ص�ͼ
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


//��������
void GameScene::addTouchListener()
{
		// ���봥���Ĵ���
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

//���̼���
void addKeyboardListener()
{
	//auto *listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	//����ʾ��
	//���̰��µĲ���
	if (keycode == EventKeyboard::KeyCode::KEY_R)
	{
		CCLOG("R pressed\n");
	}
}