//
//  SquarePanelLayer.cpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#include "puzzle/SquarePanelLayer.h"

USING_NS_CC;

SquarePanelLayer::SquarePanelLayer()
:m_backColor(nullptr)
,m_select(false)
,m_selectColor(nullptr)
,m_erase(false)
,m_actionFlg(false)
,m_type(PT_RED)
,m_IndexRow(0)
,m_IndexColumn(0)
{
    
}
SquarePanelLayer::~SquarePanelLayer()
{
    
}

bool SquarePanelLayer::init()
{
    if(!Layer::init())return false;

    m_backColor = LayerColor::create(Color4B::WHITE, 80, 80);
    m_backColor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_backColor->setIgnoreAnchorPointForPosition(false);

    m_icon = Sprite::create();
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setIgnoreAnchorPointForPosition(false);

    this->addChild(m_backColor,1);
    this->addChild(m_icon,2);
    
    return true;
}

SquarePanelLayer::pieceType SquarePanelLayer::getColorType()
{
    return m_type;
}
void SquarePanelLayer::setColorType(pieceType type)
{
    switch(type)
    {
        case PT_RED:
            setMainColor(Color3B(0xFF,0x6F,0x6F));
            m_icon->initWithFile("panel/red.png");
            break;
        case PT_GREEN:
            setMainColor(Color3B(0x6F,0xFF,0x6F));
            m_icon->initWithFile("panel/green.png");
            break;
        case PT_BULE:
            setMainColor(Color3B(0x6F,0x6F,0xFF));
            m_icon->initWithFile("panel/blue.png");
            break;
        case PT_HEART:
            setMainColor(Color3B(0x3F,0x3F,0x3F));
            m_icon->initWithFile("panel/Mana-50.png");
            break;
        default:
            m_icon->initWithFile("panel/Mana-50.png");
            setMainColor(Color3B::GRAY);
            break;
    }
    m_type = type;
}


void SquarePanelLayer::setMainColor(cocos2d::Color3B color)
{
    m_backColor->setColor(color);
}
void SquarePanelLayer::setPieceSize(cocos2d::Size size)
{
    m_backColor->setContentSize(size);
    this->setContentSize(size);
    m_backColor->setPosition(size * 0.5f);
    m_icon->setPosition(size * 0.5f);
}

bool SquarePanelLayer::isSelect()
{
    return m_select;
}
bool SquarePanelLayer::isErase()
{
    return m_erase;
}

//
void SquarePanelLayer::select()
{
    m_select = true;
    
    if(m_selectColor)m_selectColor->removeFromParent();
    m_selectColor = LayerColor::create(Color4B(0x00,0xFF,0xFF,0x7F));
    m_selectColor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_selectColor->setIgnoreAnchorPointForPosition(false);
    m_selectColor->setContentSize(m_backColor->getContentSize()+Size(6,6));
    m_selectColor->setPosition(m_selectColor->getContentSize() * 0.5f);
    this->addChild(m_selectColor,0);
    
    float scale = (m_backColor->getContentSize().width - 4) / m_backColor->getContentSize().width;
    this->m_backColor->setScale(scale);
    
    this->setLocalZOrder(10);
 
}
//
void SquarePanelLayer::unselect()
{
    m_select = false;
    
    if(m_selectColor)m_selectColor->removeFromParent();
    m_selectColor = nullptr;
    
    this->m_backColor->setScale(1.0f);
    this->setLocalZOrder(0);
}
//何かの実行中か
bool SquarePanelLayer::isAction()
{
    return m_actionFlg;
}


//
void SquarePanelLayer::eraseAction()
{
    cocos2d::Vector<FiniteTimeAction*> seq,seq2,seq3;
    
    seq.pushBack(EaseOut::create(RotateBy::create(1.0f, 360*10),0.5f));
    seq.pushBack(CallFunc::create([=](){
        m_erase = true;
        m_actionFlg = false;
                                  }));
    seq2.pushBack(EaseOut::create(FadeTo::create(1.0f, 0),0.5f));
    seq3.pushBack(EaseOut::create(ScaleTo::create(1.0f, 0),0.5f));
    
    this->m_backColor->runAction(Spawn::create(
                            Sequence::create(seq),
                            Sequence::create(seq2),
                            Sequence::create(seq3),
                            NULL));
    
    m_actionFlg = true;
}
//
void SquarePanelLayer::generateAction()
{
    m_erase = false;
    cocos2d::Vector<FiniteTimeAction*> seq,seq2;
    
    seq.pushBack(EaseOut::create(FadeTo::create(0.25f, 255),0.5f));
    seq2.pushBack(EaseOut::create(ScaleTo::create(0.25f, 1.0f),0.5f));
    seq.pushBack(CallFunc::create([=](){
        m_actionFlg = false;
    }));
    
    this->m_backColor->runAction(Spawn::create(
                            Sequence::create(seq),
                            Sequence::create(seq2),
                            NULL));
    m_actionFlg = true;
}

