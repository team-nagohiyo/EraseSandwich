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

/**
 ユニットたちが戦う画面上部のレイヤー
 */
class BattleScreenLayer
    :public cocos2d::Layer
{
protected:
    cocos2d::LayerGradient * m_Back;
public:
    BattleScreenLayer();
    virtual ~BattleScreenLayer();

    CREATE_FUNC(BattleScreenLayer);
    bool init() override;
    
};

#endif /* BattleScreenLayer_hpp */
