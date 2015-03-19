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

	BFShip newShip (x,y,length,direction);
	if (checkCollision(newShip)){
		_board.push_back(BFShip(x,y,length,direction));
		return true;
	}
	else
		return false;

}

const vector<BFShip> & BFBoard::getShips() const{
	return _board;
}

bool BFBoard::checkCollision (const BFShip & newShip) const{
	unordered_set<pair<unsigned int, unsigned int>, pair_hash> spaces;

	coordinateSet newShipCoordinates = getSpaces(newShip);

	for (auto ship : _board){
		coordinateSet shipCoordinates = getSpaces (ship);
		for (auto coord = shipCoordinates.begin(); coord != shipCoordinates.end(); coord++){
			if (newShipCoordinates.count(*coord))
				return false;
		}
	}

	return true;
}

coordinateSet BFBoard::getSpaces(const BFShip & ship) const{
	coordinateSet spaces;
	boardCoordinate currentPosition = ship.getPosition();
	int xModifier = 0, yModifier = 0;

	if (ship.getDirection() == NORTH)
		yModifier = 1;
	if (ship.getDirection() == SOUTH)
		yModifier = -1;
	if (ship.getDirection() == EAST)
		xModifier = 1;
	if (ship.getDirection() == WEST)
		xModifier = -1;

	for (auto coordNum = 0; coordNum < ship.getLength();
		 currentPosition.first += xModifier, currentPosition.second += yModifier, coordNum++){
		spaces.insert(currentPosition);
	}

	return spaces;
}

bool BFBoard::placePin(unsigned int x, unsigned int y){
	return true;
}