//
//  objSpring.cpp
//  DesertTour
//
//  Created by Cary on 15/12/23.
//
//

#include "objSpring.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



// on "init" you need to initialize your instance
bool objSpring::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("AudioAssets/audio_home/audio_spring.mp3");
    
    auto tan = CSLoader::createNode("LayerUI/Other/Spring.csb");
    addChild(tan);
    auto stan = tan->getChildByName<Sprite*>("tur0001_1");
    PhysicsBody* phys = PhysicsBody::createBox(stan->getContentSize());
    phys->setTag(600001);
    //设置触发 掩码
    phys->setCategoryBitmask(0x01);
    phys->setCollisionBitmask(0x02);
    phys->setContactTestBitmask(0x01);
    phys->setDynamic(false);
    stan->setPhysicsBody(phys);
    return true;
}


/** 场景进入函数
 *  @2015/12/22 14:48
 */
void objSpring::onEnter()
{
    Layer::onEnter();
    
        auto collisionevent = EventListenerPhysicsContact::create();
        collisionevent->onContactBegin = CC_CALLBACK_1(objSpring::onCollisionBegin, this);
        collisionevent->onContactPostSolve = CC_CALLBACK_2(objSpring::onContactPostSolve, this);
        collisionevent->onContactPreSolve = CC_CALLBACK_2(objSpring::onContactPreSolve, this);
        collisionevent->onContactSeparate = CC_CALLBACK_1(objSpring::onContactSeparate, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionevent, this);
    
}

/** 设置物体
 *  @2015/12/23 13:45
 */
void objSpring::setObj(Node* obj)
{
    //设置Anchor点
    this->setName(obj->getName());
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obj->getPosition());
    this->setScaleX(obj->getScaleX());
    this->setScaleY(obj->getScaleY());
    this->setRotation(obj->getRotation());
    this->setPositionZ(obj->getPositionZ());
    obj->setVisible(false);
}


/** 碰撞开始事件
 *  @2015/12/16 11:28
 */
bool objSpring::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    log("弹簧  A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 600001)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
    }
    
    if(bodyB->getTag() == 600001)
    {
        //log("A:%d",bodyA->getTag());
        //  100001     物理世界
        //  555555     主要车的
        //  300001     悬浮的物体
        //  400001     第一关的怪物
        //  600001     弹簧的物体
        objSpring::physisBody =bodyA;
        switch (bodyA->getTag()) {
            case 555555:
                log("弹簧  车碰到了弹簧");
                objSpring::physisBody =bodyA;
                break;
            case 400001:
                objSpring::physisBody =bodyA;
                break;
                
            case 600001:
                log("弹簧的物体");
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
bool objSpring::onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
{
    
    // log("碰到了 弹簧 bbbbbbb");
    
    
    return false;
}

/** 碰撞中。。。
 *  @2015/12/16 09:40
 */
void objSpring::onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)
{
    
    
}

/** 碰撞离开
 *  @2015/12/16 09:40
 */
void objSpring::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    //log("A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 600001)
    {
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
        
    }
    
    
    
    if(bodyB->getTag() == 600001)
    {
        
        //log("A:%d",bodyA->getTag());
        //  100001     物理世界
        //  555555     主要车的
        //  300001     悬浮的物体
        //  400001     第一关的怪物
        //  600001     弹簧的物体
        
        objSpring::physisBody =nullptr;
        
        switch (bodyA->getTag()) {
            case 555555:
                objSpring::physisBody =nullptr;
                break;
            case 400001:
                objSpring::physisBody =nullptr;
                break;
                
            case 600001:
                log("弹簧的物体");
                break;
                
            default:
                break;
        }
    }
    
}



/** 添加力度
 *  @2015/12/23 13:48
 */
void objSpring::addForce(Vec2 force)
{
    auto td = CSLoader::createTimeline("LayerUI/Other/Spring.csb");
    td->gotoFrameAndPlay(0, 16, false);
    this->runAction(td);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_spring.mp3");
    if (objSpring::physisBody !=nullptr)
    {
        objSpring::physisBody->setVelocity(force);
    }
}


/** 设置需要添加力的物体
 *  @2015/12/23 15:18
 */
void objSpring::setObjForce(cocos2d::PhysicsBody* physisBody)
{
    objSpring::physisBody=physisBody;

}

/** 清除添加力的刚体
 *  @2015/12/23 15:18
 */
void objSpring::setObjClear()
{
    objSpring::physisBody = nullptr;

}




































