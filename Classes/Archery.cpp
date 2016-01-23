//
//  Archery.cpp
//  DesertTour
//
//  Created by Cary on 16/1/12.
//
//

#include "Archery.hpp"


#include "MainUI.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;



bool Archery::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setTexture("DesertUI/Level/level_6/ar.png");
    
    PhysicsBody* phybody = PhysicsBody::createBox(Size(this->getContentSize().width-4,this->getContentSize().height-4));
    phybody->setTag(PHY_TAG_ARCHERY_L5);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x01);
    phybody->setContactTestBitmask(0x01);
    this->setPhysicsBody(phybody);
    phybody->setGravityEnable(false);
    auto oncollsiionevent = EventListenerPhysicsContact::create();
    oncollsiionevent->onContactBegin = CC_CALLBACK_1(Archery::onCollisionBegin, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oncollsiionevent, this);
    phybody->setVelocity(Vec2(-500.0f,0.0f));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_adc.mp3");
    
    return true;
}


void Archery::update(float ft)
{
    this->setPositionX(this->getPositionX() + _speed * ft * this->getScaleX());
    
}

void Archery::setObj(Sprite* obj)
{
    //this->setTexture(obj->getTexture());
}


/** 碰撞开始事件
 *  @2015/01/12 16:34
 */
bool Archery::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_adcka.mp3");
        ParticleSystemQuad* par = ParticleSystemQuad::create("Effect/archEffect.plist");
        par->setPosition(Vec2(this->getPositionX()-30, this->getPositionY()));
        this->getParent()->addChild(par);
        this->removeFromParent();
    }
    return true;
}


bool Bullet::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setTexture("DesertUI/Level/level_9/bell.png");
    //this->setContentSize(Size(16.0f,16.0f));
    PhysicsBody* phybody = PhysicsBody::createCircle(this->getContentSize().width / 2);
    phybody->setTag(PHY_TAG_ARCHERY_L5);
    phybody->setCategoryBitmask(0x01);
    phybody->setCollisionBitmask(0x02);
    phybody->setContactTestBitmask(0x01);
    this->setPhysicsBody(phybody);
    phybody->setGravityEnable(false);
    auto oncollsiionevent = EventListenerPhysicsContact::create();
    oncollsiionevent->onContactBegin = CC_CALLBACK_1(Bullet::onCollisionBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oncollsiionevent, this);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_adc.mp3");
    
    return true;
}

/** 碰撞开始事件
 *  @2015/01/12 16:34
 */
bool Bullet::onCollisionBegin(const cocos2d::PhysicsContact& contact)
{
    PhysicsBody* bodyA = contact.getShapeA()->getBody();
    PhysicsBody* bodyB = contact.getShapeB()->getBody();
    
    PhysicsBody* body = this->getPhysicsBody();
    if(body == bodyA || body == bodyB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("AudioAssets/audio_home/audio_adcka.mp3");
        ParticleSystemQuad* par = ParticleSystemQuad::create("Effect/archEffect.plist");
        par->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
        this->getParent()->addChild(par);
        schedule([=](float ft)
                 {
                    this->removeFromParent();
                 }, 1 / 60, "a");
    }
    return true;
}






















