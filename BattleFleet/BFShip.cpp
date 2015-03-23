//
//  BFShip.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/05.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFShip.h"

BFShip::BFShip(unsigned int x, unsigned int y, unsigned int length, Direction direction){
    
	_xCoordinate = x;
	_yCoordinate = y;
    _length = length;
    _direction = direction;

}

const boardCoordinate BFShip::getPosition() const{

    return boardCoordinate (_xCoordinate, _yCoordinate);
    
}

const unsigned int BFShip::getLength() const{
    
    return _length;
    
}

const Direction BFShip::getDirection() const{
    
    return _direction;
}

bool BFShip::operator == (const BFShip & rhs) const{
	return (this->getPosition() == rhs.getPosition()) &&
		(this->_length == rhs.getLength()) &&
		(this->_direction == rhs.getDirection());
}