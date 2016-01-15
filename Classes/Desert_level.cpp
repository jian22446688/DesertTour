//
//  Desert_home.cpp
//  DesertTour
//
//  Created by Cary on 15/12/12.
//
//

#include "Desert_level.hpp"
#include "TooslFunction.hpp"
#include "MainUI.hpp"

#include "Desert_home.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


Scene* Desert_level::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = Desert_level::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Desert_level::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto root_Desert_level = CSLoader::createNode("Scene/Desert_level.csb");
    this->addChild(root_Desert_level);
    auto anim = CSLoader::createTimeline("Node/animation/fire_x.csb");
    auto animx = CSLoader::createTimeline("Node/animation/fire_xx.csb");
    anim->gotoFrameAndPlay(0, 55, true);
    animx->gotoFrameAndPlay(0, 55, true);
    root_Desert_level->runAction(anim);
    root_Desert_level->runAction(animx);
    
    for (int i =0 ; i<10; i++)
    {
        char level[10];
        sprintf(level, "level_%d",i+1);
        auto level_ao = root_Desert_level->getChildByName<Node*>(level)->getChildByName<Button*>("btn_level");
        level_ao->addTouchEventListener(CC_CALLBACK_2(Desert_level::onBtnClickLevel, this));
        LevelSystem* ls =new LevelSystem();
        ls->btnLevel = level_ao;
        ls->initLevel();
        delete ls;
    }
    
    text_showstar = root_Desert_level->getChildByName<TextAtlas*>("txt_showstarcount");
    Button* btn_level_back = root_Desert_level->getChildByName<Button*>("btn_level_back");
    btn_level_back->addTouchEventListener(CC_CALLBACK_2(Desert_level::onBtnClickBack, this));
    
    return true;
}

void Desert_level::onEnter()
{
    Layer::onEnter();
    char showst[10];
    int starcount = ToolsFunction::CountStarNumber();
    sprintf(showst, "%d/50",starcount);
    text_showstar->setString(showst);
}

void Desert_level::onBtnClickBack(Ref* reft,Widget::TouchEventType type)
{
    if (type==Widget::TouchEventType::ENDED)
    {
        auto home_scene = Desert_home::createScene();
        Director::getInstance()->replaceScene(home_scene);
    }
}

void Desert_level::onBtnClickLevel(Ref* reft,Widget::TouchEventType type)
{
    if (type ==Widget::TouchEventType::ENDED)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/gone.wav");
        auto btn_name = dynamic_cast<Button*>(reft);
        std::string  ss = btn_name->getParent()->getName();
        //加载关卡
        ToolsFunction::LoadLevel(ss);
    }
}

/******************************卡关系统******************************/

/** 初始化关卡
 *  @2015/12/13 15:45
 */
void LevelSystem::initLevel()
{
    btnLevel->setEnabled(false);
    //吧当前的卡关的名字转换成  数字  卡关
    std::string levelname = btnLevel->getParent()->getName().c_str();
    currentLevel = std::atoi(levelname.substr(6,levelname.length()-6).c_str());
    int currentcount = ToolsFunction::CountStarNumber();
    switch (currentLevel)
    {
        case 1:
            //当前的卡关是否开启；
            isCurrentLevel = true;
            btnLevel->setEnabled(isCurrentLevel);
            break;
        case 2:
            if (currentcount >=ToolsFunction::AsbL2)
            {
                if (isCurrentLevel ==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 3:
            if (currentcount >=ToolsFunction::AsbL3)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 4:
            if (currentcount >=ToolsFunction::AsbL4)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 5:
            if (currentcount >=ToolsFunction::AsbL5)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 6:
            if (currentcount >=ToolsFunction::AsbL6)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 7:
            if (currentcount >=ToolsFunction::AsbL7)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        case 8:
            if (currentcount >=ToolsFunction::AsbL8)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
            
        case 9:
            if (currentcount >=ToolsFunction::AsbL9)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
            
        case 10:
            if (currentcount >=ToolsFunction::AsbL10)
            {
                if (isCurrentLevel==false)
                {
                    isCurrentLevel= ToolsFunction::getLevelStatus(btnLevel->getParent()->getName());
                    btnLevel->setEnabled(isCurrentLevel);
                }
            }
            break;
        default:
            break;
    }
    //得到卡关的星星数量
    star[0] = btnLevel->getParent()->getChildByName<Sprite*>("img_showstar_1");
    star[1] = btnLevel->getParent()->getChildByName<Sprite*>("img_showstar_2");
    star[2] = btnLevel->getParent()->getChildByName<Sprite*>("img_showstar_3");
    star[3] = btnLevel->getParent()->getChildByName<Sprite*>("img_showstar_4");
    star[4] = btnLevel->getParent()->getChildByName<Sprite*>("img_showstar_5");
    if (isCurrentLevel)
        //当前的卡关星星数量
        currentLevelStarNumber = ToolsFunction::getLevelStarCount(btnLevel->getParent()->getName());
    ShowStar();
}

/** 显示关卡星星
 *  @2015/12/13 15:45
 */
void LevelSystem::ShowStar()
{
    for (int i =0; i<5; i++)
    {
        star[i]->setVisible(false);
    }
    if (isCurrentLevel && currentLevelStarNumber !=0)
    {
        for (int j = 0; j<currentLevelStarNumber; j++)
        {
            star[j]->setVisible(true);
        }
    }
}

/******************************卡关系统******************************/
















