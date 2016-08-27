//
//  PuzzleControllLayer.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#ifndef __care_of_road__PuzzleControllLayer__
#define __care_of_road__PuzzleControllLayer__

#include "cocos2d.h"
#include "SquarePieceLayer.h"



/**
 * パズルを操作するレイヤー
 */
class PuzzleControllLayer : public cocos2d::Layer
{
public:
protected:
    cocos2d::EventListenerTouchOneByOne * m_Listener;
    
    cocos2d::Vector<SquarePieceLayer*> m_puzlelist;
    cocos2d::Vector<SquarePieceLayer*> m_selectlist;
    
public:
    CREATE_FUNC(PuzzleControllLayer);
    virtual bool init();
    PuzzleControllLayer();
    virtual ~PuzzleControllLayer();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

#endif /* defined(__care_of_road__PuzzleControllLayer__) */
