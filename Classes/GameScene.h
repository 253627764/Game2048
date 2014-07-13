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
private:
    LayerColor * colorBack;
    //是否开始触摸移动
    bool m_startMoved;
    //触摸移动开始的点
    int m_x,m_y;
    bool m_sound_clear;
    //分数
    int m_score;
public:
    //定义移动的方向
    E_MOVE_DIR m_dir;
    //存放4x4区域的状态(空白或非空白)
    int map[GAME_ROWS][GAME_COLS];
    //存放所有的块
    Vector<MovedTiled *> m_allTiled;
    	
    //移动所有的块
    void moveAllTiled(E_MOVE_DIR dir);
    //产生新块
    void newMovedTiled();
    //上，下，左，右移动
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
    static Scene * createScene();
    CREATE_FUNC(Game);
    bool init();
    
};


#endif /* defined(__Game2048__GameScene__) */
