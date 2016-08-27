//
//  GameData.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#include "GameData.h"

USING_NS_CC;

//初期値
#define DEF_DEFAULT_BASE_POWER (1)
#define DEF_DEFAULT_CHARGE_POWER (1)
#define DEF_DEFAULT_CHARGE_TIME (1.5f)
#define DEF_DEFAULT_SHOT_CYCLE (1.0f)
#define DEF_DEFAULT_SHOT_SIZE (1.0f)
#define DEF_DEFAULT_PLAYER_HP (1)

//最大値
#define DEF_MAX_BASE_POWER (30)
#define DEF_MAX_CHARGE_POWER (30)
#define DEF_MIN_CHARGE_TIME (0.2f)
#define DEF_MIN_SHOT_CYCLE (0.2f)
#define DEF_MAX_SHOT_SIZE (3.0f)
#define DEF_MAX_PLAYER_HP (5)

//加算レート
#define DEF_ADD_BASE_POWER (1)
#define DEF_ADD_CHARGE_POWER (1)
#define DEF_ADD_CHARGE_TIME (0.05f)
#define DEF_ADD_SHOT_CYCLE (0.05f)
#define DEF_ADD_SHOT_SIZE (0.1f)
#define DEF_ADD_PLAYER_HP (1)

//消費レート
#define DEF_RATE_BASE_POWER (1.5f)
#define DEF_RATE_CHARGE_POWER (2.2f)
#define DEF_RATE_CHARGE_TIME (4.3f)
#define DEF_RATE_SHOT_CYCLE (3.8f)
#define DEF_RATE_SHOT_SIZE (0.1f)
#define DEF_RATE_PLAYER_HP (5.0f)

GameData::GameData()
{
#if COCOS2D_DEBUG
    this->resetdefaultValue();
    this->setGamePoint(100000);
    this->saveSettingData();
#endif
}
GameData * GameData::getInstance()
{
    static GameData instance;
    return &instance;
}
/**
 * スコアの取得
 */
int GameData::getHighScore()
{
    return UserDefault::getInstance()->getIntegerForKey("HighScore", 0);
}
/**
 * スコアの設定
 */
void GameData::setHighScore(int val)
{
     UserDefault::getInstance()->setIntegerForKey("HighScore", val);
}
/**
 * 基本値の読み込み
 */
void GameData::loadSettingData()
{
    //ポイント
    this->m_GamePoint = UserDefault::getInstance()->getIntegerForKey("GamePoint", 0);
    if(this->m_GamePoint < 0)this->m_GamePoint = 0;
    //最大パワー
    this->m_BasePower = UserDefault::getInstance()->getIntegerForKey("BasePower", 1);
    if(this->m_BasePower < 1)this->m_BasePower = 1;
    //チャージパワー
    this->m_ChargePower = UserDefault::getInstance()->getIntegerForKey("ChargePower", 1);
    if(this->m_ChargePower < 1)this->m_ChargePower = 1;
    //チャージ速度
    this->m_ChargeTime = UserDefault::getInstance()->getFloatForKey("ChargeTime", 1.5f);
    if(this->m_ChargeTime < 0.2f)this->m_ChargeTime = 0.2f;
    //連射ディレイ
    this->m_ShotCycle = UserDefault::getInstance()->getFloatForKey("ShotCycle", 1.0f);
    if(this->m_ShotCycle < 0.2f)this->m_ShotCycle = 0.2f;
    //弾の大きさ
    this->m_ShotSize = UserDefault::getInstance()->getFloatForKey("ShotSize", 1.0f);
    if(this->m_ShotSize < 1.0f)this->m_ShotSize = 1.0f;
    //プレイヤーのHP
    this->m_PlayerHp = UserDefault::getInstance()->getIntegerForKey("PlayerHp", 1);
    if(this->m_PlayerHp < 1)this->m_PlayerHp = 1;
}

/**
 * 基本値の保存
 */
void GameData::saveSettingData()
{
    //ポイント
    UserDefault::getInstance()->setIntegerForKey("GamePoint", this->m_GamePoint);
    //最大パワー
    UserDefault::getInstance()->setIntegerForKey("BasePower", this->m_BasePower);
    //チャージパワー
    UserDefault::getInstance()->setIntegerForKey("ChargePower", this->m_ChargePower);
    //チャージ速度
    UserDefault::getInstance()->setFloatForKey("ChargeTime", this->m_ChargeTime);
    //連射ディレイ
    UserDefault::getInstance()->setFloatForKey("ShotCycle", this->m_ShotCycle);
    //弾の大きさ
    UserDefault::getInstance()->setFloatForKey("ShotSize", this->m_ShotSize);
    //プレイヤーのHP
    UserDefault::getInstance()->setIntegerForKey("PlayerHp", this->m_PlayerHp);
}
/**
 * デバック用デフォルトリセット
 */
