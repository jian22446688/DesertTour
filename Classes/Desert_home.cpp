//
//  Desert_home.cpp
//  DesertTour
//
//  Created by Cary on 15/12/12.
//
//

#include "Desert_home.hpp"
#include "Desert_level.hpp"
#include "Desert_help.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


Scene* Desert_home::createScene()
{
    auto simpleaudio = CocosDenshion::SimpleAudioEngine::getInstance();
    
    simpleaudio->preloadBackgroundMusic("AudioAssets/audio_home/audio_bg.mp3");
    simpleaudio->preloadEffect("AudioAssets/audio_home/gone.wav");
    simpleaudio->preloadEffect("AudioAssets/audio_home/audio_adc.mp3");
    simpleaudio->preloadEffect("AudioAssets/audio_home/audio_adcka.mp3");
    simpleaudio->preloadEffect("AudioAssets/audio_home/audio_gamewin.mp3");
    simpleaudio->preloadEffect("AudioAssets/audio_home/audio_gameover.mp3");
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Desert_home::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Desert_home::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioAssets/audio_home/audio_bg.mp3",true);
    
    
    auto root_Desert_home = CSLoader::createNode("Scene/Desert_home.csb");
    this->addChild(root_Desert_home);

    Button* btn_help = root_Desert_home->getChildByName<Button*>(BTN_HOME_HELP);
    Button* btn_start = root_Desert_home->getChildByName<Button*>(BTN_HOME_START);
    btn_help->addTouchEventListener(CC_CALLBACK_2(Desert_home::onBtnOnClick, this));
    btn_start->addTouchEventListener(CC_CALLBACK_2(Desert_home::onBtnOnClick, this));
    
    
    return true;
}


void Desert_home::onBtnOnClick(Ref* reft,Widget::TouchEventType type)
{
    if (type ==Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        
        Button* btn_name = static_cast<Button*>(reft);
        
        if (btn_name->getName()==BTN_HOME_HELP)
        {
            auto scene_help = Desert_help::createScene();
            Director::getInstance()->replaceScene(scene_help);
        }
        else if (btn_name->getName()==BTN_HOME_START)
        {
            auto scene_level = Desert_level::createScene();
            Director::getInstance()->replaceScene(scene_level);
        }
    }

}












