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
private:
    cocos2d::LayerColor * m_backColor;
    bool m_select;
    cocos2d::LayerColor * m_selectColor;
    pieceType m_type;
public:
    SquarePieceLayer();
    virtual ~SquarePieceLayer();
    
    CREATE_FUNC(SquarePieceLayer);
    bool init() override;

    pieceType getColorType();
    void setColorType(pieceType);
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
    
    CC_SYNTHESIZE(int, m_IndexRow, IndexRow)
    CC_SYNTHESIZE(int, m_IndexColumn, IndexColumn)
    
};
#endif /* SquarePieceLayer_hpp */
