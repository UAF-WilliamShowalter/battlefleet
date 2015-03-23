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
    unsigned long numberOfPlayers() const;
	bool placePlayerShips(Player player, unsigned int x, unsigned int y, unsigned int length, Direction direction);
	bool attackOpponent(Player player, unsigned int x, unsigned int y);
	const vector<BFShip> & getPlayerShips(Player player) const;
    
    const vector<pin> getPlayerMissPins(Player player) const;
    const vector<pin> getPlayerHitPins(Player player) const;
    
    Player getInactivePlayer() const;
    Player getActivePlayer() const;
    bool hasEnded() const;
	bool switchPlayer();
    
private:
    vector<BFBoard> _boards;
    Player _turn;
    bool _gameEnded;
    
};

#endif /* defined(__BattleFleet__Game__) */
