//
//  DebugLayer.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/14.
//
//

#ifndef __care_of_road__DebugLayer__
#define __care_of_road__DebugLayer__

#include "cocos2d.h"

/**
 * スクロールする背景
 */
class DebugLayer : public cocos2d::Layer
{
protected:
    cocos2d::Vector<cocos2d::Sprite*> m_ScrollLayers;
    float m_MaxScrollHeight;
    float m_ScrollHeight;
    
    CC_SYNTHESIZE(float, m_Speed, Speed);
public:
    DebugLayer();
    virtual ~DebugLayer();
    CREATE_FUNC(DebugLayer);
    bool init();
    
    virtual void update(float dt);
    
    virtual void updatePosition();
};

#endif /* defined(__care_of_road__DebugLayer__) */
