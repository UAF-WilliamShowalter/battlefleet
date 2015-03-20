//
//  Game.h
//  BattleFleet
//
//  Created by Jacob McKenna on 3/19/15.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#ifndef __BattleFleet__Game__
#define __BattleFleet__Game__

#include <stdio.h>
#include <vector>
#include "BFBoard.h"
#include "BFShip.h"

using std::vector;

enum Player { PLAYERONE, PLAYERTWO };

class Game {
public:
    
    Game();
    unsigned long numberOfPlayers();
    
private:
    vector<BFBoard> _BFGame;
    
};

#endif /* defined(__BattleFleet__Game__) */
