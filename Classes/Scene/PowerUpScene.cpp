//
//  PowerUpScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2015/09/16.
//
//

#include "PowerUpScene.h"
#include "TitleScene.h"
#include "GameData.h"


#define DEF_TITLE_Y (400.0f)
#define DEF_POINT_Y (300.0f)
#define DEF_LABEL_Y (150.0f)
#define DEF_LABEL_Y_MARGIN (110.0f)
#define DEF_LABEL_Y_LAYER_BOTTOM (10.0f)

#define DEF_LABEL_ANCHOR (cocos2d::Vec2(0,0))
#define DEF_NAME_X (30.0f)
#define DEF_NAME_Y (50.0f)
#define DEF_VALUE_X (100.0f)
#define DEF_COST_X (400.0f)
#define DEF_COST_Y_MARGIN (40.0f)

#define DEF_TAPLAYER_RECT_WIDTH (600.0f)
#define DEF_TAPLAYER_RECT_HEIGHT (100.0f)

USING_NS_CC;

Scene* PowerUpScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PowerUpScene::create();
    scene->addChild(layer);
    return scene;
}
bool PowerUpScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto backLayer = LayerColor::create(cocos2d::Color4B(0,0,0,0x7F));
    this->addChild(backLayer,1);
    
    auto titleSprite = Sprite::create("str/title_power_up.png");
    // position the sprite on the center of the screen
    titleSprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.height/2 + origin.y + DEF_TITLE_Y));
    
    this->addChild(titleSprite, 10);
    this->m_roll = RollBackgroundLayer::create();
    this->addChild(this->m_roll,0);
    this->m_roll->setPosition(Vec2::ZERO);
    
    //----------------
    //メニュー
    //----------------
    
    this->m_ValuePoint = Label::createWithBMFont("str/FNT_small_font_y.fnt","000000000 p");
    this->m_ValuePoint->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.height/2 + origin.y + DEF_POINT_Y));
    
    this->addChild(m_ValuePoint, 10);

    cocos2d::Vector<MenuItem*> menuList;
    
    float UpLabelPosY = visibleSize.height/2 + origin.y + DEF_LABEL_Y;
    
    //ノーマルショットパワーアップ
    this->m_MenuBasePower = this->makeMenuItemRect(PowerUpItemType::ShotPower);
    this->m_MenuBasePower->setPosition(Vec2(visibleSize.width/2 + origin.x,UpLabelPosY));
    this->m_MenuBasePower->setCallback(CC_CALLBACK_1(PowerUpScene::onPowerUpItem, this));
    menuList.pushBack(this->m_MenuBasePower);
    
    UpLabelPosY -= DEF_LABEL_Y_MARGIN;
    
    //連射時間
    this->m_MenuShotCycle = this->makeMenuItemRect(PowerUpItemType::ShotCycle);
    this->m_MenuShotCycle->setPosition(Vec2(visibleSize.width/2 + origin.x,UpLabelPosY));
    this->m_MenuShotCycle->setCallback(CC_CALLBACK_1(PowerUpScene::onPowerUpItem, this));
    menuList.pushBack(this->m_MenuShotCycle);

    UpLabelPosY -= DEF_LABEL_Y_MARGIN;

    //チャージショット最大パワー
    this->m_MenuChargePower = this->makeMenuItemRect(PowerUpItemType::ChargePower);
    this->m_MenuChargePower->setPosition(Vec2(visibleSize.width/2 + origin.x,UpLabelPosY));
    this->m_MenuChargePower->setCallback(CC_CALLBACK_1(PowerUpScene::onPowerUpItem, this));
    menuList.pushBack(this->m_MenuChargePower);
    
    UpLabelPosY -= DEF_LABEL_Y_MARGIN;
    
    //チャージ時間
    this->m_MenuChargeTime = this->makeMenuItemRect(PowerUpItemType::ChargeTime);
    this->m_MenuChargeTime->setPosition(Vec2(visibleSize.width/2 + origin.x,UpLabelPosY));
    this->m_MenuChargeTime->setCallback(CC_CALLBACK_1(PowerUpScene::onPowerUpItem, this));
    menuList.pushBack(this->m_MenuChargeTime);

    UpLabelPosY -= DEF_LABEL_Y_MARGIN;
    
    //プレイヤーHP
    this->m_MenuPlayerLife = this->makeMenuItemRect(PowerUpItemType::PlayerLife);
    this->m_MenuPlayerLife->setPosition(Vec2(visibleSize.width/2 + origin.x,UpLabelPosY));
    this->m_MenuPlayerLife->setCallback(CC_CALLBACK_1(PowerUpScene::onPowerUpItem, this));
    menuList.pushBack(this->m_MenuPlayerLife);
    
    
    auto topMenuItem = MenuItemImage::create("str/menu_top_menu.png", "str/menu_top_menu.png");
    topMenuItem->setCallback(CC_CALLBACK_1(PowerUpScene::moveToTitle, this));
    topMenuItem->setPosition(Vec2(visibleSize.width/2 + origin.x,
                                  visibleSize.width/2 + origin.y - 250.0f));
    menuList.pushBack(topMenuItem);
    
    auto menu = Menu::createWithArray(menuList);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    this->updateValue();
    
    return true;
}
/**
 * タイトル画面に移動
 */
