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
        m_PuzzleBoard->resetParam();
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
                    
                    //検索距離の加算
                    int addRange = 1;
                    if(panel->getColorType() == m_PuzzleBoard->getLastSelectPanel()->getColorType())
                    {
                        addRange = 2; //同じ色なら２加算
                    }
                    m_PuzzleBoard->setSearchRange(m_PuzzleBoard->getSearchRange() + addRange);
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
                //消去済みパネルのインスタンスを生成ように入れ替える
                if(panel->isErase())
                {
                    if(panel == m_PuzzleBoard->getLastSelectPanel())
                    {
                        switch(panel->getColorType())
                        {
                            case SquarePanelLayer::pieceType::PT_RED:
                                panel->setColorType(SquarePanelLayer::pieceType::PT_GREEN);
                                break;
                            case SquarePanelLayer::pieceType::PT_GREEN:
                                panel->setColorType(SquarePanelLayer::pieceType::PT_BULE);
                                break;
                            case SquarePanelLayer::pieceType::PT_BULE:
                                panel->setColorType(SquarePanelLayer::pieceType::PT_RED);
                                break;
                            default:
                                break;
                        }
                        panel->generateAction();
                    }
                    else
                    {
                        //最後に消されたブロックじゃ無い
                        panel->setColorType((SquarePanelLayer::pieceType)(rand()%SquarePanelLayer::pieceType::PT_HEART));
                        panel->generateAction();
                    }
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
            m_PuzzleBoard->onStateCombo();
        }
    }
    
    //------------------------------------------------------
    //パネルのコンボ
    /**
     * ステートの開始処理
     */
    void StateCombo::begin()
    {
        m_combo = m_PuzzleBoard->checkNextPanel();
    }
    /**
     * ステートの更新処理
     */
    void StateCombo::update(float delta)
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
            if(m_combo)
            {
                //コンボあり
                m_PuzzleBoard->changeState(BoardState::BOARD_STATE_ID::BSI_ERASE);
            }
            else
            {
                m_PuzzleBoard->changeState(BoardState::BOARD_STATE_ID::BSI_WAIT);
            }
        }
    }
}
//計算テーブル
int PuzzleBoardControllLayer::m_energyRateTable[] = {1,2,4,10};

