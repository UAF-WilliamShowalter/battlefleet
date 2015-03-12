//
//  BFShip.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/05.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFShip.h"

BFShip::BFShip(unsigned int x, unsigned int y, unsigned int length, unsigned int direction){
    
	_xCoordinate = x;
	_yCoordinate = y;
    _length = length;
    _direction = direction;

}

const std::pair<unsigned int, unsigned int> BFShip::getPosition() const{

    return std::pair<unsigned int, unsigned int>(_xCoordinate, _yCoordinate);
    
}

const unsigned int BFShip::getLength() const{
    
    return _length;
    
}

const unsigned int BFShip::getDirection() const{
    
    return _direction;
}

bool BFShip::operator == (const BFShip & rhs) const{
	return (this->getPosition() == rhs.getPosition()) &&
		(this->_length == rhs.getLength()) &&
		(this->_direction == rhs.getDirection());
}