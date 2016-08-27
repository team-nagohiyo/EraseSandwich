#include "UnityAdsJni.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#define LOG_TAG    "UnityAdsJni"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"

using namespace cocos2d;

#ifdef __cplusplus
extern "C" {
#endif
	
	bool canShowJni()
	{
		
        JniMethodInfo methodInfo;
        
        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "canUnityAdsShow", "()Z"))
        {
            LOGD("Failed to find static method of canUnityAdsShow");
            return false;
		}
		
		// Android側のメソッドコール
		jboolean ans = (jboolean)methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		
        bool ret = false;
        if(JNI_TRUE == ans)ret = true;
        
        // オブジェクトの解放
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
		return ret;
	}
    
    void showJni()
    {
        
        JniMethodInfo methodInfo;
        
        if (! JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showUnityAds", "()V"))
        {
            LOGD("Failed to find static method of showUnityAds");
            return;
        }
        
        // Android側のメソッドコール
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        
        // オブジェクトの解放
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }

#ifdef __cplusplus
}
#endif