//
//  test.cpp
//  BattleFleet
//  UAF CS372
//  Spring 2015, Project 1
//  William Showalter & Jacob McKenna
//

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <utility>
#include "BFShip.h"
#include "BFBoard.h"
#include "catch.hpp"

TEST_CASE("Tests BattleFleet Game Components","BattleFleet")
{
	SECTION("Individual Ship Placement test"){
        BFShip testShip(0,0,3,NORTH);
		std::pair<unsigned int, unsigned int> position(0,0);
		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 3);
        REQUIRE(testShip.getDirection() == NORTH);

        testShip = BFShip(3,4,4,EAST);
		position = std::pair<unsigned int, unsigned int>(3,4);
		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 4);
        REQUIRE(testShip.getDirection() == EAST);
        
        testShip = BFShip(10,10,5,SOUTH);
        position = std::pair<unsigned int, unsigned int>(10,10);
        REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 5);
        REQUIRE(testShip.getDirection() == SOUTH);
        
        testShip = BFShip(9,1,2,WEST);
        position = std::pair<unsigned int, unsigned int>(9,1);
        REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 2);
        REQUIRE(testShip.getDirection() == WEST);
	}

	SECTION("Board Multiple Ship Placement test"){
		BFBoard testBoard;
		vector<BFShip> testShips;
		REQUIRE(testBoard.placeShip(0,0,3,NORTH));
		testShips.push_back(BFShip(0,0,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);

		REQUIRE(testBoard.placeShip(1,0,3,NORTH));
		testShips.push_back(BFShip(1,0,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);

        // Bad Placement tests...
        REQUIRE(!testBoard.placeShip(-1,0,3,NORTH));
        REQUIRE(!testBoard.placeShip(11,11,5,SOUTH));
	}
}



