//
//  GaugeController.h
//  BULL
//
//  Created by oohara yukio on 2017/06/21.
//
//

#ifndef GaugeController_h
#define GaugeController_h

#include "cocos2d.h"

/**
 * ゲージ系を操作するクラス
 */
class GaugeController
{
public:

    //ゲージタイプ
    enum GAUGE_TYPE
    {
        GAUGE_TYPE_NONE,
        GAUGE_TYPE_VERTICAL_BOTTOM_ZERO,    //垂直(下開始)
        GAUGE_TYPE_VERTICAL_TOP_ZERO,       //垂直(上開始)
        GAUGE_TYPE_HORIZONTAL_LEFT_ZERO,    //水平(左開始)
        GAUGE_TYPE_HORIZONTAL_RIGHT_ZERO,   //水平(右開始)
    };
protected:
    GAUGE_TYPE m_type;                      //種別
    cocos2d::Size m_Size;                   //サイズ
    cocos2d::Vec2 m_defaultPos;             //初期ポジション
    cocos2d::Vec2 m_defaultAnchorPos;       //初期anchor
    
    cocos2d::Node *m_target;    //引き伸ばし
    float m_defaultScale;       //初期スケール
    cocos2d::Vec2 m_offset;     //初期値からのオフセット

    float m_value;              //現在値
    
    //ゲージのタイプ別の初期設定
    void setupType(GAUGE_TYPE type);
    
    //バーのサイズを更新する
    void updateBarRate();

public:
    //コンストラクタ
    GaugeController();
    //デストラクタ
    virtual ~GaugeController();
    
    //コントロール対象の設定
    void setControlNode(cocos2d::Node* ref);

    //レートの設定
    void setRate(float value);
    
    //タイプ
    void setType(GAUGE_TYPE type);

};

#endif /* GaugeController_h */
