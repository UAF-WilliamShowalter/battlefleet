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

TEST_CASE("Tests BattleFleet Game Components","BattleFleet")
{
	SECTION("Ship Placement test"){
		BFShip testShip;
		// X,Y
		testShip.placeOnBoard(0,0);
		REQUIRE(testShip.getPosition() == std_pair<int,int>(0,0));
	}
}