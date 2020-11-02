#include <string>
#include <vector>
#include <array>

#include "./catch/catch.hpp"
#include "scilib.h"
#include "fileSys.h"


TEMPLATE_TEST_CASE("matrix::determinant", "[matrix][numerics]", int, float, double) {
	const fileSys::file<TestType> TEST_FILE = {{4,2,3,2, 5,6,7,1, 2,3,1,5, 2,3,2,3}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);
	REQUIRE( scilib::determinant(mat1) == -2 );
}

TEMPLATE_TEST_CASE("matrix::adjugate", "[matrix][numerics]", int, float, double) {
	const fileSys::file<TestType> TEST_FILE = {{4,2,3,2, 5,6,7,1, 2,3,1,5, 2,3,2,3}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);

	const scilib::Matrix2d<TestType> mat2 = scilib::adjugate(mat1);
	const std::array<TestType, 16> result = {3,-10,-25,43, 5,-12,-29,49, -6,16,40,-68, -3,8,19,-33};
	const TestType *val = &result.at(0);
	for (const TestType el : mat2)
		REQUIRE( el == *val++ );
}