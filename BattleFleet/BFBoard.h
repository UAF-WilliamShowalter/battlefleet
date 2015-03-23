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

// Random hashing function for pairs in order to use unordered_set
// Code directly from stackoverflow.
struct pair_hash {
	inline std::size_t operator()(const std::pair<int,int> & v) const {
		return v.first*31+v.second;
	}
};

typedef unordered_set<pair<unsigned int, unsigned int>, pair_hash> coordinateSet;
typedef pair<unsigned int, unsigned int> pin;

const int BF_BOARD_SIZE = 10;

class BFBoard {
public:
    
	bool placeShip(unsigned int x, unsigned int y, unsigned int length, Direction Direction);
	bool placePin(unsigned int x, unsigned int y);
	bool checkAfloat (const BFShip & shipToCheck) const;
	const vector<BFShip> & getShips() const;
	unsigned int countHits() const;
    
    bool playerHasLost() const;
    
    vector<pin> getHits() const;
    vector<pin> getMisses() const;

public: // Could be made private if testing program is refactored to get code coverage only through the other public interfaces
	bool coordHasHit(unsigned int x, unsigned int y) const;

private:
	bool checkCollisionFree (const BFShip & newShip) const;
	pair<int,int> getDirectionModifier(Direction direction) const;
	bool checkOffBoard(const BFShip & ship) const;
	coordinateSet getSpaces(const BFShip & ship) const;

private:
    vector<BFShip> _board;
	vector<pin> _pins;
};

#endif /* defined(__BattleFleet__BFBoard__) */
