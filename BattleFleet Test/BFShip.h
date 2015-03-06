//
//  BFShip.h
//  BattleFleet
//
//  Created by William Showalter on 15/03/05.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#ifndef __BattleFleet__BFShip__
#define __BattleFleet__BFShip__

#include <stdio.h>
#include <utility>

enum Direction {North, East, West, South};

class BFShip {
public:
	
	BFShip(unsigned int x, unsigned int y, unsigned int length, unsigned int Direction);
	std::pair<unsigned int,unsigned int> getPosition();
	unsigned int getLength();
	unsigned int getDirection();
    
private:
    
	unsigned int _xCoordinate;
	unsigned int _yCoordinate;
	unsigned int _length;
	unsigned int _direction;
	
};

#endif /* defined(__BattleFleet__BFShip__) */
