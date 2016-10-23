//
//  PuzzleBoardControllLayer.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "PuzzleBoardControllLayer.h"

USING_NS_CC;

#define WIDTH_PANELS (6)
#define HEIGHT_PANELS (5)

#define PANEL_SIZE (cocos2d::Size(92,92))
#define PANEL_MARGEN (cocos2d::Vec2(2.0f,2.0f))

namespace BoardState {
    /**
     * ステートの開始処理
     */
    void StateBegin::begin()
    {
        m_PuzzleBoard->onStateSelect();
    }
    //------------------------------------------------------
    void StateWait::begin()
    {
        m_waitTime = 0.0f;
    }
    /**
     * ステートの更新処理
     */
    void StateWait::update(float delta)
    {
        m_waitTime += delta;
        if(m_waitTime > 1.0f)
        {
            m_PuzzleBoard->onStateSelect();
        }
    }
    
    //------------------------------------------------------
    //パネルの生成
    //パネルの消去
    void StateErase::begin()
    {
        for(auto rows : m_PuzzleBoard->getPuzzleTable())
        {
            for(auto panel : rows)
            {
                if(panel->isSelect())
                {
                    panel->unselect();
                    panel->eraseAction();
                }
            }
        }
    }
    /**
     * ステートの更新処理
     */
    void StateErase::update(float delta)
    {
        bool nonAction = true;
        for(auto rows : m_PuzzleBoard->getPuzzleTable())
        {
            for(auto panel : rows)
            {
                if(panel->isAction())
                {
                    //誰かはアニメーション中
                    nonAction = false;
                    break;
                }
            }
            if(!nonAction)
            {
                break;
            }
        }
        if(nonAction)
        {
            //コンボにする
            //m_PuzzleBoard->onStateCombo();
            m_PuzzleBoard->onStateGenerate();
        }
    }
    
    //------------------------------------------------------
    //パネルの生成
    /**
     * ステートの開始処理
     */
    void StateGenerate::begin()
    {
        for(auto rows : m_PuzzleBoard->getPuzzleTable())
        {
            for(auto panel : rows)
            {
                if(panel->isErase())
                {
                    panel->setColorType((SquarePieceLayer::pieceType)(rand()%SquarePieceLayer::pieceType::PT_MAX));
                    panel->generateAction();
                }
            }
        }
    }
    /**
     * ステートの更新処理
     */
    void StateGenerate::update(float delta)
    {
        bool nonAction = true;
        for(auto rows : m_PuzzleBoard->getPuzzleTable())
        {
            for(auto panel : rows)
            {
                if(panel->isAction())
                {
                    //誰かはアニメーション中
                    nonAction = false;
                    break;
                }
            }
            if(!nonAction)
            {
                break;
            }
        }
        if(nonAction)
        {
            //コンボにする
            //m_PuzzleBoard->onStateCombo();
            m_PuzzleBoard->onStateWait();
        }
    }
    
    //------------------------------------------------------
    //パネルのコンボ
    /**
     * ステートの開始処理
     */
    void StateCombo::begin()
    {
        
    }
}
//計算テーブル
int PuzzleBoardControllLayer::m_energieRateTable[] = {1,2,4,10};

