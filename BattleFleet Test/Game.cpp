//
//  Game.cpp
//  BattleFleet
//
//  Created by Jacob McKenna on 3/19/15.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "Game.h"

Game::Game(){
    
    // Two boards for two players.
    _boards.push_back(BFBoard());
    _boards.push_back(BFBoard());
    
    _turn = false;
    
}

unsigned long Game::numberOfPlayers() {
    
    return _boards.size();
    
}

bool Game::placePlayerShips(Player player, unsigned int x , unsigned int y, unsigned int length, Direction direction) {
    
    return (_boards[player].placeShip(x, y, length, direction));
    
}

bool Game::attackOpponent(Player player, unsigned int x, unsigned int y) {
    
    if (player == _turn){
        
        if (_boards[!player].placePin(x, y)){
            _turn = !player;
            return true;
        }
        else
            return false;
        
    }
    
    else
        return false;
    
}

bool Game::playerTurn(Player player){
    
    return (player == _turn);
    
}

bool Game::hasEnded() {
    
    for (auto ship = 0; ship < _boards[PLAYERONE].getShips().size(); ship++) {
        
        if (_boards[PLAYERONE].checkAfloat(_boards[PLAYERONE].getShips()[ship]))
            return false;
    
    }
    
    for (auto ship = 0; ship < _boards[PLAYERTWO].getShips().size(); ship++) {
        
        if (_boards[PLAYERTWO].checkAfloat(_boards[PLAYERTWO].getShips()[ship]))
            return false;
        
    }
    
    return true;
    
}


