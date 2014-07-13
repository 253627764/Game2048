//
//  GameOver.h
//  Game2048
//
//  Created by luowei on 14-7-13.
//
//

#ifndef __Game2048__GameOver__
#define __Game2048__GameOver__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class GameOver:Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOver);
    void menuCallBack(Ref* pObject);
};

#endif /* defined(__Game2048__GameOver__) */
