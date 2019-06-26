//这个类开始在项目生成的时候是helloworld类，这里我改了一下  
#include "MainScene.h"  
#include "Config.h"
#include "HelpScene.h"
#include "AboutScene.h"
//项目中调用了NewScene所以需要引用  
//#include "NewScene.h"  
//#include "GameScene.h"  
USING_NS_CC;
//创建主场景  
Scene* MainScene::createScene()
{
	//使用场景类创建一个场景  
	auto scene = Scene::create();
	//创建一个MainScene层  
	MainScene *layer = MainScene::create();
	//把层添加到场景里面去  
	scene->addChild(layer);
	// 返回一个场景  
	return scene;
}

// 初始化一个MainScene层  
bool MainScene::init()
{
	//层的初始化是否成功  
	if (!Layer::init())
	{
		return false;
	}
	//获取坐标系界面的屏幕可见区域  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//原点位置  
	Point origin = Director::getInstance()->getVisibleOrigin();
	//创建一个关闭按钮，参数分别为，正常状态显示的图片，选中状态的图片，操作调用的方法即调用MainScene的menuCloseCallback方法  
	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	//设置关闭按钮的位置为视图的右下方  
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
		
	//创建菜单，请注意，最后一个参数一定是NULL  
	auto menu = Menu::create(closeItem, NULL);
	//初始化菜单的位置为原点位置，这个我也需要找个时间理解下  
	menu->setPosition(Point::ZERO);
	//把菜单添加到层中  
	this->addChild(menu, 1);
	*/
	 //添加背景图
	auto bg = Sprite::create("resources/menu_background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, LAYER_0);

	//添加开始游戏图(onPushSceneGame)
	auto gameStart = MenuItemImage::create("resources/button_start_up.png", "resources/button_start_down.png", CC_CALLBACK_1(MainScene::onPushSceneGame, this));
	gameStart->setPosition(Point(200 ,80));
	
	//添加游戏说明图(onPushSceneHelp)
	auto help= MenuItemImage::create("resources/button_help_up.png", "resources/button_help_down.png", CC_CALLBACK_1(MainScene::onPushSceneHelp, this));
	help->setPosition(Point(200, -30));
	
	//添加制作人员图(onPushSceneAbout)
	auto about= MenuItemImage::create("resources/button_about_up.png", "resources/button_about_down.png", CC_CALLBACK_1(MainScene::onPushSceneAbout, this));
	about->setPosition(Point(200, -140));

	//添加按钮
	auto menu_oper = Menu::create(gameStart,help,about, NULL);
	this->addChild(menu_oper, LAYER_1);

	return true;
}

//进入游戏的方法
void MainScene::onPushSceneGame(Ref* pSender) {
	/*
	auto scene = Scene::create();
	scene->addChild(SceneTestLayer::create());
	Director::getInstance()->replaceScene(TransitionFlipX::create(.5, scene));
	*/
}

//进入帮助的方法
void MainScene::onPushSceneHelp(Ref* pSender) {
	
	auto scene = Scene::create();
	scene->addChild(HelpScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//方法为渐变
	
}

//进入关于的方法
void MainScene::onPushSceneAbout(Ref* pSender) {
	auto scene = Scene::create();
	scene->addChild(AboutScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//方法为渐变
}

/**
 * 关闭视窗的方法
 * 下面是官方定义好的一个宏，意思就是，当平台为wp8或者winRT会弹出框
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