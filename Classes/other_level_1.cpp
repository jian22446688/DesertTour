//
//  other_level_1.cpp
//  DesertTour
//
//  Created by Cary on 15/12/22.
//
//

#include "other_level_1.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


bool other_level_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    fu = CSLoader::createNode("LayerUI/Other/xuanfu.csb");
    addChild(fu);
    auto f = fu->getChildByName<Sprite*>("FileNode_1")->getChildByName<Sprite*>("anim_di0001_1");
    PhysicsBody* fb = PhysicsBody::createBox(Size(f->getContentSize().width/7,f->getContentSize().height));
    fb->setPositionOffset(Vec2(f->getContentSize().width/2-16, 0));
    fb->setTag(300001);
    //设置触发 掩码
    fb->setCategoryBitmask(0x01);
    //fb->setCollisionBitmask(0x01);
    fb->setContactTestBitmask(0x01);
    fb->setDynamic(false);
    f->setPhysicsBody(fb);
    auto fudong = CSLoader::createTimeline("Node/level_animation/yuan.csb");
    fudong->gotoFrameAndPlay(0, 35, true);
    fu->runAction(fudong);
    
    ParticleFlower* partic = ParticleFlower::create();
    partic->setPosition(this->getPosition());
    //partic->
    addChild(partic);
    
    return true;
}



/** 设置物体
 *  @2015/12/22 19:35
 */
void other_level_1::setObj(Node* obj)
{
    //设置Anchor点
    //this->setName(obj->getName());
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());

    obj->setVisible(false);
    
}


/** 获取一个node
 *  @2015/12/23 16:28
 */
Node* other_level_1::getNo()
{
    auto f = fu->getChildByName<Sprite*>("FileNode_1")->getChildByName<Sprite*>("anim_di0001_1");
    return f;

}



/** 场景进入函数
 *  @2015/12/22 14:48
 */
void other_level_1::onEnter()
{
    Layer::onEnter();
    
    auto collisionevent = EventListenerPhysicsContact::create();
    collisionevent->onContactBegin = CC_CALLBACK_1(other_level_1::onCollisionBegin, this);
    collisionevent->onContactPostSolve = CC_CALLBACK_2(other_level_1::onContactPostSolve, this);
    collisionevent->onContactPreSolve = CC_CALLBACK_2(other_level_1::onContactPreSolve, this);
    collisionevent->onContactSeparate = CC_CALLBACK_1(other_level_1::onContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionevent, this);
    
}


/** 碰撞开始事件
 *  @2015/12/16 11:28
 */
bool other_level_1::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    //log("A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 300001)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
        
    }
    
    if(bodyB->getTag() == 300001)
    {
        //log("A:%d",bodyA->getTag());
        //  100001     物理世界
        //  555555     主要车的
        //  300001     悬浮的物体
        //  400001     第一关的怪物
        //  600001     弹簧的物体
        switch (bodyA->getTag()) {
            case 555555:
                log("车碰到了 悬浮了。。。。。。");
                currentTag = bodyA->getTag();
                bodyA->setTag(300002);
                break;
                
            default:
                break;
        }
    }
    
    return true;
}

/** 碰撞开始事件
 *  @2015/12/16 09:40
 */
bool other_level_1::onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
{
    
    
    
    
    return false;
}

/** 碰撞中。。。
 *  @2015/12/16 09:40
 */
void other_level_1::onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)
{
    log("悬浮  被碰到了  bbbbbbb");
    
}

/** 碰撞离开
 *  @2015/12/16 09:40
 */
void other_level_1::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    //log("A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 300001)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
        
    }
    
    if(bodyB->getTag() == 300001)
    {
        //log("A:%d",bodyA->getTag());
        //  100001     物理世界
        //  555555     主要车的
        //  300001     悬浮的物体
        //  400001     第一关的怪物
        //  600001     弹簧的物体
        switch (bodyA->getTag())
        {
            case 300002:
                bodyA->setTag(currentTag);
                currentTag = 0;
                log("悬浮》  物体退出了悬浮物体");
                
                break;
            default:
                break;
        }
    }
    
}





























