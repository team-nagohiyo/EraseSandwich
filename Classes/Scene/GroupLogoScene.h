//
//  GroupLogoScene.h
//  care_of_road
//
//  Created by 大原幸夫 on 2016/01/31.
//
//

#ifndef GroupLogoScene_h
#define GroupLogoScene_h

#include <stdio.h>
#include "cocos2d.h"

class GroupLogoScene :
public cocos2d::Layer
{
public:
    
    static cocos2d::Scene * createScene();
    CREATE_FUNC(GroupLogoScene);
    virtual bool init();
    
    GroupLogoScene();
    virtual ~GroupLogoScene();
};

#endif /* GroupLogoScene_h */
