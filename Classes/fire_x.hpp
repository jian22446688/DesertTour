//
//  fire_x.hpp
//  DesertTour
//
//  Created by Cary on 15/12/21.
//
//

#ifndef fire_x_hpp
#define fire_x_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class fire_x : public cocos2d::Layer
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init()
    {
        if (!Layer::init()) {
            return false;
        }
        auto root_fire_x = cocos2d::CSLoader::createNode("Node/animation/fire_xx.csb");
        this->addChild(root_fire_x);
        auto animx = cocos2d::CSLoader::createTimeline("Node/animation/fire_xx.csb");
        animx->gotoFrameAndPlay(0, 55, true);
        root_fire_x->runAction(animx);
        return true;
    }
    

    CREATE_FUNC(fire_x);
    
    
    void setObject(Node* object)
    {
        this->setPosition(object->getPosition());
        //设置Anchor点
        this->setAnchorPoint(cocos2d::Vec2(0,0));
        this->setScaleX(object->getScaleX());
        this->setScaleY(object->getScaleY());
        this->setRotation(object->getRotation());
        //this->setScale(object->getScale());
        object->setVisible(false);
    }
    
};


#endif /* fire_x_hpp */
