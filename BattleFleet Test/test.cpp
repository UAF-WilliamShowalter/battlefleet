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
		BFShip testShip;
		std::pair<unsigned int, unsigned int> position;

		// X,Y
		testShip.placeShip(0,0);
		testShip.getPosition();
		position.first=0;
		position.second=0;

		REQUIRE(testShip.getPosition() == position);

		testShip.placeShip(3,4);
		position = std::pair<unsigned int, unsigned int>(3,4);
		REQUIRE(testShip.getPosition() == position);
	}
}