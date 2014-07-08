//
//  SplashScene.h
//  Game2048
//
//  Created by luowei on 14-7-8.
//
//

#ifndef __Game2048__SplashScene__
#define __Game2048__SplashScene__

#include <iostream>
#include "cocos2d.h"
#include "gamedefine.h"

USING_NS_CC;


class Splash:Layer{
    bool init();
    
public:
    CREATE_FUNC(Splash);
    static Scene * createScene();
    void jumpToGame(float t);
};


#endif /* defined(__Game2048__SplashScene__) */
