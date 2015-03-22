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
        
        if (_boards[!player].placePin(x, y)){
			if (_turn == PLAYERONE){
				_turn = PLAYERTWO;
			}
			else {
				_turn = PLAYERONE;
			}
            return true;
        }
        else
            return false;
        
    }
    
    else
        return false;
    
}

Player Game::playerTurn(){
    
    return _turn;
    
}

bool Game::hasEnded() {
    
    unsigned int shipsSunk = 0;
    
	for (auto ship : _boards[PLAYERONE].getShips()) {
        
        shipsSunk += !_boards[PLAYERONE].checkAfloat(ship);
        
        if (shipsSunk == _boards[PLAYERONE].getShips().size()) {
            _gameEnded = true;
            return true;
        }
    
    }
    
    shipsSunk = 0;
    
    for (auto ship = 0; ship < _boards[PLAYERTWO].getShips().size(); ship++) {
        
        shipsSunk += !_boards[PLAYERTWO].checkAfloat(_boards[PLAYERTWO].getShips()[ship]);
        
        if (shipsSunk == _boards[PLAYERTWO].getShips().size()) {
            _gameEnded = true;
            return true;
        }
        
    }
    
    return false;
    
}

