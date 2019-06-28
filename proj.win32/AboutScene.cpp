#include "AboutScene.h"  
#include "MainScene.h"  
#include "Config.h"
USING_NS_CC;
//蜜汁构造函数
AboutScene::AboutScene() {}
bool AboutScene::init()
{
	if (Layer::init())
	{
		//获取坐标系界面的屏幕可见区域  
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//原点位置  
		Point origin = Director::getInstance()->getVisibleOrigin();
		//关于图
		auto pic = Sprite::create("resources/about_scene.png");
		pic->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(pic, LAYER_0);
		//返回按钮图
		auto back = MenuItemImage::create("resources/button_back_up.png", "resources/button_back_down.png", CC_CALLBACK_1(AboutScene::backToMainScene, this));
		back->setPosition(Point(300, -225));
		//添加按钮
		auto menu_oper = Menu::create(back, NULL);
		this->addChild(menu_oper, LAYER_1);
		return true;
	}
	return false;
}

void AboutScene::backToMainScene(Ref* sender) {
	auto scene = Scene::create();
	scene->addChild(MainScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//方法为渐变
}