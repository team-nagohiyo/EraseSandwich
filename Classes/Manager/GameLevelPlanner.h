//
//  GameLevelPlanner.h
//  care_of_road
//
//  Created by 大原幸夫 on 2015/10/12.
//
//

#ifndef GameLevelPlanner_h
#define GameLevelPlanner_h

#include <stdio.h>

#define DEF_CONFIG_INDEX_ACCUMULATION (0)
#define DEF_CONFIG_INDEX_GROUP_WEIGHT (1)
#define DEF_CONFIG_INDEX_CYCLE_TIME (2)
#define DEF_CONFIG_TYPE_MAX (3)
#define DEF_CONFIG_MAX_ROW_INDEX (28)

/**
 * プレイ中の変化するレベル条件を管理する
 */
class GameLevelPlanner
{
protected:
    /**
     * ステージ構成設定値
     */
    static float configurationStageSegment[][DEF_CONFIG_TYPE_MAX];
public:
    GameLevelPlanner();
    virtual ~GameLevelPlanner();
    static GameLevelPlanner * getInstance();
    
    
    /**
     * 敵の蓄積値
     */
    float getGenerateAccumulationValue(int level);
    /**
     * 敵の発生状況
     */
    float getGenerateGroupWeight(int level);
    /**
     * 敵の発生周期
     */
    float getGenerateCycleTime(int level);
};

#endif /* GameLevelPlanner_h */
