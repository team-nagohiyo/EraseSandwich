//
//  PlayerObject.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "PlayerObject.h"
#include "GameMediator.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

PlayerObject::PlayerObject()
:m_CatchBullet(nullptr)
,m_State(PlayerState::Wait)
,m_ChargeTime(0)
{
    this->setHitLength(64.0f);
    this->setLife(1);
}
PlayerObject::~PlayerObject()
{
    
}
PlayerObject* PlayerObject::create()
{
    PlayerObject * ret = nullptr;
    ret = new PlayerObject();
    if(ret && ret->init())
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
bool PlayerObject::init()
{
    if(!HitObject::init())
    {
        return false;
    }
    this->m_mainSprite = Sprite::create("game/turtle.png");
    
    
    this->addChild(this->m_mainSprite);
    this->setContentSize(this->m_mainSprite->getContentSize());
    this->setAnchorPoint(Vec2::ONE * 0.5f);
    
    this->m_mainSprite->setPosition(this->getContentSize()/2.0f);

    this->m_ChargeTime = 0;
    this->m_Delay = 0;
    return true;
}

/**
 * 行動の更新
 */
void PlayerObject::updateAction(float dt)
{
    //ダメージ反映処理
    if(this->getState() != PlayerState::Hit)
    {
        if(!this->getHitObjectList().empty())
        {
            this->setState(PlayerState::Hit);
            this->m_ChargeTime = 0;
            this->getHitObjectList().clear();
            
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/se_enemy_hit.mp3");
            this->setLife(this->getLife() - 1);
            this->m_mainSprite->setColor(Color3B::RED);
        }
    }

    //待ち時間状態に入ったなら
    if(this->getState() == PlayerState::Delay || this->getState() == PlayerState::Wait)
    {
        if(this->m_Delay < 0)
        {
            //弾が生成タイミングなら
            this->m_CatchBullet = this->createBullet();
            GameMediator::getInstance()->entryBulletObjectToField(this->m_CatchBullet);
            this->m_CatchBullet->setPosition(this->getPosition());
            this->m_CatchBullet->setAttack(this->getBasePower());
            
            //charge中ステートの処理
            if(this->m_Mode == ShotMode::ChageShot)
            {
                //[状態切替]charge
                this->setState(PlayerState::Charge);
                this->m_CatchBullet->catchBody(this);
            }
            else
            {
                //[状態切替]ショット
                this->setState(PlayerState::Shot);
            }
            
            //待ち時間の初期化
            this->m_Delay += this->getShotCycle();
        }
        else
        {
            this->setState(PlayerState::Delay);
            this->m_Delay -= dt;
        }
    }
    
    //チャージ中の処理
    if(this->getState() == PlayerState::Charge)
    {
        float rate = (this->m_ChargeTime / this->getChargeMaxTime());
        if(rate > 1.0f)rate = 1.0f;
        if(this->m_CatchBullet)
        {
            this->m_CatchBullet->setChageScale(1.0f * (rate) + 1.0f);
            this->m_CatchBullet->setRotateSpeed((15.0f * 360.0f / 60) * rate);
        }
        
        //チャージ中にモードが変更されたら
        if(this->m_Mode == ShotMode::MachineGun ||
           this->m_ChargeTime > this->getChargeMaxTime()
           )
        {
            //[状態切替]ショット
            this->setState(PlayerState::Shot);
            this->m_CatchBullet->setAttack(this->getBasePower() + this->getChargeMaxTime() * rate);
        }
        else
        {
            this->m_ChargeTime += dt;
        }
    }
    
    //ショットの処理
    if(this->getState() == PlayerState::Shot)
    {
        this->m_ChargeTime = 0;
        this->m_CatchBullet->shot();
        this->m_CatchBullet = nullptr;
        
        //[状態切替]待ち時間の設定
        this->setState(PlayerState::Delay);
    }
    
    if(this->getState() == PlayerState::Hit)
    {
        this->m_HitTime += dt;
        if(this->m_HitTime > 0.5f)
        {
            this->m_HitTime = 0;
            this->m_ChargeTime = 0;
            this->m_mainSprite->setColor(Color3B::WHITE);
            this->setState(PlayerState::Delay);
        }
    }
    
}

/**
 * 弾の発射
 */
void PlayerObject::OnMashinGun()
{
    this->m_Mode = ShotMode::MachineGun;
}

/**
 * 弾の溜め
 */
void PlayerObject::OnChage()
{
    this->m_Mode = ShotMode::ChageShot;
}

/**
 * 弾の生成
 */
BulletObject * PlayerObject::createBullet()
{
    BulletObject * ret = nullptr;
    ret = BulletObject::create(0);
    return ret;
}

/**
 * 生きているか
 */
bool PlayerObject::isAlive()
{
    return this->getLife() > 0;
}
