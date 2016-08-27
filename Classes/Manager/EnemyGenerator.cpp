//
//  EnemyGenerator.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/20.
//
//

#include "EnemyGenerator.h"
#include "EnemyObject.h"
#include "GameMediator.h"
#include "GameLevelPlanner.h"

USING_NS_CC;

//エネミーデータクラス

EnemyGenerator::EnemyData::EnemyData()
{
    
}
EnemyGenerator::EnemyData::~EnemyData()
{
    
}


//エネミージェネレーターのクラス

EnemyGenerator::EnemyGenerator()
:m_Level(0)
{
    //name weight life
    //ゴミ袋	1	1
    EnemyData enemy1;
    enemy1.setId(1);
    enemy1.setName("ゴミ袋");
    enemy1.setBaseWeight(1);
    enemy1.setBaseLife(1);
    m_EnemyLibrary.push_back(enemy1);

    //ゴミ箱	2	2
    EnemyData enemy2;
    enemy2.setId(2);
    enemy2.setName("ゴミ箱");
    enemy2.setBaseWeight(2);
    enemy2.setBaseLife(2);
    m_EnemyLibrary.push_back(enemy2);

    //空き缶	6	5
    EnemyData enemy3;
    enemy3.setId(3);
    enemy3.setName("空き缶");
    enemy3.setBaseWeight(6);
    enemy3.setBaseLife(5);
    m_EnemyLibrary.push_back(enemy3);

    //冷蔵庫	18	7
    EnemyData enemy4;
    enemy4.setId(4);
    enemy4.setName("冷蔵庫");
    enemy4.setBaseWeight(18);
    enemy4.setBaseLife(7);
    m_EnemyLibrary.push_back(enemy4);

    //岩	33	10
    EnemyData enemy5;
    enemy5.setId(5);
    enemy5.setName("岩");
    enemy5.setBaseWeight(6);
    enemy5.setBaseLife(5);
    m_EnemyLibrary.push_back(enemy5);

    //樹	21	4
    EnemyData enemy6;
    enemy6.setId(6);
    enemy6.setName("樹");
    enemy6.setBaseWeight(21);
    enemy6.setBaseLife(4);
    m_EnemyLibrary.push_back(enemy6);

    //テレビ	12	5
    EnemyData enemy7;
    enemy7.setId(7);
    enemy7.setName("テレビ");
    enemy7.setBaseWeight(12);
    enemy7.setBaseLife(5);
    m_EnemyLibrary.push_back(enemy7);
}
/**
 * シングルトンinstance
 */
EnemyGenerator * EnemyGenerator::getInstance()
{
    static EnemyGenerator instance;
    return &instance;
}
/**
 * ランダムで敵を選択する
 */
EnemyGenerator::EnemyData* EnemyGenerator::choiceRandomEnemyData(float weight)
{
    std::vector<EnemyData*> work;
    auto it = this->m_EnemyLibrary.begin();
    while(it != this->m_EnemyLibrary.end())
    {
        if(it->getBaseWeight() <= weight)
        {
            //EnemyLibraryに格納されてるインスタンスのアドレスを取得
            work.push_back(&(*it));
        }
        it++;
    }
    if(work.size() <= 0)return nullptr;
    int index = std::rand()%work.size();
    return work[index];
}

/**
 * ジェネレート
 */
void EnemyGenerator::updateSchedule(float dt)
{
    this->m_createDelay -= dt;
    
    //敵の生成
    if(this->m_createDelay < 0.0f)
    {
        //重み分連続で作成する
        float groupWeight = GameLevelPlanner::getInstance()->getGenerateGroupWeight(this->m_Level);
        while(groupWeight > 0)
        {
            auto enemyData = this->choiceRandomEnemyData(groupWeight);
            if(enemyData == nullptr)break;//敵を探せなかったら中止
            auto enemy = EnemyObject::create(enemyData->getId());
            int wkLife = enemyData->getBaseLife() + this->m_Level;
            enemy->setLife(wkLife);
            float workX = this->getGeneratePosition().x;
            float workY = this->getGeneratePosition().y;
            float width = this->getGenerateWidth() - enemy->getContentSize().width;
            workX += (random(0.0f, width) + (enemy->getContentSize().width / 2.0f) - workX);
            enemy->setPosition(Vec2(workX,workY));
            GameMediator::getInstance()->entryEnemyObjectToField(enemy);
            
            //生成数
            this->setMakeCount(this->getMakeCount()+ 1);
            
            //敵重さ分蓄積値を減らすことでレベルアップさせる
            this->m_nextLevel -= enemyData->getBaseWeight();
            
            groupWeight -= enemyData->getBaseWeight();
        }

        //レベルアップ条件を達成するか
        if(this->m_nextLevel <= 0)
        {
            CCLOG("レベルアップ");
            this->m_Level++;
            this->m_nextLevel = GameLevelPlanner::getInstance()->getGenerateAccumulationValue(this->getLevel());
        }
        
        this->m_createDelay = GameLevelPlanner::getInstance()->getGenerateCycleTime(this->getLevel());
    }
}
/**
 * カウントの初期化
 */
void EnemyGenerator::reset()
{
    this->m_createDelay = 0.0f;
    this->setMakeCount(0);
    this->setLevel(0);

    //次回レベルの値
    this->m_nextLevel = GameLevelPlanner::getInstance()->getGenerateAccumulationValue(this->getLevel());
    
    this->m_createDelay = GameLevelPlanner::getInstance()->getGenerateCycleTime(this->getLevel());
}

