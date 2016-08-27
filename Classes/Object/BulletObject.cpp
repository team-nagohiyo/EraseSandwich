//
//  BulletObject.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "BulletObject.h"
#include "EnemyObject.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SHOT_MOVE_VEC (cocos2d::Vec2(0,30.0f))

BulletObject::BulletObject()
:m_ChachParent(nullptr)
,m_RotateSpeed(5.0f*360.0f/60)
,m_ChageScale(1.0f)
,m_Attack(1)
{
    this->setHitLength(64.0f);

}
BulletObject::~BulletObject()
{
    
}
BulletObject* BulletObject::create(int charaId)
{
    BulletObject * ret = nullptr;
    ret = new BulletObject();
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
bool BulletObject::init(int charaId)
{
    if(!HitObject::init())
    {
        return false;
    }
    
    this->m_mainSprite = nullptr;
    switch (charaId)
    {
        default:
        case 0:
            m_mainSprite = Sprite::create("game/ball.png");
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
void BulletObject::updateAction(float dt)
{
    //ダメージ判定
    for(auto work : this->getHitObjectList() )
    {
        EnemyObject * enemy = dynamic_cast<EnemyObject*>(work);
        if(enemy)
        {
            if(this->getAttack() > enemy->getMaxLife())
            {
                this->setAttack(this->getAttack() - enemy->getMaxLife());
            }
            else
            {
                this->setAttack(0);
            }
        }
    }
    this->getHitObjectList().clear();
    
    if(this->m_ChachParent)
    {
        this->setPosition(this->m_ChachParent->getPosition() + Vec2(0,50));
    }
    else
    {
        this->setPosition(this->getPosition() + SHOT_MOVE_VEC);
    }
    
    //回転処理
    this->m_mainSprite->setRotation(this->m_mainSprite->getRotation() + this->getRotateSpeed());
    //charge変形処理
    if(this->getChageScale() < 0.5f)
    {
        this->setChageScale(0.5f);
    }
    this->m_mainSprite->setScaleY(this->getChageScale());
}

/**
 * 球を捕まえる(溜めている最中)
 */
void BulletObject::catchBody(cocos2d::Node * target)
{
    this->m_ChachParent = target;
    this->setEnabled(false);
}
/**
 * 行動が自由になる
 */
void BulletObject::freeBody()
{
    this->m_ChachParent = nullptr;
    this->setEnabled(true);
}
/**
 * 放たれる
 */
void BulletObject::shot()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/se_shot.mp3");
    
    this->freeBody();
    this->m_ChachParent = nullptr;
}

