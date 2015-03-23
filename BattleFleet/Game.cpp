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
    
    _activePlayer = PLAYERONE; // Player one starts the game.
}

unsigned long Game::numberOfPlayers() const{
    
    return _boards.size();
    
}

bool Game::placePlayerShips(Player player, unsigned int x, unsigned int y, unsigned int length, Direction direction) {
    
    return (_boards[player].placeShip(x, y, length, direction));
    
}

bool Game::attackOpponent(Player player, unsigned int x, unsigned int y) {
    
    if ((player == _activePlayer) && (!hasEnded())){
        
        if (_boards[getInactivePlayer()].placePin(x, y)){
            
            return true;
            
        }
        else
            return false;
        
    }
    
    else
        return false;
    
}

Player Game::getActivePlayer() const{
    
    return _activePlayer;
    
}

Player Game::getInactivePlayer() const {
    
    if (_activePlayer == PLAYERONE)
        return PLAYERTWO;
    
    else
        return PLAYERONE;
    
}

bool Game::hasEnded() const {
    
	return	(_boards[PLAYERONE].playerHasLost() || _boards[PLAYERTWO].playerHasLost());

}

const vector<BFShip> & Game::getPlayerShips(Player player) const
{
	return _boards[player].getShips();
}

bool Game::switchPlayer() {
	if (_activePlayer == PLAYERONE){
		_activePlayer = PLAYERTWO;
	}
	else {
		_activePlayer = PLAYERONE;
	}

	// Returning true allows for the use of statements like:
	// (Game->attackOpponent(Player, X, Y) && Game->switchPlayer());
	// Where the switch player only executes after a successful attach placement.
	return true;
}

const vector<pin> Game::getPlayerMissPins(Player player) const{
    
    return _boards[player].getMisses();
    
}

const vector<pin> Game::getPlayerHitPins(Player player) const {
    
    return _boards[player].getHits();
    
}

