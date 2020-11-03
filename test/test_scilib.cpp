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

TEMPLATE_TEST_CASE("matrix::median", "[matrix][numerics]", float, double) {
	const fileSys::file<TestType> TEST_FILE = {{4,2,3,2, 5,6,7,1, 2,22,1,5, 2,12,2,9}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);

	SECTION("Median of whole matrix, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat1, 0);
		const double result = 3.5;
		REQUIRE( medMat(0,0) == result );
	}

	SECTION("Median of matrix in row-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat1, 1);
		const std::vector<TestType> result = {3,9,2.5,3.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	SECTION("Median of matrix in column-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat1, 2);
		const std::vector<TestType> result = {2.5,5.5,3.5,5.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	const fileSys::file<TestType> TEST_FILE2 = {{4,2,10, 6,7,1, 2,1,5}, 3,3};
	const scilib::Matrix2d<TestType> mat2(TEST_FILE2);

	SECTION("Median of whole matrix, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 0);
		const double result = 4;
		REQUIRE( medMat(0,0) == result );
	}

	SECTION("Median of matrix in row-wise direction, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 1);
		const std::vector<TestType> result = {4,2,5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	SECTION("Median of matrix in column-wise direction, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 2);
		const std::vector<TestType> result = {4,6,2};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}
}

TEMPLATE_TEST_CASE("matrix::movmedian", "[matrix][numerics]", float, double) {
	const fileSys::file<TestType> TEST_FILE = {{4,3,2, 5,7,1, 2,22,1}, 3,3};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);

	SECTION("Median of whole matrix, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat1, 3, 0);
		const std::vector<TestType> result = {3.5,3,3, 5,5,2, 2,2,11.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	// SECTION("Median of matrix in row-wise direction, even number of elements") {
	// 	const scilib::Matrix2d<TestType> medMat = scilib::median(mat1, 1);
	// 	const std::vector<TestType> result = {3,9,2.5,3.5};
	// 	const TestType *el2 = &result.at(0);
	// 	for (const TestType el: medMat)
	// 		REQUIRE( el == *el2++ );
	// }

	// SECTION("Median of matrix in column-wise direction, even number of elements") {
	// 	const scilib::Matrix2d<TestType> medMat = scilib::median(mat1, 2);
	// 	const std::vector<TestType> result = {2.5,5.5,3.5,5.5};
	// 	const TestType *el2 = &result.at(0);
	// 	for (const TestType el: medMat)
	// 		REQUIRE( el == *el2++ );
	// }

	// const fileSys::file<TestType> TEST_FILE2 = {{4,2,10, 6,7,1, 2,1,5}, 3,3};
	// const scilib::Matrix2d<TestType> mat2(TEST_FILE2);

	// SECTION("Median of whole matrix, odd number of elements") {
	// 	const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 0);
	// 	const double result = 4;
	// 	REQUIRE( medMat(0,0) == result );
	// }

	// SECTION("Median of matrix in row-wise direction, odd number of elements") {
	// 	const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 1);
	// 	const std::vector<TestType> result = {4,2,5};
	// 	const TestType *el2 = &result.at(0);
	// 	for (const TestType el: medMat)
	// 		REQUIRE( el == *el2++ );
	// }

	// SECTION("Median of matrix in column-wise direction, odd number of elements") {
	// 	const scilib::Matrix2d<TestType> medMat = scilib::median(mat2, 2);
	// 	const std::vector<TestType> result = {4,6,2};
	// 	const TestType *el2 = &result.at(0);
	// 	for (const TestType el: medMat)
	// 		REQUIRE( el == *el2++ );
	// }
}