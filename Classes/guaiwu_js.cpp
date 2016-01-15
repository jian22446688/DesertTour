//
//  guaiwu_js.cpp
//  DesertTour
//
//  Created by Cary on 15/12/22.
//
//

#include "guaiwu_js.hpp"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



bool guaiwu_js::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto root_layer = CSLoader::createNode("LayerUI/Other/guaiwu.csb");
    addChild(root_layer);
    auto rooaby = root_layer->getChildByName<Node*>("FileNode_1")->getChildByName<Sprite*>("anim_guaiwu_zo0001_2");
    PhysicsBody* phybody = PhysicsBody::createBox(Size(rooaby->getContentSize().width-8, rooaby->getContentSize().height-20));
    phybody->setTag(400001);
    phybody->setMass(3000);
    phybody->setRotationEnable(false);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x02);
    phybody->setContactTestBitmask(0x01);
    phybody->setDynamic(true);
    rooaby->setPhysicsBody(phybody);
    guaiwu = CSLoader::createTimeline("Node/animation/guaiwujs.csb");
    guaiwu->gotoFrameAndPlay(0,35, true);
    root_layer->runAction(guaiwu);
    scheduleUpdate();
    //添加碰撞事件
    auto collisionlistener = EventListenerPhysicsContact::create();
    collisionlistener->onContactBegin =CC_CALLBACK_1(guaiwu_js::onCollisionBegin, this);
    collisionlistener->onContactSeparate = CC_CALLBACK_1(guaiwu_js::onContactSeparate,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionlistener, this);
    return true;
}

void guaiwu_js::update(float ft)
{
    
    if (isMove)
    {
        if (iskeyl)
        {
            if (this->getPositionX() > moveA.x)
            {
                this->setPositionX((this->getPositionX()-ft*guaiwu_js::movespeed));
            }else{
                iskeyl = false;
                iskeyr = true;
                this->setScaleX(-this->getScaleX());
            }
        }
        if (iskeyr)
        {
            if (this->getPositionX() <moveB.x)
            {
                
                this->setPositionX((this->getPositionX()+ft*guaiwu_js::movespeed));
            }
            else
            {
                iskeyl = true;
                iskeyr = false;
                this->setScaleX(-this->getScaleX());
            }
        }
    }
}


void guaiwu_js::setGuanwu(Node* obje)
{
    //设置Anchor点
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setPosition(obje->getPosition());
    this->setScaleX(obje->getScaleX());
    this->setScaleY(obje->getScaleY());
    this->setRotation(obje->getRotation());
    obje->setVisible(false);
}

void guaiwu_js::setMovePosition(Node* objeA,Node* objeB ,float movespeed)
{
    isMove = true;
    this->movespeed = movespeed;
    moveA =objeA->getPosition();
    moveB =objeB->getPosition();
    objeA->setVisible(false);
    objeB->setVisible(false);
    
}

/** 怪物吃东西
 *  @2015/12/26 13:48
 */
void guaiwu_js::setEat()
{
    if (isMove)
    {
        scheduleOnce(schedule_selector(guaiwu_js::setEatFinish),3.0f);
        //设置怪物 停止移动
        isMove =false;
        //切换动画吃东西
        guaiwu->gotoFrameAndPlay(40, 165, true);
        this->setScaleX(-this->getScaleX());
    }
}

/** 怪物吃东西完成
 *  @2015/12/26 13:48
 */
void guaiwu_js::setEatFinish(float ft)
{
    //回复之前的移动
    isMove =true;
    guaiwu->gotoFrameAndPlay(0,35, true);
    //怪物还原之前的状态
    this->setScaleX(-this->getScaleX());
}

/** 碰撞开始事件
 *  @2015/12/28 14:40
 */
bool guaiwu_js::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    PhysicsBody* temp =nullptr;
    log("弹簧  A:%d B:%d",bodyA->getTag(),bodyB->getTag());
    if(bodyA->getTag() == 400001){
        temp = bodyB;
        bodyB = bodyA;
        bodyA = temp;
    }
    if(bodyB->getTag() == 400001)
    {
        if (bodyA->getTag() ==400008)
        {
            //设置怪物 停止移动
            isMove =false;
            //切换动画吃东西
            this->removeFromParent();
        }
        
        if (bodyA->getTag() == 400010) {
            this->iskeyl = !this->iskeyl;
            this->iskeyr = !this->iskeyr;
            this->setScaleX(-this->getScaleX());
            log("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        }
        
        switch (bodyA->getTag()) {
            case 400006:
                if (bodyA->getNode() !=nullptr)
                {
                    bodyA->getNode()->removeFromParent();
                }
                setEat();
                break;
            case 555555:
                //僵死碰到车
                guaiwu_js::killcar();
                
                break;
                
            case 600001:
                
                break;
                
            default:
                break;
        }
    }
    
    return true;
}


/** 碰撞开始事件
 *  @2015/12/28 14:40
 */
bool guaiwu_js::onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve)
{
    
    return true;
}

/** 碰撞中。。。
 *  @2015/12/28 14:40
 */
void guaiwu_js::onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve)
{
    
    
}

/** 碰撞离开
 *  @2015/12/28 14:40
 */
void guaiwu_js::onContactSeparate(const cocos2d::PhysicsContact& contact)
{
    
    
}

/** 僵死兴奋反向
 *  @2015/12/29 11:00
 */
void guaiwu_js::Reverse(Node* tagpostion)
{
    if (!iskeyl && this->getPositionX() > tagpostion->getPosition().x)
    {
  
        this->iskeyl = !this->iskeyl;
        this->iskeyr = !this->iskeyr;
        this->setScaleX(-this->getScaleX());
        this->movespeed += 18;
    }
}


/** 僵死碰到主要车死亡
 *  @2015/12/29 08:5
 */
void guaiwu_js::killcar()
{
    //设置怪物 停止移动
    isMove =false;
    //this->getPhysicsBody()->setEnabled(false);
    this->setVisible(false);
    
}

/** 设置僵死自销毁
 *  @2015/12/30 14:25
 */
void guaiwu_js::setDelete_js(guaiwu_js* deletejs)
{
    delejs = deletejs;
}

/** 僵死自销毁
 *  @2015/12/30 14:25
 */
void guaiwu_js::delete_js()
{
    
    delejs->removeFromParent();

}


/** 获取怪物的当前位置
 *  @2015/01/08 15:05
 */
cocos2d::Vec2 guaiwu_js::getCurrentPos()
{
    return this->getPosition();
}















