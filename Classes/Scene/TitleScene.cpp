//
//  TitleScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/14.
//
//

#include "Scene/TitleScene.h"
#include "Manager/GameData.h"
#include "Scene/GameScene.h"
#include "Scene/PowerUpScene.h"
#include "Scene/RankingScene.h"

#include "SimpleAudioEngine.h"
//#include "UnityAdsWrapper.h"
//#include "AppCCloudPlugin.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}
bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto titleSprite = cocos2d::ui::Text::create("Erase Sandwich", "fonts/Marker Felt.ttf", 70);
    titleSprite->enableOutline(Color4B::BLACK,5);
    
    // position the sprite on the center of the screen
    titleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.height/2 + origin.y + 300.0f));
    
    this->addChild(titleSprite, 10);

    this->m_roll = RollBackgroundLayer::create();
    this->addChild(this->m_roll,0);
    this->m_roll->setPosition(Vec2::ZERO);
    
    //メニュー
    auto gameItem = MenuItemImage::create("str/menu_game_start.png", "str/menu_game_start.png");
    gameItem->setCallback(CC_CALLBACK_1(TitleScene::moveToGame, this));
    gameItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                               visibleSize.width/2 + origin.y - 50.0f));
    
    auto powerUpItem = MenuItemImage::create("str/menu_power_up.png", "str/menu_power_up.png");
    powerUpItem->setCallback(CC_CALLBACK_1(TitleScene::moveToPowrUp, this));
    powerUpItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                               visibleSize.width/2 + origin.y - 150.0f));
    
    auto rankingItem = MenuItemImage::create("str/menu_ranking.png", "str/menu_ranking.png");
    rankingItem->setCallback(CC_CALLBACK_1(TitleScene::moveToRanking, this));
    rankingItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                               visibleSize.width/2 + origin.y - 250.0f));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(gameItem, powerUpItem,rankingItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    //音楽は常に流しっぱなし
    if(false == SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        //SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/cow_bgm_Sunrise.mp3",true);
    }

    //データの初回読み込み
    GameData::getInstance()->loadSettingData();
    GameData::getInstance()->saveSettingData();
    
    //
    
    
    return true;
}
/**
 * ゲーム画面に移動
 */
void TitleScene::moveToGame(Ref * sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
/**
 * パワーアップ画面に移動
 */
void TitleScene::moveToPowrUp(Ref * sender)
{
    Director::getInstance()->replaceScene(PowerUpScene::createScene());
}
/**
 * ランキング画面に移動
 */
void TitleScene::moveToRanking(Ref * sender)
{
    Director::getInstance()->replaceScene(RankingScene::createScene());
}
