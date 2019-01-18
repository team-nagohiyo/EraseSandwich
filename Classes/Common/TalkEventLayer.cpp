//
//  TalkEventLayer.cpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2019/01/14.
//

#include "TalkEventLayer.hpp"

USING_NS_CC;

TalkEventLayer::TalkEventLayer()
:_touchLayerListener(nullptr)
,_isTouch(false)
{
    
}


TalkEventLayer::~TalkEventLayer()
{
    
}

TalkEventLayer* TalkEventLayer::create()
{
    TalkEventLayer* ret = new (std::nothrow) TalkEventLayer();
    if(ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}


bool TalkEventLayer::init()
{
    if(!cocos2d::Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    setTouchCallback(listener);
    listener->onTouchBegan = CC_CALLBACK_2(TalkEventLayer::callbackTouchBegin,this);
    listener->onTouchMoved = CC_CALLBACK_2(TalkEventLayer::callbackTouchMove,this);
    listener->onTouchEnded = CC_CALLBACK_2(TalkEventLayer::callbackTouchEnd,this);
    listener->onTouchCancelled = CC_CALLBACK_2(TalkEventLayer::callbackTouchCancel,this);

    return true;
}


void TalkEventLayer::setupForBinaryFile(const std::string& path)
{
    
}


void TalkEventLayer::update(float dt)
{
    
}


void TalkEventLayer::play()
{
    
}

void TalkEventLayer::stop()
{
    
}

void TalkEventLayer::pause()
{
    
}

void TalkEventLayer::resume()
{
    
}

void TalkEventLayer::next()
{
    
}



void TalkEventLayer::setEventCallback(std::function<void(std::string tag,std::string command)>func)
{
    _eventCallback = func;
}


void TalkEventLayer::setTouchCallback(cocos2d::EventListenerTouchOneByOne* touch)
{
    CC_SAFE_RELEASE_NULL(_touchLayerListener);
    _touchLayerListener = touch;
    if(_touchLayerListener)
    {
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchLayerListener, this);
    }
    CC_SAFE_RETAIN(_touchLayerListener);
    _isTouch = !(touch)? true : false;  //nullならfalse
}

void TalkEventLayer::setEnable(bool enable)
{
    if(_touchListener)
    {
        _isTouch = enable;
    }
}

bool TalkEventLayer::isEnable()
{
    return _isTouch;
}


bool TalkEventLayer::callbackTouchBegin(cocos2d::Touch*, cocos2d::Event*)
{
    return true;
}

void TalkEventLayer::callbackTouchMove(cocos2d::Touch*, cocos2d::Event*)
{
    
}

void TalkEventLayer::callbackTouchEnd(cocos2d::Touch*, cocos2d::Event*)
{
    
}

void TalkEventLayer::callbackTouchCancel(cocos2d::Touch*, cocos2d::Event*)
{
    
}
