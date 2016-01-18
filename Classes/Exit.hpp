//
//  Exit.hpp
//  DesertTour
//
//  Created by Cary on 15/12/25.
//
//

#ifndef Exit_hpp
#define Exit_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;
using namespace cocos2d;

class Exit : public cocos2d::Sprite
{
public:
    
    //构造函数
    Exit()
    {
        
    }
    //析构函数
    ~Exit()
    {
        
        
    }
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Exit);
    
    
    void remo();
    
    void setObj(Sprite* obj)
    {
        //设置精灵贴图
        this->setTexture(obj->getTexture());
        //设置位置
        this->setPosition(obj->getPosition());
        //设置旋转
        this->setRotation(obj->getRotation());
        //设置锚点
        this->setAnchorPoint(obj->getAnchorPoint());
        //设置缩放 X
        this->setScaleX(obj->getScaleX());
        //设置缩放 Y
        this->setScaleY(obj->getScaleY());
        //设置大小
        this->setContentSize(obj->getContentSize());
        //设置物体是否可见
        this->setVisible(obj->isVisible());
        //设置物体标签
        this->setTag(obj->getTag());
        //设置斜切 X
        this->setSkewX(obj->getSkewX());
        //设置斜切 Y
        this->setSkewY(obj->getSkewY());
        //设置透明度
        this->setOpacity(obj->getOpacity());
        //设置是否翻转 X
        this->setFlippedX(obj->isFlippedX());
        //设置是否翻转 Y
        this->setFlippedY(obj->isFlippedY());
        //设置颜色
        this->setColor(obj->getColor());
        //设置资源数据
        this->setUserData(obj->getUserData());
        //销毁传进来的物体
        //obj->removeFromParent();
        cocos2d::PhysicsBody* psworld2 =cocos2d::PhysicsBody::createBox(Size(this->getContentSize().width-20 ,
                                                                             this->getContentSize().height-150));
        psworld2->setPositionOffset(Vec2(0, -50));
        //设置触发 掩码
        psworld2->setContactTestBitmask(0x01);
        psworld2->setCollisionBitmask(0x02);
        psworld2->setDynamic(false);
        psworld2->setTag(666666);
        this->setPhysicsBody(psworld2);
    }
};



























#endif /* Exit_hpp */
