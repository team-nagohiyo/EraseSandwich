 //
//  BattleScreenLayer.hpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#ifndef BattleScreenLayer_hpp
#define BattleScreenLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Common/GaugeController.h"

/**
 ユニットたちが戦う画面上部のレイヤー
 */
class BattleScreenLayer
    :public cocos2d::Layer
{
protected:
    cocos2d::LayerGradient * m_Back;
    cocos2d::Sprite *m_background;
    GaugeController m_gauge;
    
    cocos2d::Sprite *m_debugUnit;
    cocos2d::Sprite *m_debugGauge;
    float m_debugGaugeValue;
    float m_debugGaugeTime;
public:
    BattleScreenLayer();
    virtual ~BattleScreenLayer();

    CREATE_FUNC(BattleScreenLayer);
    bool init() override;
    
    //画面の情報更新
    virtual void update(float delta);
};

#endif /* BattleScreenLayer_hpp */
