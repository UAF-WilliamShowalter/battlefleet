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
#include <unordered_set>
#include "BFShip.h"

using std::vector;
using std::unordered_set;
using std::pair;

const int BF_BOARD_SIZE = 10;

// Random hashing function for pairs in order to use unordered_set
// Code directly from stackoverflow - should review it at some point.
struct pair_hash {
	inline std::size_t operator()(const std::pair<int,int> & v) const {
		return v.first*31+v.second;
	}
};

class BFBoard {
public:
    
	bool placeShip(unsigned int x, unsigned int y, unsigned int length, unsigned int Direction);
	const unordered_set<pair<unsigned int,unsigned int>, pair_hash > getOccupiedSpaces () const;
	const vector<BFShip> & getShips() const;

private:

    vector<BFShip> _board;

};

#endif /* defined(__BattleFleet__BFBoard__) */
