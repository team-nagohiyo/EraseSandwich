//
//  GaugeController.cpp
//  BULL
//
//  Created by oohara yukio on 2017/06/21.
//
//

#include "GaugeController.h"

USING_NS_CC;

//コンストラクタ
GaugeController::GaugeController()
:m_type(GAUGE_TYPE_NONE)
,m_defaultScale(0)
{
}

//デストラクタ
GaugeController::~GaugeController()
{
}

//コントロール対象の設定
void GaugeController::setControlNode(cocos2d::Node* ref)
{
    if(nullptr == ref)
    {
        CCLOG("ゲージのコントロール対象がない");
        return;
    }
    
    m_target = ref;
    
    m_Size = ref->getContentSize();
    m_defaultPos = ref->getPosition();
    m_defaultAnchorPos = ref->getAnchorPoint();
    m_defaultScale = ref->getScale();
    
    //設定に合わせて初期設定する
    setupType(m_type);
}

//ゲージのタイプ設定
void GaugeController::setupType(GAUGE_TYPE type)
{
    m_target->setPosition(m_defaultPos);
    m_target->setAnchorPoint(m_defaultAnchorPos);
    m_target->setScale(m_defaultScale);
    m_offset = Vec2::ZERO;
    
    switch(type)
    {
    case GAUGE_TYPE_NONE:
        break;
    case GAUGE_TYPE_VERTICAL_TOP_ZERO:
    {
        m_target->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
        break;
    }
    case GAUGE_TYPE_VERTICAL_BOTTOM_ZERO:
    {
        m_target->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
        break;
    }
    case GAUGE_TYPE_HORIZONTAL_LEFT_ZERO:
    {
        m_target->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        break;
    }
    case GAUGE_TYPE_HORIZONTAL_RIGHT_ZERO:
    {
        m_target->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
        break;
    }
    }

    Vec2 anc = m_target->getAnchorPoint() - m_defaultAnchorPos;
    m_offset = Vec2(m_Size.width * anc.x,m_Size.height * anc.y);
    m_target->setPosition(m_defaultPos + m_offset);
    
    //レート情報を変換タイプを元に再設定
    updateBarRate();
}

//レートの設定
void GaugeController::updateBarRate()
{
    if(nullptr == m_target)
    {
        return;
    }
    
    switch (m_type)
    {
    default:
    case GAUGE_TYPE_VERTICAL_TOP_ZERO:
    case GAUGE_TYPE_VERTICAL_BOTTOM_ZERO:
    m_target->setScaleY(m_value*m_defaultScale);
    break;
    case GAUGE_TYPE_HORIZONTAL_RIGHT_ZERO:
    case GAUGE_TYPE_HORIZONTAL_LEFT_ZERO:
    m_target->setScaleX(m_value*m_defaultScale);
    break;
    }
}

//レートの設定
void GaugeController::setRate(float value)
{
    m_value = clampf(value, 0.0f, 1.0f);
    updateBarRate();
}

//タイプ
void GaugeController::setType(GAUGE_TYPE type)
{
    m_type = type;
    setupType(type);
}
