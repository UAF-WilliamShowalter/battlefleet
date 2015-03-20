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
    _BFGame.push_back(BFBoard());
    _BFGame.push_back(BFBoard());
    
}

unsigned long Game::numberOfPlayers() {
    
    return _BFGame.size();
    
}

BFBoard & Game::placePlayerShips(Player player){
    
    return _BFGame[player];
    
}

BFBoard & Game::getOpponentBoard(Player player){
    
    return _BFGame[!player];
    
}