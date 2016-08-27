//
//  GameMediator.h
//  care_of_road
//
//  Created by ooharayukio on 2015/09/17.
//
//

#ifndef __care_of_road__GameMediator__
#define __care_of_road__GameMediator__

#include "cocos2d.h"

//仲介管理クラスの定義のみ
class BulletObject;
class EnemyObject;
class hitObject;
class GameScene;

/**
 * ゲーム中のクラス間仲介者
 * @note 各オブジェクト行動に関わる指示の仲介
 */
class GameMediator
{
protected:
    GameScene * m_GameScene;
public:
    static GameMediator * getInstance();
    GameMediator();
    virtual ~GameMediator();
    
    virtual void setMediateGameScene(GameScene* target);
    
    /**
     * 弾を登録
     */
    virtual void entryBulletObjectToField(BulletObject * target);
    
    /**
     * 敵を登録
     */
    virtual void entryEnemyObjectToField(EnemyObject * target);
};

#endif /* defined(__care_of_road__GameMediator__) */
