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

        if ((y + length) > BF_BOARD_SIZE) {
            
            return false;
            
        }
    }
    
    if (direction == SOUTH) {
        
        if ((y - length + 1) > 9) {
            
            return false;
            
        }
    }
    
    if (direction == EAST) {
        
        if ((x + length) > BF_BOARD_SIZE) {
            
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
	coordinateSet spaces;

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
	for (auto pin : _pins)
	{
		if (pin.first == x && pin.second == y)
			return false;
		if ((BF_BOARD_SIZE <= x) || (BF_BOARD_SIZE <= y))
			return false;
	}
	_pins.push_back(pin(x,y));
	return true;
}

bool BFBoard::coordHasHit(unsigned int x, unsigned int y){
	pin pinToCheck = pin(x,y);
	for (auto ship : _board)
	{
		coordinateSet shipCoordinates = getSpaces(ship);
		for (auto coord = shipCoordinates.begin(); coord != shipCoordinates.end(); coord++){
			if (pinToCheck.first == coord->first && pinToCheck.second == coord->second)
				return true;
		}
	}

	return false;
}