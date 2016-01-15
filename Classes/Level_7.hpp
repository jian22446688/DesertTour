//
//  Level_7.hpp
//  DesertTour
//
//  Created by Cary on 15/12/26.
//
//

#ifndef Level_7_hpp
#define Level_7_hpp

#include <stdio.h>
#include "MainUI.hpp"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


class Level_7 : public cocos2d::Layer
{
    
private:
    
    class MainUI* mainui;
    
public:
    
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level_7);
};

#endif /* Level_7_hpp */
