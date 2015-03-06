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
        BFShip testShip(0,0,3);
		std::pair<unsigned int, unsigned int> position(0,0);

		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 3);
        

        testShip = BFShip(3,4,4);
		position = std::pair<unsigned int, unsigned int>(3,4);
		REQUIRE(testShip.getPosition() == position);
        REQUIRE(testShip.getLength() == 4);
        
	}
}