//
//  RankingScene.h
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#ifndef __care_of_road__RankingScene__
#define __care_of_road__RankingScene__

#include "cocos2d.h"
#include "RollBackgroundLayer.h"

class RankingScene : public cocos2d::Layer
{
protected:
    RollBackgroundLayer * m_roll;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RankingScene);
    
    /**
     * タイトル画面に移動
     */
    void moveToTitle(cocos2d::Ref * sender);
    
    /**
     * ネットワークランキング画面に移動
     */
    void moveToRanking(cocos2d::Ref * sender);
};

#endif /* defined(__care_of_road__RankingScene__) */
