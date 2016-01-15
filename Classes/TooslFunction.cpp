//
//  TooslFunction.cpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#include "TooslFunction.hpp"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;





/** 设置精灵成刚体
 *  @2015/12/18 19:05
 */
void ToolsFunction::setPhySpriteBox(cocos2d::Sprite* spritephy)
{
    PhysicsBody* physprite = PhysicsBody::createBox(spritephy->getContentSize());
    physprite->setDynamic(false);
    
    spritephy->setPhysicsBody(physprite);
}


/** 设置静态 可碰撞 精灵成刚体
 *  @2015/12/21 09:15
 */
void ToolsFunction::setPhyDynamicSpriteBox(cocos2d::Sprite* spritephy)
{
    PhysicsBody* physprite = PhysicsBody::createBox(spritephy->getContentSize());
    physprite->setDynamic(false);
    spritephy->setPhysicsBody(physprite);
}


/** 设置静态 和车 触发事件的 精灵成刚体
 *  @2015/12/21 09:15
 */
void ToolsFunction::setPhyContactSpriteBox(cocos2d::Sprite* spritephy)
{
    PhysicsBody* psworld2 =PhysicsBody::createBox(spritephy->getContentSize());
    
    //设置触发 掩码
    psworld2->setContactTestBitmask(0x01);
    psworld2->setCollisionBitmask(0x02);
    psworld2->setDynamic(false);
    spritephy->setPhysicsBody(psworld2);
}


/** 设置静态 障碍 触发事件的 精灵成刚体
 *  @2015/12/21 09:15
 */
void ToolsFunction::setPhyContactBarrBox(cocos2d::Sprite* spritephy)
{
    PhysicsBody* psworld2 =PhysicsBody::createBox(spritephy->getContentSize());
    psworld2->setTag(PHY_TAG_BARRIER);
    //设置触发 掩码
    psworld2->setContactTestBitmask(0x01);
    psworld2->setCollisionBitmask(0x02);
    psworld2->setDynamic(false);
    spritephy->setPhysicsBody(psworld2);

}


/** 设置静态 和车 碰撞事件的 精灵成刚体
 *  @2015/12/21 09:15
 */
void ToolsFunction::setPhyCollisionSpriteBox(cocos2d::Sprite* spritephy)
{
    PhysicsBody* psworld =PhysicsBody::createBox(Size(spritephy->getContentSize().width-1 , spritephy->getContentSize().height-1));
    
    psworld->setCategoryBitmask(0x01);
    psworld->setCollisionBitmask(0x01);
    psworld->setContactTestBitmask(0x01);
    spritephy->setPhysicsBody(psworld);
}


/** 设置保存关卡的星星数量
 *  @2015/12/14 16:35
 */
void ToolsFunction::setSaveStar(std::string keynma,int starNumber)
{
    log("保存 %s ,%d",keynma.c_str(),starNumber);
    
    if (starNumber > getLevelStarCount(keynma))
    {
        auto userdefault = UserDefault::getInstance();
        char starnamber[80];
        sprintf(starnamber, "levelStarsm_%s",keynma.c_str());
        //设置单个卡关的星星数量
        userdefault->setIntegerForKey(starnamber, starNumber);
        //userdefault->flush();
        //全部星星统计
        userdefault->setIntegerForKey("allStarCountsm", (ToolsFunction::CountStarNumber()+starNumber));
        //userdefault->flush();
        //消除这个单例
        userdefault->destroyInstance();
    }
}

/** 设置卡关是否开启的状态
 *  @2015/12/14 16:35
 */
void ToolsFunction::setSavebool(std::string boolname,bool islevel)
{
    auto userdefault = UserDefault::getInstance();
    char isLevela[20];
    sprintf(isLevela,"isLevelsm_%s",boolname.c_str());
    userdefault->setBoolForKey(isLevela, islevel);
    userdefault->flush();
    
    //消除这个单例
    userdefault->destroyInstance();
    
}


/** 获取卡关开关状态
 *  @2015/12/14 16:35
 */
bool ToolsFunction::getLevelStatus(std::string levelname)
{
    //获取存数据的单例
    auto userdefault = UserDefault::getInstance();
    char isLevel[20];
    sprintf(isLevel,"isLevelsm_%s",levelname.c_str());
    //userdefault->setBoolForKey(stringandstd, isLevel);
    bool currentlevel = userdefault->getBoolForKey(isLevel);
    userdefault->flush();
    //消除这个单例
    userdefault->destroyInstance();
    
    return currentlevel;
}

/** 获取卡关的星星数量
 *  @2015/12/14 16:35
 */
int ToolsFunction::getLevelStarCount(std::string levelname)
{
    auto userdefault = UserDefault::getInstance();
    
    char starnumber[20];
    sprintf(starnumber,"levelStarsm_%s",levelname.c_str());
    
    //设置单个卡关的星星数量
    int starcount = userdefault->getIntegerForKey(starnumber);
    userdefault->flush();
    
    //消除这个单例
    userdefault->destroyInstance();
    return starcount;
}

/** 统计所有的星星数量
 *  @2015/12/14 16:35
 */
int ToolsFunction::CountStarNumber()
{
    int curren = 0;
    auto userdefault = UserDefault::getInstance();
    for (int i =1; i<11; i++)
    {
        char starnumber[28];
        sprintf(starnumber,"levelStarsm_level_%d",i);
        //获取全部星星数量
        int count = userdefault->getIntegerForKey(starnumber);
        curren = curren + count;
    }
    //    //获取全部星星数量
    //    int count = userdefault->getIntegerForKey("allStarCountsm");
    userdefault->flush();
    //消除这个单例
    userdefault->destroyInstance();
    return curren;
    
}


/** 向前播放 Tween 动作
 *  @2015/12/21 09:55
 */
void ToolsFunction::TweenForword(cocos2d::Node* tweenobject, const cocos2d::Vec2 tweenpos)
{
    MoveTo* mt = MoveTo::create(0.8f, tweenpos);
    tweenobject->runAction(mt);
}


/** 向后播放twwen 动作
 *  @2015/12/21 09:55
 */
void ToolsFunction::TweenReverse(cocos2d::Node* tweenobject, const cocos2d::Vec2 tweenpos)
{
    MoveTo* mt = MoveTo::create(0.8f, tweenpos);
    tweenobject->runAction(mt);
}


/** 进入关卡 根据数字加载关卡
 *  @2015/12/28 17:16
 */
void ToolsFunction::LoadLevel(std::string levelnumber)
{
    //移除所有的事件侦听
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
    int level = std::atoi(levelnumber.substr(6,levelnumber.length()-1).c_str());
    auto replacescene = Director::getInstance();
    if (level==1)
    {
        auto level = Level_1::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==2){
        auto level = Level_2::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==3){
        auto level = Level_3::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==4){
        auto level = Level_4::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==5){
        auto level = Level_5::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==6){
        auto level = Level_6::createScene();
        replacescene->replaceScene(level);
    }else if(level==7){
        auto level = Level_7::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==8){
        auto level = Level_8::createScene();
        replacescene->replaceScene(level);
    }else if(level==9){
        auto level = Level_9::createScene();
        replacescene->replaceScene(level);
    }
    else if(level==10){
        auto level = Level_10::createScene();
        replacescene->replaceScene(level);
    }
}




































































































