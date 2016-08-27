//
//  BattleScreenLayer.cpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#include "BattleScreenLayer.h"

USING_NS_CC;

BattleScreenLayer::BattleScreenLayer()
{
    
}
BattleScreenLayer::~BattleScreenLayer()
{
    
}

bool BattleScreenLayer::init()
{
    if(!Layer::init())return false;
    
    Size winSize = Director::getInstance()->getWinSize();
    winSize.height *=0.5f;
    
    m_Back = LayerGradient::create(Color4B::GREEN, Color4B::BLUE, Vec2(0,1));
    this->addChild(m_Back);
    
    m_Back->setContentSize(winSize);
    m_Back->setPosition(Vec2::ZERO);
    
    return true;
}