void PowerUpScene::moveToTitle(cocos2d::Ref * sender)
{
    Director::getInstance()->replaceScene(TitleScene::createScene());    
}
/**
 * メニューの作成
 */
cocos2d::MenuItem * PowerUpScene::makeMenuItemRect(PowerUpItemType itemType)
{
    MenuItem * ret = MenuItem::create();
    auto tapRect = LayerColor::create(Color4B(0xFF,0xFF,0xFF,0x7F), DEF_TAPLAYER_RECT_WIDTH, DEF_TAPLAYER_RECT_HEIGHT);
    ret->addChild(tapRect,1);
    ret->setContentSize(tapRect->getContentSize());
    
    cocos2d::Sprite * labelSprite = nullptr;
    cocos2d::Label * Valuelabel = nullptr;
    cocos2d::Label * CostLabel = Label::createWithBMFont("str/FNT_small_font_y.fnt","0000000p");
    cocos2d::Sprite * labelSpriteCost = Sprite::create("str/label_cost.png");
    
    switch (itemType)
    {
        case PowerUpItemType::ShotPower :
        {
            //ノーマルショットパワーアップ
            this->m_LabelBasePower = Sprite::create("str/label_shot_power.png");
            labelSprite = this->m_LabelBasePower;
            this->m_ValueBasePowerValue = Label::createWithBMFont("str/FNT_value_s.fnt","Lv 01");
            Valuelabel = this->m_ValueBasePowerValue;
            this->m_ValueBasePowerCost = CostLabel;
        }
            break;
        case PowerUpItemType::ShotCycle :
        {
            //連射時間
            this->m_LabelShotCycle = Sprite::create("str/label_shot_cycle.png");
            labelSprite = this->m_LabelShotCycle;
            this->m_ValueShotCycleValue = Label::createWithBMFont("str/FNT_value_s.fnt","1.50 sec");
            Valuelabel = this->m_ValueShotCycleValue;
            this->m_ValueShotCycleCost = CostLabel;
        }
            break;
        case PowerUpItemType::ChargePower :
        {
            //チャージショット最大パワー
            this->m_LabelChargePower = Sprite::create("str/label_charge_power.png");
            labelSprite = this->m_LabelChargePower;
            this->m_ValueChargePowerValue = Label::createWithBMFont("str/FNT_value_s.fnt","Lv 01");
            Valuelabel = this->m_ValueChargePowerValue;
            this->m_ValueChargePowerCost = CostLabel;
        }
            break;
        case PowerUpItemType::ChargeTime :
        {
            //チャージ時間
            this->m_LabelChargeTime = Sprite::create("str/label_charge_time.png");
            labelSprite = this->m_LabelChargeTime;
            this->m_ValueChargeTimeValue = Label::createWithBMFont("str/FNT_value_s.fnt","1.50 sec");
            Valuelabel = this->m_ValueChargeTimeValue;
            this->m_ValueChargeTimeCost = CostLabel;
        }
            break;
        case PowerUpItemType::PlayerLife :
        {
            //プレイヤーHP
            this->m_LabelPlayerLife = Sprite::create("str/label_player_life.png");
            labelSprite = this->m_LabelPlayerLife;
            this->m_ValuePlayerLifeValue = Label::createWithBMFont("str/FNT_value_s.fnt","Life 1");
            Valuelabel = this->m_ValuePlayerLifeValue;
            this->m_ValuePlayerLifeCost = CostLabel;
        }
            break;
        default:
            break;
    }
    
    //項目名
    labelSprite->setAnchorPoint(DEF_LABEL_ANCHOR);
    labelSprite->setPosition(DEF_NAME_X,DEF_NAME_Y);
    tapRect->addChild(labelSprite);
    //数値
    Valuelabel->setAnchorPoint(DEF_LABEL_ANCHOR);
    Valuelabel->setPosition(DEF_VALUE_X,DEF_LABEL_Y_LAYER_BOTTOM);
    tapRect->addChild(Valuelabel);
    //コスト
    labelSpriteCost->setPosition(DEF_COST_X,DEF_LABEL_Y_LAYER_BOTTOM + DEF_COST_Y_MARGIN);
    labelSpriteCost->setAnchorPoint(DEF_LABEL_ANCHOR);
    tapRect->addChild(labelSpriteCost);
    CostLabel->setAnchorPoint(DEF_LABEL_ANCHOR);
    CostLabel->setPosition(DEF_COST_X,DEF_LABEL_Y_LAYER_BOTTOM);
    tapRect->addChild(CostLabel);
    
    
    return ret;
}
/**
 * パワーアップメニューの選択
 */
