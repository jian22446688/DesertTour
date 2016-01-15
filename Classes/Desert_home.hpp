//
//  Desert_home.hpp
//  DesertTour
//
//  Created by Cary on 15/12/12.
//
//

#ifndef Desert_home_hpp
#define Desert_home_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;


#define BTN_HOME_HELP       "btn_home_help"

#define BTN_HOME_START      "btn_home_start"


class Desert_home : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Desert_home);
    
    
    void onBtnOnClick(Ref* reft,Widget::TouchEventType type);
    
    
};


#endif /* Desert_home_hpp */
