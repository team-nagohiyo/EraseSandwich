//
//  GameScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#include "Scene/GameScene.h"
#include "Scene/GameOverScene.h"
#include "Manager/GameData.h"
#include "Manager/GameMediator.h"
#include "Manager/EnemyGenerator.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
GameScene::GameScene()
:m_State(GameState::StartWait)
,m_TapStartSprite(nullptr)
,m_GameOverWaitTime(0)
{
    //仲介クラスに登録する
    GameMediator::getInstance()->setMediateGameScene(this);
}
GameScene::~GameScene()
{
    GameMediator::getInstance()->setMediateGameScene(nullptr);
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //情報の読み込み
    GameData::getInstance()->loadSettingData();
    
    //敵の配置レイヤー
    this->m_EnemyLayer = Layer::create();
    this->m_EnemyLayer->setPosition(Vec2::ZERO);
    this->addChild(this->m_EnemyLayer,10);

    //弾の配置レイヤー
    this->m_BulletLayer = Layer::create();
    this->m_BulletLayer->setPosition(Vec2::ZERO);
    this->addChild(this->m_BulletLayer,20);
    
    this->m_PlayerObject = PlayerObject::create();
    this->m_StartingPos = Vec2(visibleSize.width * 0.5f,200.0f);
    this->m_StartPos = Vec2(visibleSize.width * 0.5f,-128.0f);
    this->m_PlayerObject->setPosition(m_StartPos);
    this->addChild(this->m_PlayerObject,30);
    
    //プレイヤーの基本値の設定
    GameData * game = GameData::getInstance();
    this->m_PlayerObject->setBasePower(game->getBasePower());
    this->m_PlayerObject->setShotCycle(game->getShotCycle());
    this->m_PlayerObject->setChargeMaxPower(game->getChargePower());
    this->m_PlayerObject->setChargeMaxTime(game->getChargeTime());
    this->m_PlayerObject->setLife(GameData::getInstance()->getPlayerHp());
    if(this->m_PlayerObject->getLife() < 1)this->m_PlayerObject->setLife(1);
    
    //メニュー
    auto labelScore = Sprite::create("str/label_score.png");
    labelScore->setPosition(Vec2(origin.x + 10.0f + labelScore->getContentSize().width * 0.5f,
                                 origin.y + visibleSize.height
                                 - 10.0f - labelScore->getContentSize().height * 0.5f));
    this->addChild(labelScore, 50);
    
    this->m_ScoreLabel = Label::createWithBMFont("str/little_number.fnt","");
    this->m_ScoreLabel->setPosition(Vec2(origin.x + labelScore->getContentSize().width + 20.0f,
                            labelScore->getPositionY()));
    this->m_ScoreLabel->setAnchorPoint(Vec2(0.0f,0.5f));
    this->addChild(this->m_ScoreLabel, 60);
    
    //タップスタートのUI
    this->m_TapStartSprite = Sprite::create("str/title_tap_start.png");
    this->m_TapStartSprite->setPosition(this->getContentSize() * 0.5f);
    this->addChild(this->m_TapStartSprite, 1000);
    
    //スコア表示の更新
    this->refreshScoreLabel();
    
    GameData::getInstance()->setGameScore(0);
    
    EnemyGenerator::getInstance()->reset();
    EnemyGenerator::getInstance()->setGeneratePosition(Vec2(this->getContentSize().width * 0.5f,1500.0f));
    EnemyGenerator::getInstance()->setGenerateWidth(this->getContentSize().width);
    
    //更新の開始
    this->scheduleUpdate();
    
    this->m_TouchControl = PuzzleControllLayer::create();
    this->m_TouchControl->setPosition(origin);
    this->addChild(this->m_TouchControl,1);
    
    this->m_TouchRect.setRect(origin.x, origin.y,
                              this->m_TouchControl->getContentSize().width,
                              this->m_TouchControl->getContentSize().height);
    
    m_BattleBack = BattleScreenLayer::create();
    this->addChild(m_BattleBack,1000);
    m_BattleBack->setPosition(Vec2(0,visibleSize.height * 0.5f));
    
    return true;
}
/**
 * 更新
 */
