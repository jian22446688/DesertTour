//
//  Level_1.hpp
//  DesertTour
//
//  Created by Cary on 15/12/15.
//
//

#ifndef Level_1_hpp
#define Level_1_hpp

#include <stdio.h>
#include "MainUI.hpp"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Level_1 : public cocos2d::Layer
{
    
    
private:
    
    class MainUI* mainui;
    
    class SpriteTweenBase* dh1;
    
    bool ismove = true;
    cocos2d::Vec2 movepo;
    
    class objSpring* os;
    
    
    class other_level_1* xd1;
    class other_level_1* xd2;
    bool iscarfukong = false;
    
    
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    
    CREATE_FUNC(Level_1);
    
    
    /** 场景进入函数
     *  @2015/12/16 09:40
     */
    virtual void onEnter();
    
    /** 场景更新函数
     *  @2015/12/16 09:40
     */
    virtual void update(float dt);
    
    /** 给问题按钮设置 需要控制的物体
     *  @2015/12/18 19:40
     */
    void onBtnClick(Ref* reft,Widget::TouchEventType type);
    
    
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
    
    
    
};









#endif /* Level_1_hpp */
