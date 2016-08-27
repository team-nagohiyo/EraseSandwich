//
//  EnemyObject.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#ifndef __care_of_road__EnemyObject__
#define __care_of_road__EnemyObject__

#include "cocos2d.h"
#include "HitObject.h"

/**
 * 敵のオブジェクト
 */
class EnemyObject : public HitObject
{
public:
    enum struct EnemyState:int
    {
        WAIT = 0,
        HIT,
        DEAD,
        SOUL
    };
    CC_SYNTHESIZE(int, m_Id, Id);
    CC_SYNTHESIZE(int, m_Type, Type);
    CC_SYNTHESIZE(int, m_Score, Score);
    CC_SYNTHESIZE(int, m_Life, Life);
    CC_SYNTHESIZE(int, m_MaxLife, MaxLife);
    CC_SYNTHESIZE(EnemyState, m_State, State);
protected:
    cocos2d::Sprite * m_mainSprite;
    
    float m_hitDelay;

public:
    EnemyObject();
    virtual ~EnemyObject();
    static EnemyObject* create(int charaId);
    bool init(int charaId);
    
    /**
     * 行動の更新
     */
    virtual void updateAction(float dt);
    
    /**
     * ダメージを受け入れるか
     */
    virtual bool isUnlockOfDamage();

    /**
     * 生きているか
     */
    virtual bool isAlive();
};

#endif /* defined(__care_of_road__EnemyObject__) */
