
//
//  EnemyObject.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "EnemyObject.h"
#include "BulletObject.h"
#include "SimpleAudioEngine.h"

#define DEF_HIT_ANIME (0.25f)

USING_NS_CC;

EnemyObject::EnemyObject()
:m_MaxLife(1)
,m_Life(1)
,m_State(EnemyState::WAIT)
,m_Score(100)
,m_hitDelay(0)
{
    this->setHitLength(64.0f);

}
EnemyObject::~EnemyObject()
{
    
}
EnemyObject* EnemyObject::create(int charaId)
{
    EnemyObject * ret = nullptr;
    ret = new EnemyObject();
    if(ret && ret->init(charaId))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
    }
    return ret;
}
bool EnemyObject::init(int charaId)
{
    if(!HitObject::init())
    {
        return false;
    }
    this->m_mainSprite = nullptr;
    switch (charaId) {
        case 1:
            //ゴミ袋
            this->m_mainSprite = Sprite::create("game/enemy_gomibukuro.png");
            break;
        case 2:
            //ゴミ箱
            this->m_mainSprite = Sprite::create("game/enemy_gomibako.png");
            break;
        case 3:
            //空き缶
            this->m_mainSprite = Sprite::create("game/enemy_akikan.png");
            break;
        case 4:
            //冷蔵庫
            this->m_mainSprite = Sprite::create("game/enemy_reizouko.png");
            break;
        case 5:
            //岩
            this->m_mainSprite = Sprite::create("game/enemy_stone.png");
            break;
        case 6:
            //樹
            this->m_mainSprite = Sprite::create("game/enemy_wood.png");
            break;
        case 7:
            //テレビ
            this->m_mainSprite = Sprite::create("game/enemy_tv.png");
            break;
        default:
            this->m_mainSprite = Sprite::create("game/enemy.png");
            break;
    }

    
    this->addChild(this->m_mainSprite);
    this->setContentSize(this->m_mainSprite->getContentSize());
    this->setAnchorPoint(Vec2::ONE * 0.5f);
    
    this->m_mainSprite->setPosition(this->getContentSize()/2.0f);
    return true;
}

/**
 * 行動の更新
 */
void EnemyObject::updateAction(float dt)
{
    //ダメージ反映処理
    if(this->getState() == EnemyState::WAIT)
    {
        for(auto work : this->getHitObjectList() )
        {
            BulletObject * bullet = dynamic_cast<BulletObject*>(work);
            if(bullet)
            {
                this->setLife(this->getLife() - bullet->getAttack());
                this->setState(EnemyState::HIT);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/se_enemy_hit.mp3");
            }
        }
        //死亡判定
        if(this->getLife() < 0)
        {
            this->setEnabled(false);
            this->setState(EnemyState::DEAD);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/se_burst.mp3");
        }
        //ヒット状態のアニメーション
        if(this->getState() == EnemyState::HIT)
        {
            this->m_mainSprite->setColor(Color3B::RED);
        }
    }
    this->getHitObjectList().clear();
    
    //ヒット中のアニメーション
    if(this->getState() == EnemyState::HIT)
    {
        this->m_hitDelay += dt;
        if(this->m_hitDelay > DEF_HIT_ANIME)
        {
            this->m_hitDelay = 0;
            this->m_mainSprite->setColor(Color3B::WHITE);
            this->setState(EnemyState::WAIT);
        }
    }
    
    
    //死亡アニメーション
    if(this->getState() == EnemyState::DEAD)
    {
        if(this->m_mainSprite->getScale() > 2.0f)
        {
            this->setState(EnemyState::SOUL);
        }
        else
        {
            float rate = this->m_mainSprite->getScale() + (1.0f / 0.25f) * dt;
            this->m_mainSprite->setScale(rate);
        }
    }
}
/**
 * ダメージを受け入れるか
 */
bool EnemyObject::isUnlockOfDamage()
{
    if(this->getState() == EnemyState::WAIT)return true;
    return false;
}
/**
 * 生きているか
 */
bool EnemyObject::isAlive()
{
    return this->getLife() > 0;
}

