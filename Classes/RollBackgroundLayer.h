//
//  RollBackgroundLayer.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/14.
//
//

#ifndef __care_of_road__RollBackgroundLayer__
#define __care_of_road__RollBackgroundLayer__

#include "cocos2d.h"

/**
 * スクロールする背景
 */
class RollBackgroundLayer : public cocos2d::Layer
{
protected:
    cocos2d::Vector<cocos2d::Sprite*> m_ScrollLayers;
    float m_MaxScrollHeight;
    float m_ScrollHeight;
    
    CC_SYNTHESIZE(float, m_Speed, Speed);
public:
    RollBackgroundLayer();
    virtual ~RollBackgroundLayer();
    CREATE_FUNC(RollBackgroundLayer);
    bool init();
    
    virtual void update(float dt);
    
    virtual void updatePosition();
};

#endif /* defined(__care_of_road__RollBackgroundLayer__) */
