#include "AboutScene.h"  
#include "MainScene.h"  
#include "Config.h"
USING_NS_CC;
//��֭���캯��
AboutScene::AboutScene() {}
bool AboutScene::init()
{
	if (Layer::init())
	{
		//��ȡ����ϵ�������Ļ�ɼ�����  
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//ԭ��λ��  
		Point origin = Director::getInstance()->getVisibleOrigin();
		//����ͼ
		auto pic = Sprite::create("resources/about_scene.png");
		pic->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(pic, LAYER_0);
		//���ذ�ťͼ
		auto back = MenuItemImage::create("resources/button_back_up.png", "resources/button_back_down.png", CC_CALLBACK_1(AboutScene::backToMainScene, this));
		back->setPosition(Point(300, -225));
		//��Ӱ�ť
		auto menu_oper = Menu::create(back, NULL);
		this->addChild(menu_oper, LAYER_1);
		return true;
	}
	return false;
}

void AboutScene::backToMainScene(Ref* sender) {
	auto scene = Scene::create();
	scene->addChild(MainScene::create());
	Director::getInstance()->replaceScene(TransitionCrossFade::create(.2, scene));//����Ϊ����
}