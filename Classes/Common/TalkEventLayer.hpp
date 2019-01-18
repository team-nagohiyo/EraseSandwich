//
//  TalkEventLayer.hpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2019/01/14.
//

#ifndef TalkEventLayer_hpp
#define TalkEventLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

enum TalkEventDataType : unsigned char
{
    talkMessage = 10,               //メッセージの表示
    CharaFadeIn = 20,               //キャラクタの挿入
    CharaFadeOut = 21,              //キャラクタの破棄
    CharaChangePosition = 22,       //キャラクタの配置換え
    CharaShake = 23,                //キャラクタを揺らす
    BackgroundFadeIn = 50,          //背景の挿入
    BackgroundFadeOut = 51,         //背景の破棄
    BackgroundFadeInOut = 52,       //背景の切り替え
};

/**
 * 会話イベントのデータ
 */
struct TalkEventData
{
    TalkEventDataType _type;    //データの種別
    std::uint32_t length;       //データサイズ
    unsigned char* _data;       //データ
};

/**
 * 会話アニメーションを再生するレイヤー
 */
class TalkEventLayer : public cocos2d::Layer
{
protected:
    enum TalkPlayAction : int
    {
        Wait,
        Play,
        NextWait,
        
    };
    TalkPlayAction _action;
    bool _isTouch;
    std::function<void(std::string tag,std::string command)> _eventCallback;
public:
    TalkEventLayer();
    virtual ~TalkEventLayer();
    static TalkEventLayer* create();
    virtual bool init();
    void setupForBinaryFile(const std::string& path);
    
    //更新処理
    virtual void update(float dt);
    
    virtual void play();    //再生
    virtual void stop();    //停止
    virtual void pause();   //一時停止
    virtual void resume();  //再開
    virtual void next();    //次のメッセージ
    
    
    //会話データに埋め込まれたコールバック
    void setEventCallback(std::function<void(std::string tag,std::string command)>func);
    
    virtual void setTouchCallback(cocos2d::EventListenerTouchOneByOne* touch);
    virtual void setEnable(bool enable);
    virtual bool isEnable();

protected:
    cocos2d::EventListenerTouchOneByOne* _touchLayerListener;
    virtual bool callbackTouchBegin(cocos2d::Touch*, cocos2d::Event*);
    virtual void callbackTouchMove(cocos2d::Touch*, cocos2d::Event*);
    virtual void callbackTouchEnd(cocos2d::Touch*, cocos2d::Event*);
    virtual void callbackTouchCancel(cocos2d::Touch*, cocos2d::Event*);
    
};

#endif /* TalkEventLayer_hpp */
