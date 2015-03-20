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