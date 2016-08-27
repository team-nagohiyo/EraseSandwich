//
//  HitObject.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#ifndef __care_of_road__HitObject__
#define __care_of_road__HitObject__

#include "cocos2d.h"

class HitObject : public cocos2d::Node
{
    cocos2d::Vector<HitObject*> m_HitObjectList;
    CC_SYNTHESIZE(bool, m_Enabled, Enabled);
    CC_SYNTHESIZE(float, m_HitLength, HitLength);
public:
    HitObject();
    virtual ~HitObject();
    
    virtual bool init();
    /**
     * ヒットした人を登録する
     */
    virtual void entryHitObject(HitObject * obj);
    
    /**
     * ヒットした人を登録する
     */
    cocos2d::Vector<HitObject*>& getHitObjectList();
};

#endif /* defined(__care_of_road__HitObject__) */
