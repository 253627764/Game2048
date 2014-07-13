//
//  GameScene.cpp
//  Game2048
//
//  Created by luowei on 14-7-8.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene * Game::createScene(){
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init(){
    if(!Layer::init()){
        return false;
    }
    
    //初始化游戏标题
    auto labelGame=Label::createWithBMFont("futura-48.fnt","2048");
    labelGame->setScale(2);
    labelGame->setPosition(Point(labelGame->getContentSize().width,GAME_SCREEN_HEIGH-labelGame->getContentSize().height));
    this->addChild(labelGame);
    
    //初始化游戏网格
    int tiledMapWidth = GAME_TILED_WIDTH*GAME_COLS+GAME_TILED_BOARD_WIDTH*(GAME_COLS+1);
    int tiledMapHeight = GAME_TILED_HEIGHT*GAME_ROWS+GAME_TILED_BOARD_WIDTH*(GAME_ROWS+1);
    colorBack = LayerColor::create(Color4B(170,170,170,255),tiledMapWidth , tiledMapHeight);
    //    colorBack->setAnchorPoint(Point(colorBack->getContentSize().width/2,colorBack->getContentSize().height/2));
    colorBack->setPosition(Point((GAME_SCREEN_WIDTH-tiledMapWidth)/2,(GAME_SCREEN_HEIGH-tiledMapHeight)/2));
    this->addChild(colorBack);
    
    //初始化网格中的每一块
    for(int row=0;row < GAME_ROWS;row++){
        for (int col=0; col < GAME_COLS; col++) {
            auto layerTiled = LayerColor::create(Color4B(70,70,70,255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
            layerTiled->setPosition(Point(GAME_TILED_WIDTH*col+GAME_TILED_BOARD_WIDTH*(col+1),GAME_TILED_HEIGHT*row+GAME_TILED_BOARD_WIDTH*(row+1)));
            colorBack->addChild(layerTiled);
        }
    }
    
    //初始化逻辑的网格数组
    for(int i=0;i<GAME_ROWS;i++){
        for(int j=0;j<GAME_COLS;j++){
            map[i][j] = 0;//空白
        }
    }
    
    
    //初始化数字块
    newMovedTiled();
    
    
    //触摸处理
    auto event = EventListenerTouchOneByOne::create();
    event->onTouchBegan=[&](Touch * tou,Event *eve){
        m_x = tou->getLocation().x;
        m_y = tou->getLocation().y;
        m_startMoved = false;
        return true;
    };
    event->onTouchMoved=[&](Touch * tou,Event *eve){
        int x = tou->getLocation().x;
        int y = tou->getLocation().y;
        
        //移动10像素才计入移动
        if(!m_startMoved && (abs(m_x -x) > 10 || abs(m_y-y) > 10) ){
            m_startMoved = true;
            
            //判断方向
            E_MOVE_DIR dir;
            if(abs(m_x-x)>abs(m_y-y)){
                if(m_x < x){
                    dir = E_MOVE_DIR::RIGHT;
                }else{
                    dir = E_MOVE_DIR::LEFT;
                }
            }else{
                if(m_y < y){
                    dir = E_MOVE_DIR::UP;
                }else{
                    dir = E_MOVE_DIR::DOWN;
                }
            }
            //移动所有的元素块
            moveAllTiled(dir);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
    
    //分数
    
    
    return true;
}

void Game::moveAllTiled(E_MOVE_DIR dir){
    m_sound_clear=false;
    //移动所有块，消除
    switch(dir){
        case E_MOVE_DIR::UP:
            moveUp();
            break;
        case E_MOVE_DIR::DOWN:
            moveDown();
            break;
        case E_MOVE_DIR::LEFT:
            moveLeft();
            break;
        case E_MOVE_DIR::RIGHT:
            moveRight();
            break;
        default:
            break;
    }
    

    //播放音乐
    if(m_sound_clear)
    {
        SimpleAudioEngine::getInstance()->playEffect("moveClear.wav");
    }else
    {
        SimpleAudioEngine::getInstance()->playEffect("move1.wav");
    }
    
    //判断输赢
    
    //产生新块
    newMovedTiled();
    
}

//产生新块
void Game::newMovedTiled(){
    auto tiled = MovedTiled::create();
    
    //在空白位置产生块
    int freeCount = 16-m_allTiled.size();
    //没有空白区域
    if(freeCount == 0){
        return;
    }
    //随机产生一个位置数
    int num = rand()%freeCount;

    int count = 0;
    int row = 0;
    int col = 0;
    bool find = false;
    for(;row < GAME_ROWS;row++){
        for(col = 0;col<GAME_COLS;col++){
            //说明这一位置是空白区域
            if(map[row][col]==0){
                count ++; //记录空白的数量
                if(count>=num){
                    find = true;
                    break;
                }
            }
        }
        if(find){
            break;
        }
    }
    
    //添加到colorBack
    colorBack->addChild(tiled);
    //位置数转换成区块坐标
//    tiled->moveTo(num/GAME_ROWS,num%GAME_COLS);
//    tiled->moveTo(row, col);
    tiled->showAt(row, col);
    
    //将新产生的块保存到vector
    m_allTiled.pushBack(tiled);
    //修改新块所在区块坐标的状态值
//    map[num/GAME_ROWS][num%GAME_COLS]=m_allTiled.getIndex(tiled)+1;
    map[row][col]=m_allTiled.getIndex(tiled)+1;
}

void Game::moveUp(){
    for(int col=0;col < GAME_COLS;col++){
        //向上移动，先从最上方第4行开始移动(cocos2d中左下角为原点)
        for(int row=GAME_ROWS-1;row>=0;row--){
            
            //如果当前块不是空白块->移动
            if(map[row][col] > 0){
                //移动当前行
                for(int row1=row;row1<GAME_ROWS-1;row1++){
                    //判断它上方是否为0,是0就移上去
                    if(map[row1+1][col]==0){
                        map[row1+1][col]=map[row1][col];
                        map[row1][col]=0;
                        m_allTiled.at(map[row1+1][col]-1)->moveTo(row1+1, col);
                    }else{
                        //判断是否有可以消除的块,取出前方那一块的数值
                        int numObj = m_allTiled.at(map[row1+1][col]-1)->m_number;
                        //取出当前块的值
                        int rowNum = m_allTiled.at(map[row1][col]-1)->m_number;
                        if(numObj == rowNum){
                            m_sound_clear=true;
                            m_allTiled.at(map[row1+1][col]-1)->doubleNumber();
                            m_allTiled.at(map[row1][col]-1)->removeFromParent();
                            
                            //取得当前要消除块在map中的标号
                            int index = map[row1][col];
                            m_allTiled.erase(map[row1][col]-1);
                            //把map中标号大于当前块的减1
                            for(int r=0;r<GAME_ROWS;r++){
                                for(int c=0;c<GAME_COLS;c++){
                                    if(map[r][c]>index){
                                        map[r][c]--;
                                    }
                                }
                            }
                            map[row1][col] = 0;
                        }
                        break;
                    }
                }
            
            }
            
        }
    }
    
    //消除最前面的
    
}

void Game::moveDown(){
    for(int col=0;col < GAME_COLS;col++){
        //向上移动，先从最上方第4行开始移动(cocos2d中左下角为原点)
        for(int row=0;row < GAME_ROWS;row++){
            
            //如果当前块不是空白块->移动
            if(map[row][col] > 0){
                //移动当前行
                for(int row1=row;row1>0;row1--){
                    //判断它下方是否为0,是0就移下去
                    if(map[row1-1][col]==0){
                        map[row1-1][col]=map[row1][col];
                        map[row1][col]=0;
                        m_allTiled.at(map[row1-1][col]-1)->moveTo(row1-1, col);
                    }else{
                        //判断是否有可以消除的块,取出前方那一块的数值
                        int numObj = m_allTiled.at(map[row1-1][col]-1)->m_number;
                        //取出当前块的值
                        int rowNum = m_allTiled.at(map[row1][col]-1)->m_number;
                        if(numObj == rowNum){
                            m_sound_clear=true;
                            m_allTiled.at(map[row1-1][col]-1)->doubleNumber();
                            m_allTiled.at(map[row1][col]-1)->removeFromParent();
                            
                            //取得当前要消除块在map中的标号
                            int index = map[row1][col];
                            m_allTiled.erase(map[row1][col]-1);
                            //把map中标号大于当前块的减1
                            for(int r=0;r<GAME_ROWS;r++){
                                for(int c=0;c<GAME_COLS;c++){
                                    if(map[r][c]>index){
                                        map[r][c]--;
                                    }
                                }
                            }
                            map[row1][col] = 0;
                        }
                        break;
                    }
                }
                
            }
            
        }
    }
}

void Game::moveLeft(){
    for(int row=0;row < GAME_ROWS;row++){
        //向上移动，先从最上方第4行开始移动(cocos2d中左下角为原点)
        for(int col=0;col < GAME_COLS;col++){
            
            //如果当前块不是空白块->移动
            if(map[row][col] > 0){
                //移动当前行
                for(int col1=col;col1>0;col1--){
                    //判断它左方是否为0,是0就移向左边
                    if(map[row][col1-1]==0){
                        map[row][col1-1]=map[row][col1];
                        map[row][col1]=0;
                        m_allTiled.at(map[row][col1-1]-1)->moveTo(row, col1-1);
                    }else{
                        //判断是否有可以消除的块,取出前方那一块的数值
                        int numObj = m_allTiled.at(map[row][col1-1]-1)->m_number;
                        //取出当前块的值
                        int rowNum = m_allTiled.at(map[row][col1]-1)->m_number;
                        if(numObj == rowNum){
                            m_sound_clear=true;
                            m_allTiled.at(map[row][col1-1]-1)->doubleNumber();
                            m_allTiled.at(map[row][col1]-1)->removeFromParent();
                            
                            //取得当前要消除块在map中的标号
                            int index = map[row][col1];
                            m_allTiled.erase(map[row][col1]-1);
                            //把map中标号大于当前块的减1
                            for(int r=0;r<GAME_ROWS;r++){
                                for(int c=0;c<GAME_COLS;c++){
                                    if(map[r][c]>index){
                                        map[r][c]--;
                                    }
                                }
                            }
                            map[row][col1] = 0;
                        }
                        break;
                    }
                }
                
            }
            
        }
    }

}

void Game::moveRight(){
    for(int row=0;row < GAME_ROWS;row++){
        //向上移动，先从最上方第4行开始移动(cocos2d中左下角为原点)
        for(int col=GAME_COLS-1;col>=0;col--){
            
            //如果当前块不是空白块->移动
            if(map[row][col] > 0){
                //移动当前行
                for(int col1=col;col1<GAME_COLS-1;col1++){
                    //判断它左方是否为0,是0就移向左边
                    if(map[row][col1+1]==0){
                        map[row][col1+1]=map[row][col1];
                        map[row][col1]=0;
                        m_allTiled.at(map[row][col1+1]-1)->moveTo(row, col1+1);
                    }else{
                        //判断是否有可以消除的块,取出前方那一块的数值
                        int numObj = m_allTiled.at(map[row][col1+1]-1)->m_number;
                        //取出当前块的值
                        int rowNum = m_allTiled.at(map[row][col1]-1)->m_number;
                        if(numObj == rowNum){
                            m_sound_clear=true;
                            m_allTiled.at(map[row][col1+1]-1)->doubleNumber();
                            m_allTiled.at(map[row][col1]-1)->removeFromParent();
                            
                            //取得当前要消除块在map中的标号
                            int index = map[row][col1];
                            m_allTiled.erase(map[row][col1]-1);
                            //把map中标号大于当前块的减1
                            for(int r=0;r<GAME_ROWS;r++){
                                for(int c=0;c<GAME_COLS;c++){
                                    if(map[r][c]>index){
                                        map[r][c]--;
                                    }
                                }
                            }
                            map[row][col1] = 0;
                        }
                        break;
                    }
                }
                
            }
            
        }
    }

}