PuzzleBoardControllLayer::PuzzleBoardControllLayer()
:m_firstSelect(nullptr)
,m_lastSelect(nullptr)
{
    
    m_puzleTable.reserve(WIDTH_PANELS);
    for(int widthIndex = 0; widthIndex < WIDTH_PANELS ; widthIndex++)
    {
        m_puzleTable.push_back(std::vector<SquarePieceLayer*>());
        for(int heightIndex = 0; heightIndex < HEIGHT_PANELS ; heightIndex++)
        {
            m_puzleTable[widthIndex].reserve(HEIGHT_PANELS);
            m_puzleTable[widthIndex].push_back(nullptr);
        }
    }
    
    //ステートの追加
    m_StateController.addState(new BoardState::StateBegin(this));
    m_StateController.addState(new BoardState::StateWait(this));
    m_StateController.addState(new BoardState::StateSelect(this));
    m_StateController.addState(new BoardState::StateErase(this));
    m_StateController.addState(new BoardState::StateCombo(this));
    m_StateController.addState(new BoardState::StateGenerate(this));
}
PuzzleBoardControllLayer::~PuzzleBoardControllLayer()
{
    
}
bool PuzzleBoardControllLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    this->setContentSize(Size(this->getContentSize().width,320.0f));
    
    this->m_Listener = EventListenerTouchOneByOne::create();
    this->m_Listener->setSwallowTouches(true);
    this->m_Listener->onTouchBegan = CC_CALLBACK_2(PuzzleBoardControllLayer::onTouchBegan, this);
    this->m_Listener->onTouchMoved = CC_CALLBACK_2(PuzzleBoardControllLayer::onTouchMoved, this);
    this->m_Listener->onTouchEnded = CC_CALLBACK_2(PuzzleBoardControllLayer::onTouchEnded, this);
    this->m_Listener->onTouchCancelled = CC_CALLBACK_2(PuzzleBoardControllLayer::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->m_Listener, this);


    //横のパネル数
    Vec2 posOffset= Vec2(PANEL_SIZE) + PANEL_MARGEN;
    Vec2 pos = Vec2((Director::getInstance()->getWinSize().width - (posOffset.x * WIDTH_PANELS))*0.5f,0) + posOffset * 0.5f;
    
    m_PuzzleTableRect.setRect(pos.x - PANEL_SIZE.width * 0.5f, pos.y - PANEL_SIZE.width * 0.5f,
                              PANEL_SIZE.width * WIDTH_PANELS, PANEL_SIZE.height * HEIGHT_PANELS);
    
    for(int x = 0;x < WIDTH_PANELS;x++)
    {
        for(int y = 0;y < HEIGHT_PANELS;y++)
        {
            auto layer = SquarePieceLayer::create();
            layer->setColorType((SquarePieceLayer::pieceType)(rand()%SquarePieceLayer::pieceType::PT_MAX));
            layer->setPieceSize(PANEL_SIZE);
            layer->setPosition(pos);
            layer->setIndexColumn(x);
            layer->setIndexRow(y);
            this->addChild(layer);

            //管理の追加
            this->m_puzleTable[x][y] = layer;
            
            pos.y += posOffset.y;
        }
        pos.x += posOffset.x;
        pos.y -= posOffset.y * HEIGHT_PANELS;
    }
    
    
    return true;
}
/**
 * @breif 行動中か
 * @return true = 行動中
 */
bool PuzzleBoardControllLayer::isRunBoardAction()
{
    return m_StateController.getCurrentStateId() != BoardState::BSI_WAIT;
}
/**
 * @brief ステートの更新管理
 *
 */
void PuzzleBoardControllLayer::updateStateObserver(float deltatime)
{
    auto state = m_StateController.getCurrentState();
    if(state)
    {
        state->checkChengeState();
    }
}
/**
 * @breif ステートに合わせた行動
 */
void PuzzleBoardControllLayer::updateStateAction(float deltatime)
{
    //ステートの更新処理
    m_StateController.updateState(deltatime);
}

//-----------------------------------------------------------------
//ステート変更系
//-----------------------------------------------------------------
/**
 * 選択ステートに移行する
 */
void PuzzleBoardControllLayer::onStateSelect()
{
    m_StateController.chengeState(BoardState::BSI_SELECT);
}
/**
 * 選択ステートに移行する
 */
void PuzzleBoardControllLayer::onStateWait()
{
    m_StateController.chengeState(BoardState::BSI_WAIT);
}
/**
 * 生成ステートに移行する
 */
void PuzzleBoardControllLayer::onStateGenerate()
{
    m_StateController.chengeState(BoardState::BSI_GENERATE);
}
/**
 * コンボステートに移行する
 */
void PuzzleBoardControllLayer::onStateCombo()
{
    m_StateController.chengeState(BoardState::BSI_COMBO);
}


