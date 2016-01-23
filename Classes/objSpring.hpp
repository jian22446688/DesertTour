//
//  objSpring.hpp
//  DesertTour
//
//  Created by Cary on 15/12/23.
//
//

#ifndef objSpring_hpp
#define objSpring_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class objSpring : public cocos2d::Layer
{
    
private:
    
    cocos2d::PhysicsBody* physisBody = nullptr;
    
    cocos2d::Sprite* stan;
    
    int _phytag;
    
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(objSpring);
    
    /** 设置物体
     *  @2015/12/23 13:45
     */
    void setObj(Node* obj);
    
    /** 场景进入函数
     *  @2015/12/22 14:48
     */
    virtual void onEnter();
    
    /** 碰撞开始事件
     *  @2015/12/16 11:28
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    /** 碰撞开始事件
     *  @2015/12/16 09:40
     */
    bool onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
    
    
    /** 碰撞中。。。
     *  @2015/12/16 09:40
     */
    void onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
    
    /** 碰撞离开
     *  @2015/12/16 09:40
     */
    void onContactSeparate(const cocos2d::PhysicsContact& contact);
    
    
    
    /** 添加力度 默认是 0，2000
     *  @2015/12/23 13:48
     */
    void addForce(cocos2d::Vec2 force = cocos2d::Vec2(0, 1500));
    
    /** 设置需要添加力的物体
     *  @2015/12/23 15:18
     */
    void setObjForce(cocos2d::PhysicsBody* obje);
    
    /** 清除添加力的刚体
     *  @2015/12/23 15:18
     */
    void setObjClear();
    
    /** 设置刚体的属性
     *  @2015/01/19 11:55
     */
    void setPhysicsTag(int tag);
  
    
    
};


#endif /* objSpring_hpp */
