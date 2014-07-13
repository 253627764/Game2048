//
//  MoveTiled.h
//  Game2048
//
//  Created by luowei on 14-7-9.
//
//

#ifndef __Game2048__MovedTiled__
#define __Game2048__MovedTiled__

#include <iostream>
#include "cocos2d.h"
#include "gamedefine.h"

USING_NS_CC;

class MovedTiled:public Node{
public:
    int m_row;
    int m_col;
    int m_number;
    
    //在某个位置显示这个块
    void showAt(int r,int c);
    
    //将这个块移动到某行某列
    void moveTo(int r,int c);
    
    //翻倍
    void doubleNumber();
    
    CREATE_FUNC(MovedTiled);
    bool init();
};



#endif /* defined(__Game2048__MovedTiled__) */
