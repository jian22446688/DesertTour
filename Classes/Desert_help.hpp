//
//  Desert_help.hpp
//  DesertTour
//
//  Created by Cary on 15/12/14.
//
//

#ifndef Desert_help_hpp
#define Desert_help_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

#define BTN_HELP_COLSE      "btn_help_colse"
#define BTN_HELP_START      "btn_help_start"


class Desert_help : public cocos2d::Layer
{
public:

    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Desert_help);
    
    void onBtnClickhelp(Ref* reft, Widget::TouchEventType type);
};


#endif /* Desert_help_hpp */
