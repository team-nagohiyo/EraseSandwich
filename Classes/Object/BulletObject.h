//
//  BulletObject.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#ifndef __care_of_road__BulletObject__
#define __care_of_road__BulletObject__

#include "cocos2d.h"
#include "HitObject.h"

/**
 * 敵のオブジェクト
 */
class BulletObject : public HitObject
{
    CC_SYNTHESIZE(int, m_Id, Id);
    CC_SYNTHESIZE(int, m_Type, Type);
    CC_SYNTHESIZE(int, m_Score, Score);
    CC_SYNTHESIZE(int, m_Attack, Attack);
    
    //溜め変形率
    CC_SYNTHESIZE(float, m_ChageScale, ChageScale);
    //溜め回転速度
    CC_SYNTHESIZE(float, m_RotateSpeed, RotateSpeed);
    
protected:
    cocos2d::Sprite * m_mainSprite;
    
    //Catchしている人の保存
    cocos2d::Node * m_ChachParent;
public:
    BulletObject();
    virtual ~BulletObject();
    static BulletObject* create(int charaId);
    bool init(int charaId);
    
    /**
     * 行動の更新
     */
    virtual void updateAction(float dt);
    
    /**
     * 球を捕まえる(溜めている最中)
     */
    virtual void catchBody(cocos2d::Node *);
    
    /**
     * 行動が自由になる
     */
    virtual void freeBody();
    
    /**
     * 放たれる
     */
    virtual void shot();
};

#endif /* defined(__care_of_road__BulletObject__) */
