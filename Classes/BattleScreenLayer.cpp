//
//  BattleScreenLayer.cpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#include "BattleScreenLayer.h"

USING_NS_CC;

#define DEBUG_GAUGE_TIME (20)

BattleScreenLayer::BattleScreenLayer()
:m_debugGaugeValue(0.0f)
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
    
    m_background = Sprite::create("game/forest_back.png");
    this->addChild(m_background);
    m_background->setScale(winSize.height / m_background->getContentSize().height);
    
    m_background->setPosition(winSize * 0.5f);
    
    //デバック用ゲージシステム
    m_debugUnit = Sprite::create("game/girls.png");
    this->addChild(m_debugUnit);
    m_debugUnit->setPosition(Vec2(150,100));

    //デバック用ゲージシステム
    m_debugGauge = Sprite::create("game/gauge.png");
    this->addChild(m_debugGauge);
    m_debugGauge->setPosition(Vec2(150,100));
    m_gauge.setControlNode(m_debugGauge);
    m_gauge.setType(GaugeController::GAUGE_TYPE_HORIZONTAL_LEFT_ZERO);
    m_debugGaugeValue = 0.0f;
    m_gauge.setRate(0.0f);
    
    return true;
}

//画面の情報更新
void BattleScreenLayer::update(float delta)
{
    m_debugGaugeTime += delta;
    m_debugGaugeValue = (1.0f / DEBUG_GAUGE_TIME) * m_debugGaugeTime;
    m_gauge.setRate(m_debugGaugeValue);
}

