//
//  RollBackgroundLayer.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/14.
//
//

#include "RollBackgroundLayer.h"
#include "GameData.h"

USING_NS_CC;


RollBackgroundLayer::RollBackgroundLayer()
:m_Speed(200.0f)
{
    
}
RollBackgroundLayer::~RollBackgroundLayer()
{
    
}

bool RollBackgroundLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    float height = 0;
    float width = 0;
    
    for(int index = 0; index < 3 ;index++)
    {
        auto sprite = Sprite::create("game/back_tile.png");
        this->addChild(sprite);
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2(0,height));
        this->m_ScrollLayers.pushBack(sprite);
        
        width = sprite->getContentSize().width;
        height += sprite->getContentSize().height;
    }
    
    this->setContentSize(Size(width,height));
    
    this->m_ScrollHeight = GameData::getInstance()->getGroundHeightMove();
    this->m_MaxScrollHeight = height / 3.0f;

    //初回更新
    this->updatePosition();

    this->scheduleUpdate();
    
    return true;
}

void RollBackgroundLayer::update(float dt)
{
    this->m_ScrollHeight -= m_Speed * dt;//1秒間に進む
    if(this->m_ScrollHeight < -this->m_MaxScrollHeight)this->m_ScrollHeight += this->m_MaxScrollHeight;
    
    //現在の移動地データを入れる
    GameData::getInstance()->setGroundHeightMove(this->m_ScrollHeight);
    
    this->updatePosition();
}

void RollBackgroundLayer::updatePosition()
{
    float height = 0;
    for(int index = 0; index < 3 ;index++)
    {
        Sprite* work = this->m_ScrollLayers.at(index);
        work->setPositionY(this->m_ScrollHeight + height);
        height += work->getContentSize().height;
    }
}