void PowerUpScene::onPowerUpItem(cocos2d::Ref * sender)
{
    auto gd = GameData::getInstance();
    
    if(sender == this->m_MenuBasePower)
    {
        //コストチェック
        if(gd->getGamePoint() >= this->m_CostBasePower)
        {
            gd->setGamePoint(gd->getGamePoint() - this->m_CostBasePower);
            gd->setBasePower(gd->getBasePower() + gd->getAddValueBasePower());
        }
    }
    else if(sender == this->m_MenuChargePower)
    {
        //コストチェック
        if(gd->getGamePoint() >= this->m_CostChargePower)
        {
            gd->setGamePoint(gd->getGamePoint() - this->m_CostChargePower);
            gd->setChargePower(gd->getChargePower() + gd->getAddValueChargePower());
        }
    }
    else if(sender == this->m_MenuChargeTime)
    {
        //コストチェック
        if(gd->getGamePoint() >= this->m_CostChargeTime)
        {
            gd->setGamePoint(gd->getGamePoint() - this->m_CostChargeTime);
            gd->setChargeTime(gd->getChargeTime() - gd->getAddValueChargeTime());
        }
    }
    else if(sender == this->m_MenuShotCycle)
    {
        //コストチェック
        if(gd->getGamePoint() >= this->m_CostShotCycle)
        {
            gd->setGamePoint(gd->getGamePoint() - this->m_CostShotCycle);
            gd->setShotCycle(gd->getShotCycle() - gd->getAddValueShotCycle());
        }
    }
    else if(sender == this->m_MenuPlayerLife)
    {
        //コストチェック
        if(gd->getGamePoint() >= this->m_CostPlayerLife)
        {
            gd->setGamePoint(gd->getGamePoint() - this->m_CostPlayerLife);
            gd->setPlayerHp(gd->getPlayerHp() + gd->getAddValuePlayerHp());
        }
    }
    
    gd->saveSettingData();
    
    this->updateValue();
}

/**
 * メニューの数値更新
 */
