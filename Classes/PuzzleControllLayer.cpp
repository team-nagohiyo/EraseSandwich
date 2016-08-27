//
//  PuzzleControllLayer.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "PuzzleControllLayer.h"

USING_NS_CC;

#define WIDTH_PANELS (6)
#define HEIGHT_PANELS (5)

#define PANEL_SIZE (cocos2d::Size(92,92))
#define PANEL_MARGEN (cocos2d::Vec2(2.0f,2.0f))

PuzzleControllLayer::PuzzleControllLayer()
{
    
}
PuzzleControllLayer::~PuzzleControllLayer()
{
    
}
bool PuzzleControllLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    this->setContentSize(Size(this->getContentSize().width,320.0f));
    
    this->m_Listener = EventListenerTouchOneByOne::create();
    this->m_Listener->setSwallowTouches(true);
    this->m_Listener->onTouchBegan = CC_CALLBACK_2(PuzzleControllLayer::onTouchBegan, this);
    this->m_Listener->onTouchMoved = CC_CALLBACK_2(PuzzleControllLayer::onTouchMoved, this);
    this->m_Listener->onTouchEnded = CC_CALLBACK_2(PuzzleControllLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->m_Listener, this);


    //横のパネル数
    Vec2 posOffset= Vec2(PANEL_SIZE) + PANEL_MARGEN;
    Vec2 pos = Vec2((Director::getInstance()->getWinSize().width - (posOffset.x * WIDTH_PANELS))*0.5f,0) + posOffset * 0.5f;
    for(int x = 0;x < WIDTH_PANELS;x++)
    {
        for(int y = 0;y < HEIGHT_PANELS;y++)
        {
            auto layer = SquarePieceLayer::create();
            layer->setType((SquarePieceLayer::pieceType)(rand()%SquarePieceLayer::pieceType::PT_MAX));
            layer->setPieceSize(PANEL_SIZE);
            layer->setPosition(pos);
            this->m_puzlelist.pushBack(layer);
            this->addChild(layer);
            
            pos.y += posOffset.y;
        }
        pos.x += posOffset.x;
        pos.y -= posOffset.y * HEIGHT_PANELS;
    }
    
    return true;
}

bool PuzzleControllLayer::onTouchBegan(Touch *touch, Event *unused_event)
{    
    //選択
    for(auto panel : m_puzlelist)
    {
        if(panel->getBoundingBox().containsPoint(touch->getLocation()))
        {
            if(!panel->isSelect())
            {
                panel->select();
                this->m_selectlist.pushBack(panel);
            }
        }
    }
    
    return true;
}

void PuzzleControllLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    //選択
    for(auto panel : m_puzlelist)
    {
        if(panel->getBoundingBox().containsPoint(touch->getLocation()))
        {
            //すでに選択されている物で、最後に選んだ物じゃない場合キャンセル
            for(auto select:m_selectlist)
            {
                
            }
            if(!panel->isSelect())
            {
                panel->select();
            }
        }
    }
    
}

void PuzzleControllLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    //選択
    for(auto panel : m_puzlelist)
    {
        if(panel->isSelect())
        {
            panel->unselect();
            panel->eraseAction();
        }
    }

    m_selectlist.clear();
}