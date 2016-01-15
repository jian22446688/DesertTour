//
//  Exit.cpp
//  DesertTour
//
//  Created by Cary on 15/12/25.
//
//

#include "Exit.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

// on "init" you need to initialize your instance
bool Exit::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
       return true;
}


bool CarChangePosition::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setContentSize(Size(50.0f,50.0f));
    PhysicsBody* _phy = PhysicsBody::createBox(this->getContentSize());
    _phy->setTag(PHY_TAG_CARCHANGEPOS);
    //设置触发 掩码
    _phy->setCategoryBitmask(0x01);
    _phy->setCollisionBitmask(0x02);
    _phy->setContactTestBitmask(0x01);
    _phy->setDynamic(false);
    this->setPhysicsBody(_phy);
    auto _conlisionEvent = EventListenerPhysicsContact::create();
    _conlisionEvent->onContactBegin = CC_CALLBACK_1(CarChangePosition::onCollisionBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_conlisionEvent, this);
    return true;
}



/** 车变换位置
 *  @2015/01/14 10:22
 */
void CarChangePosition::setObj(Node* obj)
{
    this->setPosition(obj->getPosition());
    obj->setVisible(false);
}

/** 设置车和车的位置
 *  @2015/01/14 10:22
 */
void CarChangePosition::setChangePosition(MainCar_R* car_r, Node* obj)
{
    this->_car_r = car_r;
    this->_pos = obj;
}

/** 碰撞进入事件
 *  @2015/01/14 10:22
 */
bool CarChangePosition::onCollisionBegin(const cocos2d::PhysicsContact& contace)
{
    PhysicsBody* bodyA = contace.getShapeA()->getBody();
    PhysicsBody* bodyB = contace.getShapeB()->getBody();
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        if (bodyA->getTag() == PHY_TAG_MAINCAR || bodyB->getTag() == PHY_TAG_MAINCAR) {
            log("Ggggggggggggggggg");
            //this->_car_r->setObj(_pos);
            if (this->_cbk) {
                this->_cbk();
            }
        }
    }
    return true;
}

/** 碰撞进入回调事件
 *  @2015/01/14 11:22
 */
void CarChangePosition::addEvent(const cllback& clbak)
{
    this->_cbk = clbak;
}

























