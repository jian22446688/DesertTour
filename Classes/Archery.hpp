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

#endif /* Archery_hpp */
