//
//  RankingScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#include "Scene/RankingScene.h"
#include "Scene/TitleScene.h"
#include "Manager/GameData.h"

//#include "AppCCloudPlugin.h"

USING_NS_CC;

Scene* RankingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = RankingScene::create();
    scene->addChild(layer);
    return scene;
}
bool RankingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto titleSprite = Sprite::create("str/title_ranking.png");
    // position the sprite on the center of the screen
    titleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.height * 0.75f));
    
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
    sprintf(strScore,"%012d",GameData::getInstance()->getHighScore());
    
    auto label = Label::createWithBMFont("str/little_number.fnt",strScore);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    this->addChild(label, 2);
    
    auto networkMenuItem = MenuItemImage::create("str/menu_network_ranking.png", "str/menu_network_ranking.png");
    networkMenuItem->setCallback(CC_CALLBACK_1(RankingScene::moveToRanking, this));
    networkMenuItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 150.0f));
    
    auto topMenuItem = MenuItemImage::create("str/menu_top_menu.png", "str/menu_top_menu.png");
    topMenuItem->setCallback(CC_CALLBACK_1(RankingScene::moveToTitle, this));
    topMenuItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 250.0f));
    auto menu = Menu::create(networkMenuItem,topMenuItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}
/**
 * タイトル画面に移動
 */
void RankingScene::moveToTitle(cocos2d::Ref * sender)
{
    Director::getInstance()->replaceScene(TitleScene::createScene());
}
/**
 * ネットワークランキング画面に移動
 */
void RankingScene::moveToRanking(cocos2d::Ref * sender)
{
    // Gamersを開く
//    AppCCloudPlugin::Gamers::showGamersView();
}
