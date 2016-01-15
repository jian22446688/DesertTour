//
//  IBtnControl.hpp
//  DesertTour
//
//  Created by Cary on 15/12/28.
//
//

#ifndef IBtnControl_hpp
#define IBtnControl_hpp

#include <stdio.h>

/** 被控制按钮抽象
 *  @2015/12/28 15:41
 */
class IBtnControl {
    
public:
    
    /** 问题回答
     *  @2015/12/28 15:41
     */
    virtual void AnswerPassed(bool ispass) = 0;
    
    /** 控制的按钮是否启用
     *  @2015/12/28 15:41
     */
    virtual void IsBtnEnable(bool isbtn) = 0;
};


/** 爆炸抽象
 *  @2015/01/04 08:15
 */
class IBomb {
    
    
public:
    
  
    
    /** 问题回答
     *  @2015/01/04 09:15
     */
    virtual void PlayBomb() = 0;
};





#endif /* IBtnControl_hpp */
