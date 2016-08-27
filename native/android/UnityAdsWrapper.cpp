//
//  UnityAdsWrapper.cpp
//  care_of_road
//
//  Created by ooharayukio on 2015/10/23.
//
//

#include "UnityAdsWrapper.h"
#include "UnityAdsJni.h"

/**
 * UnityAdsの広告有無
 */
bool UnityAdsWrapper::canShow()
{
    return canShowJni();
}
/**
 * UnityAdsの広告表示
 */
void UnityAdsWrapper::show()
{
    showJni();
}