void PowerUpScene::updateValue()
{
    char buff[256] = "";
    
    auto gd = GameData::getInstance();
    
    //-----------------
    //ポイント
    //-----------------
    sprintf(buff,"%12d pt",gd->getGamePoint());
    this->m_ValuePoint->setString(buff);
    
    //-----------------
    //基本パワー
    //-----------------
    sprintf(buff,"Lv %03d",gd->getBasePower());
    this->m_ValueBasePowerValue->setString(buff);
    
    if(gd->getBasePower() < gd->getMaxValueBasePower())
    {
        this->m_CostBasePower = this->calcUpValueCost(gd->getCostRateBasePower(),
                                                      gd->getBasePower(),
                                                      gd->getDefaultValueBasePower(),
                                                      gd->getAddValueBasePower());
        sprintf(buff,"%07dp",this->m_CostBasePower);
    }
    else
    {
        sprintf(buff,"Complete");
        this->m_MenuBasePower->setEnabled(false);
    }
    this->m_ValueBasePowerCost->setString(buff);
    
    //-----------------
    //連射時間
    //-----------------
    sprintf(buff,"%01.02f sec",gd->getShotCycle());
    this->m_ValueShotCycleValue->setString(buff);
    
    if(gd->getShotCycle() > gd->getMinValueShotCycle())
    {
        this->m_CostShotCycle = this->calcDownValueCost(gd->getCostRateShotCycle(),
                                                        gd->getShotCycle(),
                                                        gd->getDefaultValueShotCycle(),
                                                        gd->getAddValueShotCycle());
        sprintf(buff,"%07dp",this->m_CostShotCycle);
    }
    else
    {
        sprintf(buff,"Complete");
        this->m_MenuShotCycle->setEnabled(false);
    }
    this->m_ValueShotCycleCost->setString(buff);
    
    //-----------------
    //チャージショット最大パワー
    //-----------------
    sprintf(buff,"Lv %02d",GameData::getInstance()->getChargePower());
    this->m_ValueChargePowerValue->setString(buff);
    
    if(gd->getChargePower() < gd->getMaxValueChargePower())
    {
        this->m_CostChargePower = this->calcUpValueCost(gd->getCostRateChargePower(),
                                                        gd->getChargePower(),
                                                        gd->getDefaultValueChargePower(),
                                                        gd->getAddValueChargePower());
        sprintf(buff,"%06dp",this->m_CostChargePower);
    }
    else
    {
        sprintf(buff,"Complete");
        this->m_MenuChargePower->setEnabled(false);
    }
    this->m_ValueChargePowerCost->setString(buff);

    //-----------------
    //チャージ時間
    //-----------------
    sprintf(buff,"%1.02f sec",GameData::getInstance()->getChargeTime());
    this->m_ValueChargeTimeValue->setString(buff);
    
    if(gd->getChargeTime() > gd->getMinValueChargeTime())
    {
        this->m_CostChargeTime = this->calcDownValueCost(gd->getCostRateChargePower(),
                                                         gd->getChargeTime(),
                                                         gd->getDefaultValueChargeTime(),
                                                         gd->getAddValueChargeTime());
        sprintf(buff,"%06dp",this->m_CostChargeTime);
    }
    else
    {
        sprintf(buff,"Complete");
        this->m_MenuChargeTime->setEnabled(false);
    }
    this->m_ValueChargeTimeCost->setString(buff);
    
    //-----------------
    //プレイヤーHP
    //-----------------
    sprintf(buff,"Life %d",GameData::getInstance()->getPlayerHp());
    this->m_ValuePlayerLifeValue->setString(buff);
    
    if(gd->getPlayerHp() < gd->getMaxValuePlayerHp())
    {
        this->m_CostPlayerLife = this->calcUpValueCost(gd->getCostRatePlayerHp(),
                                                       gd->getPlayerHp(),
                                                       gd->getDefaultValuePlayerHp(),
                                                       gd->getAddValuePlayerHp());
        sprintf(buff,"%06dp",this->m_CostPlayerLife);
    }
    else
    {
        sprintf(buff,"Complete");
        this->m_MenuPlayerLife->setEnabled(false);
    }
    this->m_ValuePlayerLifeCost->setString(buff);
}

