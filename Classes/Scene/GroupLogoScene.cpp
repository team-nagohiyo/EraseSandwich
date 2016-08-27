//
//  GroupLogoScene.cpp
//  care_of_road
//
//  Created by 大原幸夫 on 2016/01/31.
//
//

#include "GroupLogoScene.h"
#include "TitleScene.h"

USING_NS_CC;

cocos2d::Scene * GroupLogoScene::createScene()
{
    auto scene = cocos2d::Scene::create();
    GroupLogoScene *layer = GroupLogoScene::create();
    if(scene)scene->addChild(layer);
    return scene;
}

GroupLogoScene::GroupLogoScene()
{
    
}
GroupLogoScene::~GroupLogoScene()
{
    
}
bool GroupLogoScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto back =  LayerColor::create(Color4B::WHITE);
    this->addChild(back,0);
    back->setPosition(Vec2::ZERO);
    
    cocos2d::Vec2 pos = Director::getInstance()->getWinSize() * 0.5f;
    
    auto iconSprite = Sprite::create("icon/nagohiyo_mark_4.png");
    
    this->addChild(iconSprite,1);
    iconSprite->setScale(0.5f);
    iconSprite->setPosition(pos);

    Vector<FiniteTimeAction*> actions;
    
    actions.pushBack(DelayTime::create(2.0f));
    actions.pushBack(CallFunc::create([=](){
        Director::getInstance()->replaceScene(TitleScene::createScene());
                                      })
                     );
    
    this->runAction(Sequence::create(actions));
    
    return true;
}

