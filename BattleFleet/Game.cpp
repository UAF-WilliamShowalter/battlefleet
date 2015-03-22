//
//  Game.cpp
//  BattleFleet
//
//  Created by Jacob McKenna on 3/19/15.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include <iostream>
#include "Game.h"

Game::Game(){
    
    // Two boards for two players.
    _boards.push_back(BFBoard());
    _boards.push_back(BFBoard());
    
    _turn = PLAYERONE; // Player one starts the game always.
    _gameEnded = false;
    
}

unsigned long Game::numberOfPlayers() {
    
    return _boards.size();
    
}

bool Game::placePlayerShips(Player player, unsigned int x, unsigned int y, unsigned int length, Direction direction) {
    
    return (_boards[player].placeShip(x, y, length, direction));
    
}

bool Game::attackOpponent(Player player, unsigned int x, unsigned int y) {
    
    if ((player == _turn) && (_gameEnded == false)){
        
        if (_boards[getInactivePlayer()].placePin(x, y)){
            
            _gameEnded = (_boards[PLAYERONE].playerHasLost() || _boards[PLAYERTWO].playerHasLost());
            return true;
            
        }
        else
            return false;
        
    }
    
    else
        return false;
    
}

Player Game::playerTurn() const{
    
    return _turn;
    
}

Player Game::getInactivePlayer() const {
    
    if (_turn == PLAYERONE)
        return PLAYERTWO;
    
    else
        return PLAYERONE;
    
}

bool Game::hasEnded() {
    
    return _gameEnded;
    
}

const vector<BFShip> & Game::getPlayerShips(Player player) const
{
	return _boards[player].getShips();
}

void Game::switchPlayer() {
	if (_turn == PLAYERONE){
		_turn = PLAYERTWO;
	}
	else {
		_turn = PLAYERONE;
	}
}

