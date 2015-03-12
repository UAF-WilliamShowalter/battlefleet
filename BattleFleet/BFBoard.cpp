//
//  BFBoard.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/11.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFBoard.h"

bool BFBoard::placeShip(unsigned int x, unsigned int y, unsigned int length, unsigned int direction){
    
    if (x > 9) {
        
        return false;
        
    }
    
    if (y > 9) {
        
        return false;
        
    }
    
    if (direction == NORTH) {

        if ((y + length - 1) > 9) {
            
            return false;
            
        }
    }
    
    if (direction == SOUTH) {
        
        if ((y - length + 1) > 9) {
            
            return false;
            
        }
    }
    
    if (direction == EAST) {
        
        if ((x + length - 1) > 9) {
            
            return false;
            
        }
    }
    
    if (direction == WEST) {
        
        if ((x - length + 1) > 9) {
            
            return false;
            
        }
    }
    
	_board.push_back(BFShip(x,y,length,direction));
	return true;

}

const vector<BFShip> & BFBoard::getShips() const{
	return _board;
}