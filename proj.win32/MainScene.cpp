//����࿪ʼ����Ŀ���ɵ�ʱ����helloworld�࣬�����Ҹ���һ��  
#include "MainScene.h"  
#include "Config.h"
#include "HelpScene.h"
#include "AboutScene.h"
//��Ŀ�е�����NewScene������Ҫ����  
//#include "NewScene.h"  
//#include "GameScene.h"  
USING_NS_CC;
//����������  
Scene* MainScene::createScene()
{
	//ʹ�ó����ഴ��һ������  
	auto scene = Scene::create();
	//����һ��MainScene��  
	MainScene *layer = MainScene::create();
	//�Ѳ���ӵ���������ȥ  
	scene->addChild(layer);
	// ����һ������  
	return scene;
}

// ��ʼ��һ��MainScene��  
bool MainScene::init()
{
	//��ĳ�ʼ���Ƿ�ɹ�  
	if (!Layer::init())
	{
		return false;
	}
	//��ȡ����ϵ�������Ļ�ɼ�����  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ԭ��λ��  
	Point origin = Director::getInstance()->getVisibleOrigin();
	//����һ���رհ�ť�������ֱ�Ϊ������״̬��ʾ��ͼƬ��ѡ��״̬��ͼƬ���������õķ���������MainScene��menuCloseCallback����  
	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	//���ùرհ�ť��λ��Ϊ��ͼ�����·�  
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
		
	//�����˵�����ע�⣬���һ������һ����NULL  
	auto menu = Menu::create(closeItem, NULL);
	//��ʼ���˵���λ��Ϊԭ��λ�ã������Ҳ��Ҫ�Ҹ�ʱ�������  
	menu->setPosition(Point::ZERO);
	//�Ѳ˵���ӵ�����  
	this->addChild(menu, 1);
	*/
	 //��ӱ���ͼ
	auto bg = Sprite::create("resources/menu_background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, LAYER_0);

	//��ӿ�ʼ��Ϸͼ(onPushSceneGame)
	auto gameStart = MenuItemImage::create("resources/button_start_up.png", "resources/button_start_down.png", CC_CALLBACK_1(MainScene::onPushSceneGame, this));
	gameStart->setPosition(Point(200 ,80));
	
	//�����Ϸ˵��ͼ(onPushSceneHelp)
	auto help= MenuItemImage::create("resources/button_help_up.png", "resources/button_help_down.png", CC_CALLBACK_1(MainScene::onPushSceneHelp, this));
	help->setPosition(Point(200, -30));
	
	//���������Աͼ(onPushSceneAbout)
	auto about= MenuItemImage::create("resources/button_about_up.png", "resources/button_about_down.png", CC_CALLBACK_1(MainScene::onPushSceneAbout, this));
	about->setPosition(Point(200, -140));

	//��Ӱ�ť
	auto menu_oper = Menu::create(gameStart,help,about, NULL);
	this->addChild(menu_oper, LAYER_1);

	return true;
}

//������Ϸ�ķ���
void MainScene::onPushSceneGame(Ref* pSender) {
	/*
	auto scene = Scene::create();
	scene->addChild(SceneTestLayer::create());
	Director::getInstance()->replaceScene(TransitionFlipX::create(.5, scene));
	*/
}

//��������ķ���
void MainScene::onPushSceneHelp(Ref* pSender) {
	
	auto scene = Scene::create();
	scene->addChild(HelpScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//����Ϊ����
	
}

//������ڵķ���
void MainScene::onPushSceneAbout(Ref* pSender) {
	auto scene = Scene::create();
	scene->addChild(AboutScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//����Ϊ����
}

/**
 * �ر��Ӵ��ķ���
 * �����ǹٷ�����õ�һ���꣬��˼���ǣ���ƽ̨Ϊwp8����winRT�ᵯ����
 */
void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif  
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	exit(0);
#endif  
}