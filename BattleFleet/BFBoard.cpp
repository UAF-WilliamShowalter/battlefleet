//
//  BFBoard.cpp
//  BattleFleet
//
//  Created by William Showalter on 15/03/11.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#include "BFBoard.h"

bool BFBoard::placeShip(unsigned int x, unsigned int y, unsigned int length, unsigned int direction){
	_board.push_back(BFShip(x,y,length,direction));
	return true;
}

const vector<BFShip> & BFBoard::getShips() const{
	return _board;
}