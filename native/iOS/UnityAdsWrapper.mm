//
//  UnityAdsWrapper.mm
//  care_of_road
//
//  Created by ooharayukio on 2015/10/23.
//
//

#import <Foundation/Foundation.h>
#import <UnityAds/UnityAds.h>
#import "UnityAdsWrapper.h"

/**
 * UnityAdsの広告有無
 */
bool UnityAdsWrapper::canShow()
{
    if ([[UnityAds sharedInstance] canShow] && [[UnityAds sharedInstance] canShowAds]) {
        return true;
    } else {
        return false;
    }
}
/**
 * UnityAdsの広告表示
 */
void UnityAdsWrapper::show()
{
    [[UnityAds sharedInstance] show];
}
