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
        REQUIRE(testBoard.getShips() == testShips);
        
        REQUIRE(!testBoard.placeShip(11,11,5,SOUTH));
        REQUIRE(testBoard.getShips() == testShips);
        
        REQUIRE(!testBoard.placeShip(0, 0, 3, SOUTH));
        REQUIRE(!testBoard.placeShip(1,4,3,WEST));
        REQUIRE(!testBoard.placeShip(7,7,5,EAST));
        REQUIRE(!testBoard.placeShip(1,9,2,NORTH));

		// ALREADY OCCUPIED SPACES
		REQUIRE(!testBoard.placeShip(0,0,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);
		REQUIRE(!testBoard.placeShip(1,0,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);
		REQUIRE(!testBoard.placeShip(0,1,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);

		// CROSSED SHIP PLACEMENT - FIRST SUCCEEDS, SECOND FAILS
		REQUIRE(testBoard.placeShip(7,8,3,EAST));
		testShips.push_back(BFShip(7,8,3,EAST));
		REQUIRE(testBoard.getShips() == testShips);
		REQUIRE(!testBoard.placeShip(8,7,3,NORTH));
		REQUIRE(testBoard.getShips() == testShips);

	}

	SECTION("Place Pins"){
		BFBoard testBoard;
		vector<BFShip> testShips;
		vector<pin> testPins;

		/**** Placing pins with no ships on board. ****/

		//Place a pin on the board (0,0),(1,1),(9,9)
		REQUIRE(testBoard.placePin(0,0));
		REQUIRE(testBoard.placePin(1,1));
		REQUIRE(testBoard.placePin(9,9));

		//Try to place duplicate pin - Fails
		REQUIRE(!testBoard.placePin(0,0));
		REQUIRE(!testBoard.placePin(1,1));
		REQUIRE(!testBoard.placePin(9,9));

		//Try to place pins off board
		REQUIRE(!testBoard.placePin(20,20));
		REQUIRE(!testBoard.placePin(10,10));
		REQUIRE(!testBoard.placePin(5,11));
	}


}