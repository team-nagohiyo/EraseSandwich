//
//  UnityAdsWrapper.h
//  care_of_road
//
//  Created by ooharayukio on 2015/10/23.
//
//

#ifndef care_of_road_UnityAdsWrapper_h
#define care_of_road_UnityAdsWrapper_h

class UnityAdsWrapper
{
public:
    /**
     * UnityAdsの広告有無
     */
    static bool canShow();
    /**
     * UnityAdsの広告表示
     */
    static void show();
};

#endif
