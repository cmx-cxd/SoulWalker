#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include "Config.h"

class Hero : public Sprite
{
public:
	Hero();
	~Hero();

	static Hero* create(Vec2 position);


	virtual bool init(Vec2 position);

	// set and get
	Armature* getArmature() { return m_armature; }

	State state;
private:
	Armature* m_armature;
	
};

#endif