#include "Hero.h"

Hero::Hero()
{

}

Hero::~Hero()
{

}

Hero* Hero::create(Vec2 position)
{
	Hero *pRet = new(std::nothrow) Hero();
	if (pRet && pRet->init(position))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Hero::init(Vec2 position)
{
	if (!Sprite::init())
	{
		return false;
	}

	ArmatureDataManager::getInstance()->addArmatureFileInfo("resources/animation/Hero.ExportJson");
	m_armature = Armature::create("Hero");
	if (m_armature == NULL)
	{
		CCLOG("hero load error!");
		return false;
	}
	m_armature->setPosition(Vec2::ZERO);
	m_armature->getAnimation()->play("stand");//三个动作为stand,walk,air
	this->addChild(m_armature);
	this->setPosition(position);


	return true;
}
