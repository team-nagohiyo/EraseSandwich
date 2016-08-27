//
//  PlayerObject.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#ifndef __care_of_road__PlayerObject__
#define __care_of_road__PlayerObject__

#include "cocos2d.h"
#include "HitObject.h"
#include "BulletObject.h"

/**
 * プレイヤーのオブジェクト
 */
class PlayerObject : public HitObject
{
public:
    //プレイヤーのステート
    enum struct PlayerState:int
    {
        Wait = 0,
        Shot,
        Delay,
        Charge,
        Hit,
        DeadBody,
        Soul,
    };
    
    //弾モード
    enum struct ShotMode : int
    {
        MachineGun,
        ChageShot,
    };
    CC_SYNTHESIZE(int, m_Type, Type);
    CC_SYNTHESIZE(int, m_Score, Score);
    CC_SYNTHESIZE(int, m_Life, Life);
    CC_SYNTHESIZE(PlayerState, m_State, State);
    
    CC_SYNTHESIZE(float, m_BasePower, BasePower);
    CC_SYNTHESIZE(float, m_ChargeMaxPower, ChargeMaxPower);
    CC_SYNTHESIZE(float, m_ChargeMaxTime, ChargeMaxTime);
    CC_SYNTHESIZE(float, m_ShotCycle, ShotCycle);
    
protected:
    cocos2d::Sprite * m_mainSprite;
    
    float m_ChargeTime;
    float m_Delay;
    float m_HitTime;
    ShotMode m_Mode;
    
    BulletObject * m_CatchBullet;
public:
    PlayerObject();
    virtual ~PlayerObject();
    static PlayerObject* create();
    virtual bool init();

    /**
     * 行動の更新
     */
    virtual void updateAction(float dt);
    
    /**
     * 弾の発射
     */
    virtual void OnMashinGun();
    
    /**
     * 弾の溜め
     */
    virtual void OnChage();
    
    /**
     * 弾の生成
     */
    virtual BulletObject * createBullet();
    
    /**
     * 生きているか
     */
    virtual bool isAlive();
    
};


#endif /* defined(__care_of_road__PlayerObject__) */
