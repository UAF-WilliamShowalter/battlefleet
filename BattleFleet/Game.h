//
//  Game.h
//  BattleFleet
//
//  Created by Jacob McKenna on 3/19/15.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#ifndef __BattleFleet__Game__
#define __BattleFleet__Game__

#include <vector>
#include "BFBoard.h"

using std::vector;

enum Player { PLAYERONE, PLAYERTWO };

class Game {
public:
    
    Game();
    unsigned long numberOfPlayers();
    bool placePlayerShips(Player, unsigned int, unsigned int, unsigned int, Direction);
    bool attackOpponent(Player, unsigned int, unsigned int);
    
    bool playerTurn(Player);
    bool hasEnded();
    
private:
    vector<BFBoard> _boards;
    bool _turn;
    bool _gameEnded;
    
};

#endif /* defined(__BattleFleet__Game__) */
