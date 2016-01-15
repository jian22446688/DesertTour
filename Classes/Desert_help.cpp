//
//  Desert_help.cpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#include "Desert_help.hpp"
#include "Desert_home.hpp"
#include "Desert_level.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;





Scene* Desert_help::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Desert_help::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Desert_help::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto root_Desert_help = CSLoader::createNode("Scene/Desert_help.csb");
    
    this->addChild(root_Desert_help);

    Button* btn_colse = root_Desert_help->getChildByName<Button*>(BTN_HELP_COLSE);
    Button* btn_start = root_Desert_help->getChildByName<Button*>(BTN_HELP_START);
    
    btn_colse->addTouchEventListener(CC_CALLBACK_2(Desert_help::onBtnClickhelp, this));
    btn_start->addTouchEventListener(CC_CALLBACK_2(Desert_help::onBtnClickhelp, this));
    
    auto anim = CSLoader::createTimeline("Node/animation/fire_x.csb");
    auto animx = CSLoader::createTimeline("Node/animation/fire_xx.csb");
    
    anim->gotoFrameAndPlay(0, 55, true);
    animx->gotoFrameAndPlay(0, 55, true);
    root_Desert_help->runAction(anim);
    root_Desert_help->runAction(animx);

    
    return true;
}

void Desert_help::onBtnClickhelp(Ref* reft, Widget::TouchEventType type)
{

    if (type==Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        Button* btn_name = static_cast<Button*>(reft);
        if (btn_name->getName()==BTN_HELP_COLSE)
        {
            auto scene_home = Desert_home::createScene();
            Director::getInstance()->replaceScene(scene_home);
        }
        else if (btn_name->getName()==BTN_HELP_START)
        {
            auto scene_level = Desert_level::createScene();
            Director::getInstance()->replaceScene(scene_level);
        }
    }
}






















