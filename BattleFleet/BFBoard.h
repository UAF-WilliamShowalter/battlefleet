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

typedef unordered_set<pair<unsigned int, unsigned int>, pair_hash> coordinateSet;
typedef pair<unsigned int, unsigned int> pin;

class BFBoard {
public:
    
	bool placeShip(unsigned int x, unsigned int y, unsigned int length, unsigned int Direction);
	bool placePin(unsigned int x, unsigned int y);
	bool coordHasHit(unsigned int x, unsigned int y) const;
	bool checkCollision (const BFShip & newShip) const;
	bool checkAfloat (const BFShip & shipToCheck) const;
	const vector<BFShip> & getShips() const;
	unsigned int countHits() const;
    
    bool playerHasLost() const;

private:
	coordinateSet getSpaces(const BFShip & ship) const;
    vector<BFShip> _board;
	vector<pin> _pins;
};

#endif /* defined(__BattleFleet__BFBoard__) */
