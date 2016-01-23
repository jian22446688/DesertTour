//
//  Archery.hpp
//  DesertTour
//
//  Created by Cary on 16/1/12.
//
//

#ifndef Archery_hpp
#define Archery_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Archery : public cocos2d::Sprite
{
private:
    
    const float _speed = 50.0f;
    
    
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void setObj(Sprite* obj);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Archery);
    
    void update(float ft);
    
    /** 碰撞开始事件
     *  @2015/01/12 16:34
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
};

class Bullet : public cocos2d::Sprite
{
private:
    //速度
    float _speed = 1000.0f;
    //攻击力
    int _attack = 3264;
    
public:
    
    virtual bool init();
    
    CREATE_FUNC(Bullet);
    
    /** 碰撞开始事件
     *  @2015/01/21 10:54
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    /** 设置攻击力
     *  @2015/01/21 11:06
     */
    void setAttack(float att){
        this->_attack = att;
    }
    
    /** 获取攻击力
     *  @2015/01/21 11:06
     */
    int getAttack(){
        return this->_attack;
    }
    
};

























#endif /* Archery_hpp */
