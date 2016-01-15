//
//  Level_6.hpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#ifndef Level_6_hpp
#define Level_6_hpp

#include <stdio.h>
#include "MainUI.hpp"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Level_6 : public cocos2d::Layer
{
    
private:
    
    class MainUI* mainui;
    
    bool isAnim = true;
    
    bool ismove = true;
    
    float move_1 = -85.0f;
    float move_2 = -85.0f;
    
public:
    
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level_6);
};

#endif /* Level_6_hpp */
