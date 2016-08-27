#include "AppDelegate.h"
#include "TitleScene.h"

#include "GroupLogoScene.h"

//#include "AppCCloudPlugin.h"
//#define MEDIA_KEY "7f6de7b004dc223856907051e3727d67e1b947be"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
//    // appC cloud 開始
//    bool startResult = AppCCloudPlugin::setMK_iOS(MEDIA_KEY).start();
//    if(startResult){
//        CCLOG("start() succeeded");
//    }else{
//        CCLOG("start() failed");
//    }
//    startResult = AppCCloudPlugin::setOptions(API_GAMERS).setMK_iOS(MEDIA_KEY).start();
//    if(startResult){
//        CCLOG("start() succeeded");
//    }else{
//        CCLOG("start() failed");
//    }
    
    //プラットフォーム別の設定
    Application::Platform platform = Application::getInstance()->getTargetPlatform();
    switch (platform) {
        case cocos2d::Application::Platform::OS_IPAD:
            if(glview->getFrameSize().width < glview->getFrameSize().height)
            {
                glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
            }
            else
            {
                glview->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
            }
            break;
            
        case cocos2d::Application::Platform::OS_ANDROID:
        case cocos2d::Application::Platform::OS_IPHONE:
        {
            bool isLong = this->isLongScreen(glview->getFrameSize().width,glview->getFrameSize().height);
            if(glview->getFrameSize().width < glview->getFrameSize().height)
            {
                
                if(isLong)
                {
                    glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
                }
                else
                {
                    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
                }
            }
            else
            {
                if(isLong)
                {
                    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
                }
                else
                {
                    glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
                }
            }
        }
        default:
            glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
            break;
    }
    

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto scene = TitleScene::createScene();
#else
    auto scene = GroupLogoScene::createScene();
#endif

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

bool AppDelegate::isLongScreen(float w , float h)
{
    float longSize;
    float shortSize;
    if(w < h)
    {
        longSize = h;
        shortSize = w;
    }
    else
    {
        longSize = w;
        shortSize = h;
    }
    
    return (longSize / shortSize) > 1.6f;
}
