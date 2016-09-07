//
//  SquarePieceLayer.cpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#include "SquarePieceLayer.h"

USING_NS_CC;

SquarePieceLayer::SquarePieceLayer()
:m_backColor(nullptr)
,m_select(false)
,m_selectColor(nullptr)
,m_type(PT_RED)
,m_IndexRow(0)
,m_IndexColumn(0)
{
    
}
SquarePieceLayer::~SquarePieceLayer()
{
    
}

bool SquarePieceLayer::init()
{
    if(!Layer::init())return false;

    m_backColor = LayerColor::create(Color4B::WHITE, 64, 64);
    m_backColor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_backColor->ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ignoreAnchorPointForPosition(false);
    this->addChild(m_backColor,1);
    
    return true;
}

SquarePieceLayer::pieceType SquarePieceLayer::getColorType()
{
    return m_type;
}
void SquarePieceLayer::setColorType(pieceType type)
{
    switch(type)
    {
        case PT_RED:
            setMainColor(Color3B::RED);
            break;
        case PT_GREEN:
            setMainColor(Color3B::GREEN);
            break;
        case PT_BULE:
            setMainColor(Color3B::BLUE);
            break;
        case PT_YELLOW:
            setMainColor(Color3B::YELLOW);
            break;
        case PT_PURPLE:
            setMainColor(Color3B(0xFF,0x00,0xFF));
            break;
        default:
            setMainColor(Color3B::GRAY);
            break;
    }
    m_type = type;
}


void SquarePieceLayer::setMainColor(cocos2d::Color3B color)
{
    m_backColor->setColor(color);
}
void SquarePieceLayer::setPieceSize(cocos2d::Size size)
{
    m_backColor->setContentSize(size);
    this->setContentSize(size);
    m_backColor->setPosition(size * 0.5f);
}

bool SquarePieceLayer::isSelect()
{
    return m_select;
}

//
void SquarePieceLayer::select()
{
    m_select = true;
    
    if(m_selectColor)m_selectColor->removeFromParent();
    m_selectColor = LayerColor::create(Color4B(0x00,0xFF,0xFF,0x7F));
    m_selectColor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_selectColor->ignoreAnchorPointForPosition(false);
    m_selectColor->setContentSize(m_backColor->getContentSize()+Size(6,6));
    m_selectColor->setPosition(m_selectColor->getContentSize() * 0.5f);
    this->addChild(m_selectColor,0);
    
    float scale = (m_backColor->getContentSize().width - 4) / m_backColor->getContentSize().width;
    this->m_backColor->setScale(scale);
    
    this->setLocalZOrder(10);
 
}
//
void SquarePieceLayer::unselect()
{
    m_select = false;
    
    if(m_selectColor)m_selectColor->removeFromParent();
    m_selectColor = nullptr;
    
    this->m_backColor->setScale(1.0f);
    this->setLocalZOrder(0);
}


//
void SquarePieceLayer::eraseAction()
{
    cocos2d::Vector<FiniteTimeAction*> seq,seq2,seq3;
    
    seq.pushBack(EaseOut::create(RotateBy::create(1.0f, 360*10),0.5f));
    seq2.pushBack(EaseOut::create(FadeTo::create(1.0f, 0),0.5f));
    seq3.pushBack(EaseOut::create(ScaleTo::create(1.0f, 0),0.5f));
    
    this->m_backColor->runAction(Spawn::create(
                            Sequence::create(seq),
                            Sequence::create(seq2),
                            Sequence::create(seq3),
                            NULL));
}
//
void SquarePieceLayer::generateAction()
{
    cocos2d::Vector<FiniteTimeAction*> seq,seq2;
    
    seq.pushBack(EaseOut::create(FadeTo::create(1.0f, 0),0.5f));
    seq2.pushBack(EaseOut::create(ScaleTo::create(1.0f, 1.0f),0.5f));
    
    this->m_backColor->runAction(Spawn::create(
                            Sequence::create(seq),
                            Sequence::create(seq2),
                            NULL));
}

