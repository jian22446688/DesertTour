//
//  Level_5.hpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#ifndef Level_5_hpp
#define Level_5_hpp

#include <stdio.h>
#include "MainUI.hpp"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Level_5 : public cocos2d::Layer
{
    
    
private:
    
    class MainUI* mainui;
    
    Node* anim_l5_2;
    ActionTimeline* anim;
    
    bool iskill = true;
    bool ismove = true;
public:
    
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    /** 场景更新函数
     *  @2015/01/11 11:30
     */
    virtual void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level_5);
};

#endif /* Level_5_hpp */
