//
//  other_level_1.hpp
//  DesertTour
//
//  Created by Cary on 15/12/22.
//
//

#ifndef other_level_1_hpp
#define other_level_1_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class other_level_1 : public cocos2d::Layer
{
private:
    Node* fu;
    
    int currentTag=0;
    
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(other_level_1);
    
    /** 设置物体
     *  @2015/12/22 19:35
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
    
    
    /** 获取一个node
     *  @2015/12/23 16:28
     */
     Node* getNo();
};


#endif /* other_level_1_hpp */
