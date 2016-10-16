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
#include "Manager/StateController.h"


class PuzzleBoardControllLayer;

namespace BoardState {
    class PuzzleBoardState : public StateBase
    {
    protected:
        PuzzleBoardControllLayer * m_PuzzleBoard;
    public:
        
        PuzzleBoardState(PuzzleBoardControllLayer * puzzleBoard)
        {
            m_PuzzleBoard = puzzleBoard;
        }
        
        /**
         * ステートの開始処理
         */
        virtual void begin(){};
        /**
         * ステートの更新処理
         */
        virtual void update(float delta){};
        
        /**
         * ステートの変更条件を見したしているか
         */
        virtual void checkChengeState(){}
        /**
         * ステートの終了処理
         */
        virtual void end(){};
    };
    
    enum BOARD_STATE_ID : int
    {
        BSI_BEGIN = 0,
        BSI_WAIT,
        BSI_SELECT,
        BSI_ERASE,
        BSI_GENERATE,
        BSI_COMBO,
    };
    
    /**
     * ステート開始
     */
    class StateBegin : public PuzzleBoardState
    {
    public:
        StateBegin(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};

        virtual int getStateID() override { return BOARD_STATE_ID::BSI_BEGIN; }
        /**
         * ステートの開始処理
         */
        virtual void begin() override;
    };
    //パネルの許可待ち
    class StateWait : public PuzzleBoardState
    {
    private:
        float m_waitTime;
    public:
        StateWait(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};
        
        virtual int getStateID() override { return BOARD_STATE_ID::BSI_WAIT; }
        
        /**
         * ステートの開始処理
         */
        virtual void begin() override;
        /**
         * ステートの更新処理
         */
        virtual void update(float delta) override;
    };
    //パネルの選択
    class StateSelect : public PuzzleBoardState
    {
    public:
        StateSelect(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};
        virtual int getStateID() override { return BOARD_STATE_ID::BSI_SELECT; }
    };
    //パネルの消去
    class StateErase : public PuzzleBoardState
    {
    public:
        StateErase(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};
        
        virtual int getStateID() override { return BOARD_STATE_ID::BSI_ERASE; }
        /**
         * ステートの開始処理
         */
        virtual void begin() override;
        /**
         * ステートの更新処理
         */
        virtual void update(float delta) override;
    };
    //パネルの生成
    class StateGenerate : public PuzzleBoardState
    {
    public:
        StateGenerate(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};
        
        virtual int getStateID() override { return BOARD_STATE_ID::BSI_GENERATE; }
        /**
         * ステートの開始処理
         */
        virtual void begin() override;
        /**
         * ステートの更新処理
         */
        virtual void update(float delta) override;
    };
    
    //パネルのコンボ
    class StateCombo : public PuzzleBoardState
    {
    public:
        StateCombo(PuzzleBoardControllLayer*puzzleBoard)
        :PuzzleBoardState(puzzleBoard){};
        
        virtual int getStateID() override { return BOARD_STATE_ID::BSI_COMBO; }
        /**
         * ステートの開始処理
         */
        virtual void begin() override;
    };
    
}


/**
 * パズルを操作するレイヤー
 */
class PuzzleBoardControllLayer
: public cocos2d::Layer
{
public:
protected:
    cocos2d::EventListenerTouchOneByOne * m_Listener;

    SquarePieceLayer* m_firstSelect;//最初にたっぷしたパネル
    SquarePieceLayer* m_lastSelect;//最後にたっぷしたパネル
    cocos2d::Vector<SquarePieceLayer*> m_selectlist;
    std::vector<std::vector<SquarePieceLayer*>> m_puzleTable;//列・行にする
    
    cocos2d::Rect m_PuzzleTableRect;

    StateController<BoardState::PuzzleBoardState> m_StateController;
public:
    CREATE_FUNC(PuzzleBoardControllLayer);
    virtual bool init();
    PuzzleBoardControllLayer();
    virtual ~PuzzleBoardControllLayer();
    
    BoardState::PuzzleBoardState *getState(){
        return static_cast<BoardState::PuzzleBoardState*>(m_StateController.getCurrentState());
    };
    
    /**
     * @breif 行動中か
     * @return true = 行動中
     */
    bool isRunBoardAction();
    
    /**
     * @brief ステートの更新管理
     *
     */
    void updateStateObserver(float deltatime);
    
    /**
     * @breif ステートに合わせた行動
     */
    void updateStateAction(float deltatime);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    /**
     * 選択ステートに移行する
     */
    void onStateSelect();
    /**
     * 停止ステートに移行する
     */
    void onStateWait();
    /**
     * 生成ステートに移行する
     */
    void onStateGenerate();
    /**
     * コンボステートに移行する
     */
    void onStateCombo();
    
    std::vector<std::vector<SquarePieceLayer*>> & getPuzzleTable()
    {
        return m_puzleTable;
    }
    
};

#endif /* defined(__care_of_road__PuzzleControllLayer__) */
