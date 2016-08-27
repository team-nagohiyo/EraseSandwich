//
//  GameData.h
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#ifndef __care_of_road__GameData__
#define __care_of_road__GameData__

#include "cocos2d.h"

class GameData
{
    
    //移動量
    CC_SYNTHESIZE(float, m_GroundHeightMove, GroundHeightMove);
    //Gameスコア
    CC_SYNTHESIZE(int, m_GameScore, GameScore);
    //ポイント
    CC_SYNTHESIZE(int, m_GamePoint, GamePoint);
    
    //最大パワー
    CC_SYNTHESIZE(int, m_BasePower, BasePower);
    //チャージパワー
    CC_SYNTHESIZE(int, m_ChargePower, ChargePower);
    //チャージ速度
    CC_SYNTHESIZE(float, m_ChargeTime, ChargeTime);
    //連射ディレイ
    CC_SYNTHESIZE(float, m_ShotCycle, ShotCycle);
    //弾の大きさ
    CC_SYNTHESIZE(float, m_ShotSize, ShotSize);
    //プレイヤーのHP
    CC_SYNTHESIZE(int, m_PlayerHp, PlayerHp);
    
public:
    GameData();
    static GameData * getInstance();
    
    /**
     * スコアの取得
     */
    int getHighScore();
    /**
     * スコアの設定
     */
    void setHighScore(int val);
    
    /**
     * 基本値の読み込み
     */
    void loadSettingData();
    
    /**
     * 基本値の保存
     */
    void saveSettingData();
    
    /**
     * デバック用デフォルトリセット
     */
    void resetdefaultValue();

    //---------------------
    //default値
    //---------------------
    /**
     * 基本パワー
     */
    virtual int getDefaultValueBasePower();
    /**
     * チャージパワー
     */
    virtual int getDefaultValueChargePower();
    /**
     * チャージ速度
     */
    virtual float getDefaultValueChargeTime();
    /**
     * 連射ディレイ
     */
    virtual float getDefaultValueShotCycle();
    /**
     * 弾の大きさ
     */
    virtual float getDefaultValueShotSize();
    /**
     * プレイヤーのHP
     */
    virtual int getDefaultValuePlayerHp();

    //---------------------
    //加算値
    //---------------------
    /**
     * 基本パワー
     */
    virtual int getAddValueBasePower();
    /**
     * チャージパワー
     */
    virtual int getAddValueChargePower();
    /**
     * チャージ速度
     */
    virtual float getAddValueChargeTime();
    /**
     * 連射ディレイ
     */
    virtual float getAddValueShotCycle();
    /**
     * 弾の大きさ
     */
    virtual float getAddValueShotSize();
    /**
     * プレイヤーのHP
     */
    virtual int getAddValuePlayerHp();
    
    //---------------------
    //最大値
    //---------------------
    /**
     * 基本パワー
     */
    virtual int getMaxValueBasePower();
    /**
     * チャージパワー
     */
    virtual int getMaxValueChargePower();
    /**
     * チャージ速度
     */
    virtual float getMinValueChargeTime();
    /**
     * 連射ディレイ
     */
    virtual float getMinValueShotCycle();
    /**
     * 弾の大きさ
     */
    virtual float getMaxValueShotSize();
    /**
     * プレイヤーのHP
     */
    virtual int getMaxValuePlayerHp();
    
    //---------------------
    //消費レート値
    //---------------------
    /**
     * 基本パワー
     */
    virtual float getCostRateBasePower();
    /**
     * チャージパワー
     */
    virtual float getCostRateChargePower();
    /**
     * チャージ速度
     */
    virtual float getCostRateChargeTime();
    /**
     * 連射ディレイ
     */
    virtual float getCostRateShotCycle();
    /**
     * 弾の大きさ
     */
    virtual float getCostRateShotSize();
    /**
     * プレイヤーのHP
     */
    virtual float getCostRatePlayerHp();
};

#endif /* defined(__care_of_road__GameData__) */
