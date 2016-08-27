//
//  GameLevelPlanner.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/10/12.
//
//

#include "GameLevelPlanner.h"

/**
 * ステージ構成設定値
 */
float GameLevelPlanner::configurationStageSegment[][DEF_CONFIG_TYPE_MAX] =
{
    //蓄積値、出現重み、出現サイクル
    {8,3,   1.950f},
    {16,6,  1.900f},
    {24,9,  1.850f},
    {32,12, 1.800f},
    {40,15, 1.750f},
    {48,18, 1.700f},
    {56,21, 1.650f},
    {72,27, 1.550f},
    {80,30, 1.500f},
    {88,33, 1.450f},
    {96,36, 1.400f},
    {104,39,1.350f},
    {112,42,1.300f},
    {120,45,1.250f},
    {128,48,1.200f},
    {136,51,1.150f},
    {144,54,1.100f},
    {152,57,1.050f},
    {160,60,1.000f},
    {168,63,0.950f},
    {176,66,0.900f},
    {184,69,0.850f},
    {192,72,0.800f},
    {200,75,0.750f},
    {208,78,0.700f},
    {216,81,0.650f},
    {224,84,0.600f},
    {232,87,0.550f},
    {240,90,0.500f},
};

GameLevelPlanner::GameLevelPlanner()
{
    
}
GameLevelPlanner::~GameLevelPlanner()
{
    
}

GameLevelPlanner * GameLevelPlanner::getInstance()
{
    static GameLevelPlanner instance;
    return &instance;
}

/**
 * 敵の蓄積値
 */
float GameLevelPlanner::getGenerateAccumulationValue(int level)
{
    if(level > DEF_CONFIG_MAX_ROW_INDEX)level = DEF_CONFIG_MAX_ROW_INDEX;
    return configurationStageSegment[level][DEF_CONFIG_INDEX_ACCUMULATION];
}
/**
 * 敵の発生状況
 */
float GameLevelPlanner::getGenerateGroupWeight(int level)
{
    if(level > DEF_CONFIG_MAX_ROW_INDEX)level = DEF_CONFIG_MAX_ROW_INDEX;
    return configurationStageSegment[level][DEF_CONFIG_INDEX_GROUP_WEIGHT];
}
/**
 * 敵の発生周期
 */
float GameLevelPlanner::getGenerateCycleTime(int level)
{
    if(level > DEF_CONFIG_MAX_ROW_INDEX)level = DEF_CONFIG_MAX_ROW_INDEX;
    return configurationStageSegment[level][DEF_CONFIG_INDEX_CYCLE_TIME];
}

