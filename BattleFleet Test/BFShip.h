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

class BFShip {
public:
	void placeShip(unsigned int x, unsigned int y);
	std::pair<unsigned int,unsigned int> getPosition();
private:
	unsigned int _xCoordinate;
	unsigned int _yCoordinate;
};

#endif /* defined(__BattleFleet__BFShip__) */
