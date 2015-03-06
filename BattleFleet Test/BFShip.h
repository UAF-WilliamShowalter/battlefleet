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
	
	BFShip(unsigned int x, unsigned int y, unsigned int length);
	std::pair<unsigned int,unsigned int> getPosition();
	unsigned int getLength();
    
private:
    
	unsigned int _xCoordinate;
	unsigned int _yCoordinate;
	unsigned int _length;
	
};

#endif /* defined(__BattleFleet__BFShip__) */
