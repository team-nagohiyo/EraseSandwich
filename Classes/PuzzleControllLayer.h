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
#include "puzzle/SquarePieceLayer.h"

enum PuzzleState
{
    PUZZLE_STATE_BEGIN =0,
    PUZZLE_STATE_WAIT,
    PUZZLE_STATE_ERASE,
    PUZZLE_STATE_CHANGE,
    PUZZLE_STATE_LOCK,
};

/**
 * パズルを操作するレイヤー
 */
class PuzzleControllLayer : public cocos2d::Layer
{
public:
protected:
    cocos2d::EventListenerTouchOneByOne * m_Listener;

    SquarePieceLayer* m_firstSelect;//最初にたっぷしたパネル
    SquarePieceLayer* m_lastSelect;//最後にたっぷしたパネル
    cocos2d::Vector<SquarePieceLayer*> m_selectlist;
    std::vector<std::vector<SquarePieceLayer*>> m_puzleTable;//列・行にする
    
    cocos2d::Rect m_PuzzleTableRect;

public:
    CREATE_FUNC(PuzzleControllLayer);
    virtual bool init();
    PuzzleControllLayer();
    virtual ~PuzzleControllLayer();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
};

#endif /* defined(__care_of_road__PuzzleControllLayer__) */