void GameScene::update(float dt)
{
    //ヒットチェック
    this->hitCheck();
    
    //オブジェクト行動
    this->updateAction(dt);
    
    //オブジェクトデリートチェック
    this->removeObjectWithSoul();
    
    //スコア表示の更新
    this->refreshScoreLabel();
}
/**
 * ヒットチェック
 */
void GameScene::hitCheck()
{
    if(this->getState() == GameScene::GameState::GamePlay)
    {
        for(auto target : this->m_EnemyList)
        {
            if(false == target->getEnabled())continue;
            
            for(auto work : this->m_BulletList)
            {
                if(false == work->getEnabled())continue;
                float range = work->getHitLength() + target->getHitLength();
                if((work->getPosition() - target->getPosition()).length() < range)
                {
                    target->entryHitObject(work);
                    work->entryHitObject(target);
                }
            }
            
            if(false == m_PlayerObject->getEnabled())continue;
            float range = this->m_PlayerObject->getHitLength() + target->getHitLength();
            if((this->m_PlayerObject->getPosition() - target->getPosition()).length() < range)
            {
                target->entryHitObject(this->m_PlayerObject);
                this->m_PlayerObject->entryHitObject(target);
            }
        }
    }
}

/**
 * 行動
 */
void GameScene::updateAction(float dt)
{
    switch (this->getState())
    {
        case GameScene::GameState::Starting:            //スタート用の処理
        {
            Vec2 moveVec = ((this->m_StartingPos - this->m_StartPos) / 1.5f) * dt;
            this->m_PlayerObject->setPosition(this->m_PlayerObject->getPosition() + moveVec);
            if(this->m_PlayerObject->getPosition().y > this->m_StartingPos.y)
            {
                this->m_PlayerObject->setPositionY(this->m_StartingPos.y);
                this->setState(GameState::GamePlay);
            }
            break;
        }
        case GameScene::GameState::GamePlay:
        {
            break;
        }
        case GameScene::GameState::GameOverWait:            //ゲームオーバーまでの待ち時間
        {
            this->m_GameOverWaitTime += dt;
            if(this->m_GameOverWaitTime > 0.5f)
            {
                this->setState(GameState::GameOver);
            }
            break;
        }
        case GameScene::GameState::GameOver:            //ゲームオーバー
        {
            this->moveToGameOver();
            break;
        }
        default:
            break;
    }
}

/**
 * 魂状態の人を削除
 */
void GameScene::removeObjectWithSoul()
{

    //弾のデリートチェック
    cocos2d::Vector<BulletObject*> deleteList;
    for(auto work : this->m_BulletList)
    {
        if(work->getAttack() <= 0 ||
           work->getPositionY() > (work->getContentSize().height + this->getContentSize().height))
        {
            this->m_BulletLayer->removeChild(work);
            deleteList.pushBack(work);
        }
    }
    for(auto work : deleteList)
    {
        this->m_BulletList.eraseObject(work);
    }
    deleteList.clear();
    
    //敵のデリートチェック
    cocos2d::Vector<EnemyObject*> deleteList2;
    for(auto work : this->m_EnemyList)
    {
        if(work->getState() == EnemyObject::EnemyState::SOUL ||
           work->getPositionY() < -work->getContentSize().height)
        {
            this->m_EnemyLayer->removeChild(work);
            deleteList2.pushBack(work);
        }
    }
    for(auto work : deleteList2)
    {
        this->m_EnemyList.eraseObject(work);
    }
    deleteList2.clear();
    
    
}

/**
 * 敵オブジェクトの追加
 */
void GameScene::entryEnemyObject(EnemyObject* obj)
{
    this->m_EnemyList.pushBack(obj);
    this->m_EnemyLayer->addChild(obj);
}

/**
 * 弾オブジェクトの追加
 */
void GameScene::entryBulletObject(BulletObject* obj)
{
    this->m_BulletList.pushBack(obj);
    this->m_BulletLayer->addChild(obj);
}

/**
 * スコア表示の更新
 */
void GameScene::refreshScoreLabel()
{
    char strScore[32] = "";
    sprintf(strScore,"%012d",GameData::getInstance()->getGameScore());
    this->m_ScoreLabel->setString(strScore);
}
/**
 * ゲームオーバー画面に移動
 */
void GameScene::moveToGameOver()
{
    Director::getInstance()->replaceScene(GameOverScene::createScene());
}

