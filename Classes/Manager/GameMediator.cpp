//
//  GameMediator.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/17.
//
//

#include "GameMediator.h"
#include "GameScene.h"

GameMediator * GameMediator::getInstance()
{
    static GameMediator instance;
    return &instance;
}
GameMediator::GameMediator()
:m_GameScene(nullptr)
{
    
}
GameMediator::~GameMediator()
{
    
}

/**
 * 仲介ターゲット設定
 */
void GameMediator::setMediateGameScene(GameScene* target)
{
    this->m_GameScene = target;
}

/**
 * 弾を登録
 */
void GameMediator::entryBulletObjectToField(BulletObject * target)
{
    if(this->m_GameScene)
    {
        this->m_GameScene->entryBulletObject(target);
    }
}

/**
 * 敵を登録
 */
void GameMediator::entryEnemyObjectToField(EnemyObject * target)
{
    if(this->m_GameScene)
    {
        this->m_GameScene->entryEnemyObject(target);
    }
}
