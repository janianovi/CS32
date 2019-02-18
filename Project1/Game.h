//
//  Game.h
//  main
//
//  Created by Janis Chen on 1/9/19.
//  Copyright © 2019 Test Project. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();

    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    int decodeDirection(char dir);

};

#endif
