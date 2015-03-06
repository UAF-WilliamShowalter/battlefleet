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
        BFShip testShip1(0,0,3);
		std::pair<unsigned int, unsigned int> position;

		testShip1.getPosition();
		position.first=0;
		position.second=0;

		REQUIRE(testShip1.getPosition() == position);
        REQUIRE(testShip1.getLength() == 3);
        

        testShip1 = BFShip(3,4,4);
		position = std::pair<unsigned int, unsigned int>(3,4);
		REQUIRE(testShip1.getPosition() == position);
        REQUIRE(testShip1.getLength() == 4);
        
	}
}