#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include "../11.4. Walls/Walls/Walls.h"

TEST_CASE("Test 1")
{
	const Walls w = 
	{
		{ 200, 400 },
		{ 300, 400 },
		{ 300, 300 },
		{ 400, 300 },
		{ 400, 400 },
		{ 500, 400 },
		{ 500, 200 },
		{ 350, 200 },
		{ 200, 200 }
	};

	const unsigned int L = 100;
	const double expectedResult = 1628;

	CHECK(ComputePerimeter(w, L) == expectedResult);
}

TEST_CASE("Test 2")
{
	const Walls w =
	{
		{ 0, 200 },
		{ 100, 100 },
		{ 200, 200 },
		{ 200, 0 },
		{ 0, 0 }
	};

	const unsigned int L = 100;
	const double expectedResult = 1428;

	CHECK(ComputePerimeter(w, L) == expectedResult);
}

TEST_CASE("Test 3")
{
	const Walls w =
	{
		{ 0, 40 },
		{ 30, 0 },
		{ 0, 0 },
		{ 0, 10 },
		{ 10, 10 }
	};

	const unsigned int L = 20;
	const double expectedResult = 246;

	CHECK(ComputePerimeter(w, L) == expectedResult);
}

TEST_CASE("Test 4")
{
	const Walls w =
	{
		{ 500, 0 },
		{ 700, 100 },
		{ 800, 800 },
		{ 800, 2000 },
		{ 1200, 200 },
		{ 1000, 0 },
		{ 900, -300 },
		{ 0, 0 },
		{ 200, 200 },
		{ 300, 700 },
		{ 400, 600 },
		{ 400, 500 }
	};

	const unsigned int L = 100;
	const double expectedResult = 6158;

	CHECK(ComputePerimeter(w, L) == expectedResult);
}

TEST_CASE("Test 5")
{
	const Walls w =
	{
		{ 0, -1000 },
		{ -2000, -2000 },
		{ -1000, 0 },
		{ -2000, 2000 },
		{ 0, 1000 },
		{ 2000, 2000 },
		{ 1000, 0 },
		{ 2000, -2000 }
	};

	const unsigned int L = 1000;
	const double expectedResult = 22283;

	CHECK(ComputePerimeter(w, L) == expectedResult);
}
