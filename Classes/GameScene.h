//
//  GameScene.h
//  Game2048
//
//  Created by luowei on 14-7-8.
//
//

#ifndef __Game2048__GameScene__
#define __Game2048__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "gamedefine.h"
#include "MovedTiled.h"

USING_NS_CC;

class Game:Layer{

public:
    static Scene * createScene();
    CREATE_FUNC(Game);
    bool init();
    
};


#endif /* defined(__Game2048__GameScene__) */
