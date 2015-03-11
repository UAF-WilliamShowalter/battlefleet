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

std::pair<unsigned int, unsigned int> BFShip::getPosition(){

    return std::pair<unsigned int, unsigned int>(_xCoordinate, _yCoordinate);
    
}

unsigned int BFShip::getLength(){
    
    return _length;
    
}

unsigned int BFShip::getDirection(){
    
    return _direction;
    
}