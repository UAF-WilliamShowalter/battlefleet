//
//  BFBoard.h
//  BattleFleet
//
//  Created by William Showalter on 15/03/11.
//  Copyright (c) 2015 UAF CS372. All rights reserved.
//

#ifndef __BattleFleet__BFBoard__
#define __BattleFleet__BFBoard__

#include <stdio.h>
#include <vector>
#include "BFShip.h"

using std::vector;

const int BF_BOARD_SIZE = 10;

class BFBoard {
public:
	bool placeShip(unsigned int x, unsigned int y, unsigned int length, unsigned int Direction);

private:
	vector<BFShip> _board;
};

#endif /* defined(__BattleFleet__BFBoard__) */
