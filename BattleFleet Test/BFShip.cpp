//
//  BFShip.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/05.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFShip.h"

void BFShip::placeShip(unsigned int x, unsigned int y){
	_xCoordinate = x;
	_yCoordinate = y;
}
std::pair<unsigned int, unsigned int> BFShip::getPosition(){
	return std::pair<unsigned int, unsigned int>(_xCoordinate,_yCoordinate);
}