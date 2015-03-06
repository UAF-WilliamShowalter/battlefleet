//
//  test.cpp
//  BattleFleet
//  UAF CS372
//  Spring 2015, Project 1
//  William Showalter & Jacob McKenna
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <utility>
#include "BFShip.h"

TEST_CASE("Tests BattleFleet Game Components","BattleFleet")
{
	SECTION("Ship Placement test"){
        BFShip testShip(0,0,3,0);
		std::pair<unsigned int, unsigned int> position(0,0);

		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 3);
        REQUIRE(testShip.getDirection() == North);

        testShip = BFShip(3,4,4,1);
		position = std::pair<unsigned int, unsigned int>(3,4);
		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 4);
        REQUIRE(testShip.getDirection() == East);
        
        testShip = BFShip(10,10,5,2);
        position = std::pair<unsigned int, unsigned int>(10,10);
        REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 5);
        REQUIRE(testShip.getDirection() == South);
        
        testShip = BFShip(9,1,2,3);
        position = std::pair<unsigned int, unsigned int>(9,1);
        REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 2);
        REQUIRE(testShip.getDirection() == West);
	}
}