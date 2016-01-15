//
//  guaiwu_js.hpp
//  DesertTour
//
//  Created by Cary on 15/12/22.
//
//

#ifndef guaiwu_js_hpp
#define guaiwu_js_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class guaiwu_js : public cocos2d::Layer
{
    
private:
    
    bool isMove = false;
    float movespeed = 0;
    ActionTimeline* guaiwu;
    cocos2d::Vec2 moveA;
    cocos2d::Vec2 moveB;
    bool iskeyr = false;
    bool iskeyl = true;
    
    class guaiwu_js* delejs;
    
    
public:

    virtual bool init();
    
    CREATE_FUNC(guaiwu_js);
    
    virtual void update(float ft);
    
    void setGuanwu(Node* obje);
    
    void setMovePosition(Node* objeA,Node* objeB,float movespeed);

    /** 怪物吃东西
     *  @2015/12/26 13:48
     */
    void setEat();

    /** 怪物吃东西完成
     *  @2015/12/26 13:48
     */
    void setEatFinish(float ft);
    
    
    
    /** 碰撞开始事件
     *  @2015/12/28 14:40
     */
    bool onCollisionBegin(const cocos2d::PhysicsContact& contact);
    
    
    /** 碰撞开始事件
     *  @2015/12/28 14:40
     */
    bool onContactPreSolve(const cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
    
    
    /** 碰撞中。。。
     *  @2015/12/28 14:40
     */
    void onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
    
    /** 碰撞离开
     *  @2015/12/28 14:40
     */
    void onContactSeparate(const cocos2d::PhysicsContact& contact);
    
    /** 僵死兴奋反向
     *  @2015/12/29 11:00
     */
    void Reverse(Node* tagpostion);
    
    /** 僵死碰到主要车死亡
     *  @2015/12/29 08:5
     */
    void killcar();
    
    /** 设置要死僵死自销毁
     *  @2015/12/30 14:25
     */
    void setDelete_js(guaiwu_js* deletejs);
    
    /** 僵死自销毁
     *  @2015/12/30 14:25
     */
    void delete_js();
    
    /** 获取怪物的当前位置
      *  @2015/01/08 15:05
      */
    cocos2d::Vec2 getCurrentPos();
    
};













#endif /* guaiwu_js_hpp */
