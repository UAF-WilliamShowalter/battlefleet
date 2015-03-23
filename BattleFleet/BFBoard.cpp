//
//  BFBoard.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/11.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFBoard.h"

bool BFBoard::placeShip(unsigned int x, unsigned int y, unsigned int length, Direction direction){
    
    if (x >= BF_BOARD_SIZE || y >= BF_BOARD_SIZE) {
        
        return false;
        
    }

	pair<int,int> modifiers = getDirectionModifier(direction);
	int xModifier = modifiers.first, yModifier = modifiers.second;

	if ( ((y + yModifier*(length - 1)) >= BF_BOARD_SIZE) ||
		 ((x + xModifier*(length - 1)) >= BF_BOARD_SIZE) ) {

            return false;
	}

	BFShip newShip (x,y,length,direction);

	if (checkCollisionFree(newShip)){
		_board.push_back(BFShip(x,y,length,direction));
		return true;
	}
	else
		return false;

}

const vector<BFShip> & BFBoard::getShips() const{
	return _board;
}

bool BFBoard::checkCollisionFree (const BFShip & newShip) const{
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

	pair<int,int> modifiers = getDirectionModifier(ship.getDirection());

	int xModifier = modifiers.first, yModifier = modifiers.second;

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

bool BFBoard::coordHasHit(unsigned int x, unsigned int y) const{
	pin pinToCheck = pin(x,y);
	bool doesNotExist = true;
	
	for (auto pin : _pins)
	{
		if (pin == pinToCheck)
			doesNotExist = false;
	}

	if (doesNotExist)
		return false;

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

bool BFBoard::checkAfloat (const BFShip & shipToCheck) const{
	coordinateSet shipCoordinates = getSpaces(shipToCheck);
	unsigned int hits = 0;
	for (auto coord = shipCoordinates.begin(); coord != shipCoordinates.end(); coord++){
		if (this->coordHasHit(coord->first,coord->second))
			hits++;
	}

	if (hits < shipToCheck.getLength())
		return true;
	else
		return false;
}

unsigned int BFBoard::countHits() const{
	unsigned int count = 0;
	for (auto pin : _pins)
	{
		if (coordHasHit(pin.first,pin.second))
			count++;
	}
	return count;
}

bool BFBoard::playerHasLost() const {
    
    unsigned int shipsSunk = 0;
    
    for (auto ship : _board) {
    
        shipsSunk += !checkAfloat(ship);
        
        if (shipsSunk == _board.size()) {
            
            return true;
            
        }
        
    }
    
    return false;
}

vector<pin> BFBoard::getHits() const {
    
    vector<pin> hits;
    
    for (auto pin : _pins)
    {
        
        if (coordHasHit(pin.first,pin.second))
           hits.push_back(pin);
        
    }
    
    return hits;
    
}


vector<pin> BFBoard::getMisses() const {
    
    vector<pin> misses;
    
    for (auto pin : _pins)
    {
        
        if (!coordHasHit(pin.first,pin.second))
            misses.push_back(pin);
        
    }
    
    return misses;

    
}

pair<int,int> BFBoard::getDirectionModifier(Direction direction) const{
	int xModifier = 0, yModifier = 0;

	if (direction == NORTH)
		yModifier = 1;
	if (direction == SOUTH)
		yModifier = -1;
	if (direction == EAST)
		xModifier = 1;
	if (direction == WEST)
		xModifier = -1;

	return pair<int,int>(xModifier,yModifier);
}

