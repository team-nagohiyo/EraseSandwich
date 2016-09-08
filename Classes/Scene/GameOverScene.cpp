//
//  GameOverScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/22.
//
//

#include "Scene/GameOverScene.h"
#include "Manager/GameData.h"
#include "Scene/GameScene.h"
#include "Scene/PowerUpScene.h"
#include "Scene/RankingScene.h"
#include "Scene/TitleScene.h"

#include "SimpleAudioEngine.h"

//#include "UnityAdsWrapper.h"
//#include "AppCCloudPlugin.h"

#define DEF_BONUS_RATE (10.0f)

USING_NS_CC;
using namespace CocosDenshion;

GameOverScene::GameOverScene()
:m_CmMenuItem(nullptr)
,m_GetPointLabel(nullptr)
,m_GetPointValue(0)
{
}
GameOverScene::~GameOverScene()
{
    
}
Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}
bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto titleSprite = Sprite::create("str/title_game_over.png");
    // position the sprite on the center of the screen
    titleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.height/2 + origin.y + 300.0f));
    
    this->addChild(titleSprite, 10);
    
    this->m_roll = RollBackgroundLayer::create();
    this->addChild(this->m_roll,0);
    this->m_roll->setPosition(Vec2::ZERO);
    
    //メニュー
    auto labelScore = Sprite::create("str/label_score.png");
    labelScore->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height * 0.625f));
    this->addChild(labelScore, 3);
    char strScore[32] = "";
    sprintf(strScore,"%012d",GameData::getInstance()->getGameScore());
    
    //ハイスコアへの登録
    if(GameData::getInstance()->getHighScore() < GameData::getInstance()->getGameScore())
    {
        GameData::getInstance()->setHighScore(GameData::getInstance()->getGameScore());
    }
//    // ID：1885(Best score)のリーダーボードにスコア：セット
//    AppCCloudPlugin::Gamers::setLeaderBoard(1885, GameData::getInstance()->getGameScore());
    
//    // プレイカウントをインクリメント
//    AppCCloudPlugin::Gamers::incPlayCount();
    
    auto label = Label::createWithBMFont("str/little_number.fnt",strScore);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + 50.0f));
    this->addChild(label, 2);
    
    //ポイントの取得
    this->m_GetPointValue = GameData::getInstance()->getGameScore() * 0.01f;
    int totalPoint = GameData::getInstance()->getGamePoint() + this->m_GetPointValue;
    GameData::getInstance()->setGamePoint(totalPoint);
    
    this->m_GetPointLabel = Label::createWithBMFont("str/FNT_small_font_y.fnt","Get 000000000000 pt");
    this->m_GetPointLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    this->addChild(this->m_GetPointLabel, 2);
    this->refreshLabelGamePoint();

    
    cocos2d::Vector<MenuItem*> menuList;
    
    auto gameItem = MenuItemImage::create("str/menu_retry.png", "str/menu_retry.png");
    gameItem->setCallback(CC_CALLBACK_1(GameOverScene::moveToGame, this));
    gameItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                               visibleSize.width/2 + origin.y - 50.0f));
    menuList.pushBack(gameItem);
    
    auto powerUpItem = MenuItemImage::create("str/menu_power_up.png", "str/menu_power_up.png");
    powerUpItem->setCallback(CC_CALLBACK_1(GameOverScene::moveToPowrUp, this));
    powerUpItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 100.0f));
    menuList.pushBack(powerUpItem);
    
    auto rankingItem = MenuItemImage::create("str/menu_ranking.png", "str/menu_ranking.png");
    rankingItem->setCallback(CC_CALLBACK_1(GameOverScene::moveToRanking, this));
    rankingItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 150.0f));
    menuList.pushBack(rankingItem);
    
    auto topItem = MenuItemImage::create("str/menu_top_menu.png", "str/menu_top_menu.png");
    topItem->setCallback(CC_CALLBACK_1(GameOverScene::moveToTitle, this));
    topItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 200.0f));
    menuList.pushBack(topItem);

    //UnityAdsの広告判定
//    if(UnityAdsWrapper::canShow())
//    {
//        this->m_CmMenuItem = MenuItemImage::create("icon/icon_cm_point.png", "icon/icon_cm_point.png");
//        this->m_CmMenuItem->setCallback(CC_CALLBACK_1(GameOverScene::viewMoveCM, this));
//        this->m_CmMenuItem->setPosition(Vec2(visibleSize.width - this->m_CmMenuItem->getContentSize().width * 0.5f - 10.0f ,
//                                            (this->m_CmMenuItem->getContentSize().height * 0.5f) + 10.0f)
//                                       );
//        Vector<cocos2d::FiniteTimeAction *> actionList;
//        actionList.pushBack(DelayTime::create(0.5f));
//        actionList.pushBack(ScaleTo::create(0.25f, 1.1f));
//        actionList.pushBack(ScaleTo::create(0.25f, 1.0f));
//        this->m_CmMenuItem->runAction(RepeatForever::create(Sequence::create(actionList)));
//        menuList.pushBack(this->m_CmMenuItem);
//    }
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(menuList);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    //ポイントの保存
    GameData::getInstance()->saveSettingData();
    return true;
}
/**
 * ゲーム画面に移動
 */
void GameOverScene::moveToGame(Ref * sender)
{
//    // ネイティブ(バナー)消去
//    AppCCloudPlugin::Ad::hideMatchAppView();
    
    Director::getInstance()->replaceScene(GameScene::createScene());
}
/**
 * パワーアップ画面に移動
 */
void GameOverScene::moveToPowrUp(Ref * sender)
{
//    // ネイティブ(バナー)消去
//    AppCCloudPlugin::Ad::hideMatchAppView();
    
    Director::getInstance()->replaceScene(PowerUpScene::createScene());
}
/**
 * ランキング画面に移動
 */
void GameOverScene::moveToRanking(Ref * sender)
{
//    // ネイティブ(バナー)消去
//    AppCCloudPlugin::Ad::hideMatchAppView();
    
    Director::getInstance()->replaceScene(RankingScene::createScene());
}
/**
 * タイトル画面に移動
 */
void GameOverScene::moveToTitle(cocos2d::Ref * sender)
{
//    // ネイティブ(バナー)消去
//    AppCCloudPlugin::Ad::hideMatchAppView();
    
    Director::getInstance()->replaceScene(TitleScene::createScene());
}
/**
 * 動画CMの表示
 */
void GameOverScene::viewMoveCM(cocos2d::Ref * sender)
{
//    if(UnityAdsWrapper::canShow())
//    {
//        UnityAdsWrapper::show();
//        
//        auto gd = GameData::getInstance();
//        int getPoint = gd->getGameScore() * DEF_BONUS_RATE;
//        gd->setGamePoint(gd->getGamePoint() + getPoint);
//        
//        this->m_GetPointValue += getPoint;
//        
//        //仮ポイントを加算
//        this->refreshLabelGamePoint();
//    }
    
    this->m_CmMenuItem->setEnabled(false);
    this->m_CmMenuItem->setVisible(false);
    this->m_CmMenuItem->stopAllActions();
}

/**
 * 更新
 */
void GameOverScene::refreshLabelGamePoint()
{
    char strPoint[128] = "";
    sprintf(strPoint,"Get %12d pt",this->m_GetPointValue);
    
    //更新
    this->m_GetPointLabel->setString(strPoint);
}