void GameData::resetdefaultValue()
{
    this->setBasePower(this->getDefaultValueBasePower());
    this->setChargePower(this->getDefaultValueChargePower());
    this->setChargeTime(this->getDefaultValueChargeTime());
    this->setShotCycle(this->getDefaultValueShotCycle());
    this->setShotSize(this->getDefaultValueShotSize());
    this->setPlayerHp(this->getDefaultValuePlayerHp());
}
//---------------------
//default値
//---------------------
/**
 * 基本パワー
 */
int GameData::getDefaultValueBasePower()
{
    return DEF_DEFAULT_BASE_POWER;
}
/**
 * チャージパワー
 */
int GameData::getDefaultValueChargePower()
{
    return DEF_DEFAULT_CHARGE_POWER;
}
/**
 * チャージ速度
 */
float GameData::getDefaultValueChargeTime()
{
    return DEF_DEFAULT_CHARGE_TIME;
}
/**
 * 連射ディレイ
 */
float GameData::getDefaultValueShotCycle()
{
    return DEF_DEFAULT_SHOT_CYCLE;
}
/**
 * 弾の大きさ
 */
float GameData::getDefaultValueShotSize()
{
    return DEF_DEFAULT_SHOT_SIZE;
}
/**
 * プレイヤーのHP
 */
int GameData::getDefaultValuePlayerHp()
{
    return DEF_DEFAULT_PLAYER_HP;
}

//---------------------
//加算値
//---------------------
/**
 * 最大パワー
 */
int GameData::getAddValueBasePower()
{
    return DEF_ADD_BASE_POWER;
}
/**
 * チャージパワー
 */
int GameData::getAddValueChargePower()
{
    return DEF_ADD_CHARGE_POWER;
}
/**
 * チャージ速度
 */
float GameData::getAddValueChargeTime()
{
    return DEF_ADD_CHARGE_TIME;
}
/**
 * 連射ディレイ
 */
float GameData::getAddValueShotCycle()
{
    return DEF_ADD_SHOT_CYCLE;
}
/**
 * 弾の大きさ
 */
float GameData::getAddValueShotSize()
{
    return DEF_ADD_SHOT_SIZE;
}
/**
 * プレイヤーのHP
 */
int GameData::getAddValuePlayerHp()
{
    return DEF_ADD_PLAYER_HP;
}
//---------------------
//最大値
//---------------------
/**
 * 最大パワー
 */
int GameData::getMaxValueBasePower()
{
    return DEF_MAX_BASE_POWER;
}
/**
 * チャージパワー
 */
int GameData::getMaxValueChargePower()
{
    return DEF_MAX_CHARGE_POWER;
}
/**
 * チャージ速度
 */
float GameData::getMinValueChargeTime()
{
    return DEF_MIN_CHARGE_TIME;
}
/**
 * 連射ディレイ
 */
float GameData::getMinValueShotCycle()
{
    return DEF_MIN_SHOT_CYCLE;
}
/**
 * 弾の大きさ
 */
float GameData::getMaxValueShotSize()
{
    return DEF_MAX_SHOT_SIZE;
}
/**
 * プレイヤーのHP
 */
int GameData::getMaxValuePlayerHp()
{
    return DEF_MAX_PLAYER_HP;
}
//---------------------
//消費レート値
//---------------------
/**
 * 基本パワー
 */
float GameData::getCostRateBasePower()
{
    return DEF_RATE_BASE_POWER;
}
/**
 * チャージパワー
 */
float GameData::getCostRateChargePower()
{
    return DEF_RATE_CHARGE_POWER;
}
/**
 * チャージ速度
 */
float GameData::getCostRateChargeTime()
{
    return DEF_RATE_CHARGE_TIME;
}
/**
 * 連射ディレイ
 */
float GameData::getCostRateShotCycle()
{
    return DEF_RATE_SHOT_CYCLE;
}
/**
 * 弾の大きさ
 */
float GameData::getCostRateShotSize()
{
    return DEF_RATE_SHOT_SIZE;
}
/**
 * プレイヤーのHP
 */
float GameData::getCostRatePlayerHp()
{
    return DEF_RATE_PLAYER_HP;
}