PuzzleBoardControllLayer::PuzzleBoardControllLayer()
:m_firstSelect(nullptr)
,m_lastSelect(nullptr)
{
    
    m_puzleTable.reserve(WIDTH_PANELS);
    for(int widthIndex = 0; widthIndex < WIDTH_PANELS ; widthIndex++)
    {
        m_puzleTable.push_back(std::vector<SquarePanelLayer*>());
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
    m_StateController.addState(new BoardState::StateGenerate(this));
    m_StateController.addState(new BoardState::StateCombo(this));
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
            auto layer = SquarePanelLayer::create();
            layer->setColorType((SquarePanelLayer::pieceType)(rand()%SquarePanelLayer::pieceType::PT_BOM));
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

/**
 * 次のパネルを検索して確保できるか
 */
bool PuzzleBoardControllLayer::checkNextPanel()
{
    if(m_comboCount >= 2)
    {
        return false;
    }
    
    if(m_lastSelect)
    {
        auto panel = searchTableToPanel(m_lastSelect,
                           m_lastSelect->getIndexColumn(),
                           m_lastSelect->getIndexRow(),
                           m_lastSelect->getColorType(),
                           m_searchRange);
        if(panel)
        {
            m_firstSelect = m_lastSelect;
            m_lastSelect = panel;
            //選択を解除
            unselectLine(m_firstSelect, m_lastSelect);
            //選択
            selectLine(m_firstSelect, m_lastSelect);

            m_comboCount++;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
/**
 * 各パラメータをリセットする
 */
void PuzzleBoardControllLayer::resetParam()
{
    m_lastSelect = nullptr;
    m_firstSelect = nullptr;
    m_searchRange = 0;
    m_energyCycleCount = 0;
    m_comboCount = 0;
}

//-----------------------------------------------------------------
//ステート変更系
//-----------------------------------------------------------------
/**
 * 別ステートに移行する
 */
void PuzzleBoardControllLayer::changeState(BoardState::BOARD_STATE_ID stateId)
{
    m_StateController.chengeState(stateId);
}
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

//指定色のパネルを検索してくる
SquarePanelLayer* PuzzleBoardControllLayer::searchTableToPanel(SquarePanelLayer* begin,
                                                               int column,
                                                               int row,
                                                               SquarePanelLayer::pieceType type,
                                                               int &serachRange)
{
    SquarePanelLayer* ret = nullptr;
    int maxRange = 0;
    //列で検索(最初に選択している列の何行めか)
    for(auto panel : m_puzleTable[column])
    {
        int range = abs(panel->getIndexRow() - row);
        if(panel->getColorType() == type && //選択色と同じ色
           begin != panel && //選択中のパネルじゃない
           serachRange >= range &&
           maxRange < range
           )
        {
            maxRange = range;
            ret = panel;
            break;
        }
    }
    //見つからなかった場合に行でも検索する
    if(nullptr == ret)
    {
        //行で検索(最初に選択している行の何列めか)
        for(auto rows : m_puzleTable)
        {
            auto panel = rows[row];
            int range = abs(panel->getIndexColumn() - column);
            if(panel->getColorType() == type &&
               begin != panel && //選択中のパネルじゃない
               serachRange >= range &&
               maxRange < range
               )
            {
                maxRange = range;
                ret = panel;
                break;
            }
        }
    }
    
    //検索されたパネル分消費
    serachRange -= maxRange;
    
    return ret;
}

//指定したポイントのパネルを取得
SquarePanelLayer* PuzzleBoardControllLayer::getPosPanel(int column,int row,cocos2d::Vec2 pos)
{
    SquarePanelLayer* ret = nullptr;
    //列で検索(最初に選択している列の何行めか)
    for(auto panel : m_puzleTable[column])
    {
        if(panel->getBoundingBox().containsPoint(pos))
        {
            //現在のタップポイントで当てはまるピース
            ret = panel;
            break;
        }
    }
    //見つからなかった場合に行でも検索する
    if(nullptr == ret)
    {
        //行で検索(最初に選択している行の何列めか)
        for(auto rows : m_puzleTable)
        {
            auto panel = rows[row];
            if(panel->getBoundingBox().containsPoint(pos))
            {
                //現在のタップポイントで当てはまるピース
                ret = panel;
                break;
            }
        }
    }
    
    return ret;
}
//選択解除処理
void PuzzleBoardControllLayer::unselectLine(SquarePanelLayer* begin, SquarePanelLayer * end)
{
    auto it = m_selectlist.begin();
    while(it != m_selectlist.end())
    {
        if(begin && end)
        {
            int rowNum = (*it)->getIndexRow();
            int columnNum = (*it)->getIndexColumn();
            if(begin->getIndexRow() == end->getIndexRow())
            {
                if((begin->getIndexColumn() > columnNum && end->getIndexColumn() > columnNum) ||
                   (begin->getIndexColumn() < columnNum && end->getIndexColumn() < columnNum) )
                {
                    //開始終了どっちよりも小さい
                    (*it)->unselect();
                    it = m_selectlist.erase(it);
                    continue;
                }
            }
            else if( begin->getIndexColumn() == end->getIndexColumn() )
            {
                //同じ列
                if((begin->getIndexRow() > rowNum && end->getIndexRow() > rowNum) ||
                   (begin->getIndexRow() < rowNum && end->getIndexRow() < rowNum) )
                {
                    //開始終了どっちよりも小さいまたはオーバー
                    (*it)->unselect();
                    it = m_selectlist.erase(it);
                    continue;
                }
            }
            
            //同じ一列にいる場合は、消さない
            if(end->getIndexRow() == (*it)->getIndexRow()
               && begin->getIndexRow() == (*it)->getIndexRow())
            {
                it++;
                continue;
            }
            if(end->getIndexColumn() == (*it)->getIndexColumn()
               && begin->getIndexColumn() == (*it)->getIndexColumn())
            {
                it++;
                continue;
            }
        }
        
        (*it)->unselect();
        it = m_selectlist.erase(it);
    }
}

//選択処理
void PuzzleBoardControllLayer::selectLine(SquarePanelLayer* begin, SquarePanelLayer * end)
{
    if( begin && end )
    {
        int rowIndex = begin->getIndexRow();
        int columnIndex = begin->getIndexColumn();
        
        if(begin->getIndexRow() == end->getIndexRow())
        {
            //同じ行
            for(int num = 0;num < m_puzleTable.size(); num++)
            {
                if(begin->getIndexColumn() > num && end->getIndexColumn() > num)
                {
                    //開始終了どっちよりも小さい
                    continue;
                }
                if(begin->getIndexColumn() < num && end->getIndexColumn() < num)
                {
                    //開始終了どっちもオーバーしてる
                    continue;
                }
                //選択状態じゃないので選択状態にする
                if(!m_puzleTable[num][rowIndex]->isSelect())
                {
                    m_puzleTable[num][rowIndex]->select();
                    this->m_selectlist.pushBack(m_puzleTable[num][rowIndex]);
                }
            }
        }
        else if( begin->getIndexColumn() == end->getIndexColumn() )
        {
            //同じ列
            for(int num = 0; num < m_puzleTable[columnIndex].size() ; num++)
            {
                if(begin->getIndexRow() > num && end->getIndexRow() > num)
                {
                    //開始終了どっちよりも小さい
                    continue;
                }
                if(begin->getIndexRow() < num && end->getIndexRow() < num)
                {
                    //開始終了どっちもオーバーしてる
                    continue;
                }
                //選択状態じゃないので選択状態にする
                if(!m_puzleTable[columnIndex][num]->isSelect())
                {
                    m_puzleTable[columnIndex][num]->select();
                    this->m_selectlist.pushBack(m_puzleTable[columnIndex][num]);
                }
            }
        }
    }
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
    
    //最初に触ったブロックと同じなのでキャンセル
    if(m_firstSelect->getBoundingBox().containsPoint(touch->getLocation()))return;
    
    //---------------------------------
    //検索　指定した行と列以外は検索しない
    //---------------------------------
    m_lastSelect = nullptr;
    m_lastSelect = getPosPanel(columnIndex,rowIndex,touch->getLocation());

    //---------------------------------
    //選択状態をとりあえず解除
    //---------------------------------
    unselectLine(m_firstSelect, m_lastSelect);
    
    //---------------------------------
    //選択処理
    //---------------------------------
    selectLine(m_firstSelect,m_lastSelect);
}

void PuzzleBoardControllLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    //---------------------------------
    //選択状態をとりあえず解除
    //---------------------------------
    unselectLine(m_firstSelect, m_lastSelect);
    
    //---------------------------------
    //選択処理
    //---------------------------------
    selectLine(m_firstSelect,m_lastSelect);
    
    //---------------------------------
    //選択ブロックの色判定
    //---------------------------------
    if(m_PuzzleTableRect.containsPoint(touch->getLocation())
       && (m_firstSelect && m_lastSelect && m_firstSelect->getColorType() == m_lastSelect->getColorType())
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
