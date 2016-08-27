//
//  PowerUpScene.h
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#ifndef __care_of_road__PowerUpScene__
#define __care_of_road__PowerUpScene__

#include "cocos2d.h"
#include "RollBackgroundLayer.h"

class PowerUpScene : public cocos2d::Layer
{
protected:
    enum PowerUpItemType: int
    {
        None,
        ShotPower,
        ShotCycle,
        ChargePower,
        ChargeTime,
        ShotSize,
        PlayerLife,
    };
    
    RollBackgroundLayer * m_roll;

    //ポイント
    cocos2d::Sprite * m_LabelPoint;
    cocos2d::Label * m_ValuePoint;
    
    //ノーマルショットパワー
    cocos2d::Sprite * m_LabelBasePower;
    cocos2d::Label * m_ValueBasePowerValue;
    cocos2d::Label * m_ValueBasePowerCost;
    cocos2d::MenuItem * m_MenuBasePower;
    int m_CostBasePower;
    
    //連射
    cocos2d::Sprite * m_LabelShotCycle;
    cocos2d::Label * m_ValueShotCycleValue;
    cocos2d::Label * m_ValueShotCycleCost;
    cocos2d::MenuItem * m_MenuShotCycle;
    int m_CostShotCycle;
    
    //チャージパワー
    cocos2d::Sprite * m_LabelChargePower;
    cocos2d::Label * m_ValueChargePowerValue;
    cocos2d::Label * m_ValueChargePowerCost;
    cocos2d::MenuItem * m_MenuChargePower;
    int m_CostChargePower;
    
    //チャージ時間
    cocos2d::Sprite * m_LabelChargeTime;
    cocos2d::Label * m_ValueChargeTimeValue;
    cocos2d::Label * m_ValueChargeTimeCost;
    cocos2d::MenuItem * m_MenuChargeTime;
    int m_CostChargeTime;
    
    //プレイヤーLife
    cocos2d::Sprite * m_LabelPlayerLife;
    cocos2d::Label * m_ValuePlayerLifeValue;
    cocos2d::Label * m_ValuePlayerLifeCost;
    cocos2d::MenuItem * m_MenuPlayerLife;
    int m_CostPlayerLife;
    
    
    /**
     * メニューの作成
     */
    cocos2d::MenuItem * makeMenuItemRect(PowerUpItemType itemType);
    
    /**
     * メニューの数値更新
     */
    void updateValue();
    
    /**
     * 消費値の計算
     */
    template<typename T>
    int calcDownValueCost(float rate,T currentVal,T defaultVal, T AddVal)
    {
        T val = defaultVal - currentVal + AddVal;
        val /= AddVal;
        int cost;
        cost = pow(val, rate) * 10.0f;
        return cost;
    }
    /**
     * 消費値の計算
     */
    template<typename T>
    int calcUpValueCost(float rate,T currentVal,T defaultVal, T AddVal)
    {
        T val = currentVal - defaultVal + AddVal;
        val /= AddVal;
        int cost;
        cost = pow(val, rate) * 10.0f;
        return cost;
    }
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(PowerUpScene);
    
    /**
     * パワーアップメニューの選択
     */
    void onPowerUpItem(cocos2d::Ref * sender);
    
    /**
     * タイトル画面に移動
     */
    void moveToTitle(cocos2d::Ref * sender);
};


#endif /* defined(__care_of_road__PowerUpScene__) */
