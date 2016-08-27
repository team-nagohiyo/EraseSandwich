//
//  HitObject.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/09/16.
//
//

#include "HitObject.h"

HitObject::HitObject()
:m_Enabled(true)
,m_HitLength(0)
{
    
}
HitObject::~HitObject()
{
    
}

bool HitObject::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    m_HitObjectList.clear();
    
    return true;
}
/**
 * ヒットした人を登録する
 */
void HitObject::entryHitObject(HitObject * obj)
{
    this->m_HitObjectList.pushBack(obj);
}

cocos2d::Vector<HitObject*>& HitObject::getHitObjectList()
{
    return this->m_HitObjectList;
}