//-----------------------------------------------------------------
//タップ系
//-----------------------------------------------------------------
bool PuzzleBoardControllLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(this->m_StateController.getCurrentStateId() != BoardState::BSI_SELECT)
    {
        return false;
    }
    
    //選択
    for(auto row : m_puzleTable)
    {
        for(auto colum :row )
        {
            //パズル毎に判定する
            if(colum->getBoundingBox().containsPoint(touch->getLocation()))
            {
                if(!colum->isSelect())
                {
                    //初回選択
                    m_firstSelect = colum;
                    colum->select();
                    this->m_selectlist.pushBack(colum);
                }
            }
        }
    }
    
    return true;
}

void PuzzleBoardControllLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    //最後の選択
    if(nullptr == m_firstSelect)return;
    
    int rowIndex =m_firstSelect->getIndexRow();
    int columnIndex =m_firstSelect->getIndexColumn();
    
    //列で検索
    for(auto panel : m_puzleTable[columnIndex])
    {
        if(panel->getBoundingBox().containsPoint(touch->getLocation()))
        {
            m_lastSelect = panel;
            //すでに選択されている物で、最後に選んだ物じゃない場合キャンセル
            auto it = m_puzleTable[columnIndex].begin();
            while(it != m_puzleTable[columnIndex].end())
            {
                if(
                   (
                    (*it)->getIndexRow() < m_firstSelect->getIndexRow() &&
                    (*it)->getIndexRow() < m_lastSelect->getIndexRow()
                    )
                   ||
                   (
                   (*it)->getIndexRow() > m_firstSelect->getIndexRow() &&
                   (*it)->getIndexRow() > panel->getIndexRow()
                    )
                   )
                {
                    (*it)->unselect();
                    m_selectlist.eraseObject(*it);
                }
                else
                {
                    if(!(*it)->isSelect())
                    {
                        (*it)->select();
                        this->m_selectlist.pushBack(panel);
                    }
                }
                it++;
            }
        }
    }
    //行で検索
    for(auto rows : m_puzleTable)
    {
        auto panel = rows[rowIndex];
        if(panel->getBoundingBox().containsPoint(touch->getLocation()))
        {
            m_lastSelect = panel;
            //すでに選択されている物で、最後に選んだ物じゃない場合キャンセル
            auto it = m_puzleTable.begin();
            while(it != m_puzleTable.end())
            {
                if(
                   (
                    (*it)[rowIndex]->getIndexColumn() < m_firstSelect->getIndexColumn() &&
                    (*it)[rowIndex]->getIndexColumn() < panel->getIndexColumn()
                    )
                   ||
                   (
                    (*it)[rowIndex]->getIndexColumn() > m_firstSelect->getIndexColumn() &&
                    (*it)[rowIndex]->getIndexColumn() > panel->getIndexColumn()
                    )
                   )
                {
                    (*it)[rowIndex]->unselect();
                    m_selectlist.eraseObject((*it)[rowIndex]);
                }
                else
                {
                    if(!(*it)[rowIndex]->isSelect())
                    {
                        (*it)[rowIndex]->select();
                        this->m_selectlist.pushBack(panel);
                    }
                }
                it++;
            }
        }
    }
    
}

void PuzzleBoardControllLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(m_PuzzleTableRect.containsPoint(touch->getLocation())
       && (m_firstSelect && m_firstSelect->getColorType() == m_lastSelect->getColorType())
       )
    {
        //選択
        m_StateController.chengeState(BoardState::BSI_ERASE);
    }
    else
    {
        CCLOG("はみ出たか、色が違うためキャンセル");
        //キャンセル
        onTouchCancelled(touch,unused_event);
    }

    m_selectlist.clear();
}

void PuzzleBoardControllLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
    for(auto panel : m_selectlist)
    {
        if(panel->isSelect())
        {
            panel->unselect();
        }
    }
    m_selectlist.clear();
    
    m_firstSelect = nullptr;
}
