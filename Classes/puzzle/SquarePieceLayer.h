//
//  SquarePieceLayer.hpp
//  EraseSandwich
//
//  Created by 大原幸夫 on 2016/07/30.
//
//

#ifndef SquarePieceLayer_hpp
#define SquarePieceLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class SquarePieceLayer
:public cocos2d::Layer
{
private:
    cocos2d::LayerColor * m_backColor;
    bool m_select;
    cocos2d::LayerColor * m_selectColor;
public:
    enum pieceType : int
    {
        PT_RED = 0,
        PT_GREEN,
        PT_BULE,
        PT_YELLOW,
        PT_PURPLE,
        PT_BOM,
        PT_MAX
    };
    SquarePieceLayer();
    virtual ~SquarePieceLayer();
    
    CREATE_FUNC(SquarePieceLayer);
    bool init() override;
    
    void setType(pieceType);
    void setMainColor(cocos2d::Color3B color);
    void setPieceSize(cocos2d::Size size);
    
    //
    void select();
    //
    void unselect();
    
    bool isSelect();

    //
    void eraseAction();
    //
    void generateAction();
};
#endif /* SquarePieceLayer_hpp */
