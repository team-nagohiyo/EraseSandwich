//
//  TitleScene.h
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/14.
//
//

#ifndef __care_of_road__TitleScene__
#define __care_of_road__TitleScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "RollBackgroundLayer.h"


class TitleScene : public cocos2d::Layer
{
protected:
    RollBackgroundLayer * m_roll;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(TitleScene);

    /**
     * ゲーム画面に移動
     */
    void moveToGame(cocos2d::Ref * sender);
    /**
     * パワーアップ画面に移動
     */
    void moveToPowrUp(cocos2d::Ref * sender);
    /**
     * ランキング画面に移動
     */
    void moveToRanking(cocos2d::Ref * sender);
};


#endif /* defined(__care_of_road__TitleScene__) */
