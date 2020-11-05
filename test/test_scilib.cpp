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

TEMPLATE_TEST_CASE("matrix::movmedian", "[matrix][numerics]", float, double)  {
	const fileSys::file<TestType> TEST_FILE = {{4,3,2,2, 3,5,7,1, 1,2,22,1, 1,2,3,4}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);

	SECTION("Median of whole matrix, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat1, 3, 0);
		const std::vector<TestType> result = {3.5,3,2,2, 3,5,5,1, 1,2,2,1, 1,2,3,3.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	SECTION("Median of matrix in row-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat1, 3, 1);
		const fileSys::file<TestType> RESULT_FILE = {{3.5,4,4.5,1.5, 3,3,7,1, 1,2,7,1, 1,2,12.5,2.5}, 4,4};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat) {
			REQUIRE( el == *el2++ );
		}
	}

	SECTION("Median of matrix in column-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat1, 3, 2);
		const fileSys::file<TestType> RESULT_FILE = {{3.5,3,2,2, 4,5,5,4, 1.5,2,2,11.5, 1.5,2,3,3.5}, 4,4};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat) {
			REQUIRE( el == *el2++ );
		}
	}


	const fileSys::file<TestType> TEST_FILE2 = {{4,3,2, 5,7,1, 2,22,1}, 3,3};
	const scilib::Matrix2d<TestType> mat2(TEST_FILE2);
	SECTION("Median of whole matrix, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat2, 3, 0);
		const std::vector<TestType> result = {3.5,3,3, 5,5,2, 2,2,11.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( el == *el2++ );
	}

	SECTION("Median of matrix in row-wise direction, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat2, 3, 1);
		const fileSys::file<TestType> RESULT_FILE = {{4.5,5,1.5, 4,7,1, 3.5,14.5,1}, 3,3};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat) {
			REQUIRE( el == *el2++ );
		}
	}

	SECTION("Median of matrix in column-wise direction, odd number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmedian(mat2, 3, 2);
		const fileSys::file<TestType> RESULT_FILE = {{3.5,3,2.5, 6,5,4, 12,2,11.5}, 3,3};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat) {
			REQUIRE( el == *el2++ );
		}
	}
}

TEMPLATE_TEST_CASE("matrix::mean", "[matrix][numerics]", float, double)  {
	const fileSys::file<TestType> TEST_FILE = {{4,3,2,2, 3,5,8,1, 1,2,6,1, 1,2,3,4}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);
	const double epsilon = 1e-6;
	SECTION("Mean of the whole matrix") {
		const scilib::Matrix2d<TestType> meanMat = scilib::mean(mat1, 0);
		const TestType result = 3.0;
		REQUIRE( std::abs(meanMat(0)-result) < epsilon );
	}

	SECTION("Mean of the whole matrix in row-wise direction") {	
		const scilib::Matrix2d<TestType> meanMat = scilib::mean(mat1, 1);
		const std::vector<TestType> result = {2.25, 3, 4.75, 2};
		const TestType *el2 = &result.at(0);
		for (const TestType &el : meanMat)
			REQUIRE( std::abs(el-*el2++) < epsilon);
	}

	SECTION("Mean of the whole matrix in column-wise direction") {	
		const scilib::Matrix2d<TestType> meanMat = scilib::mean(mat1, 2);
		const std::vector<TestType> result = {2.75, 4.25, 2.5, 2.5};
		const TestType *el2 = &result.at(0);
		for (const TestType &el : meanMat)
			REQUIRE( std::abs(el-*el2++) < epsilon);
	}
}

TEMPLATE_TEST_CASE("matrix::movmean", "[matrix][numerics]", float, double)  {
	const fileSys::file<TestType> TEST_FILE = {{4,3,2,2, 3,5,7,1, 2,2,22,1, 1,2,3,4}, 4,4};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);
	const double epsilon = 1e-3;

	SECTION("Mean of whole matrix, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmean(mat1, 3, 0);
		const std::vector<TestType> result = {3.5,3,2.333,2.333, 3.333,5,4.333,3.333, 1.666,8.666,8.333,8, 1.333,2,3,3.5};
		const TestType *el2 = &result.at(0);
		for (const TestType el: medMat)
			REQUIRE( std::abs(el-*el2++) < epsilon );
	}

	SECTION("Mean of matrix in row-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmean(mat1, 3, 1);
		const fileSys::file<TestType> RESULT_FILE = {{3.5,4,4.5,1.5, 3,3.333,10.333,1.333, 2,3,10.666,2, 1.5,2,12.5,2.5}, 4,4};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat)
			REQUIRE( std::abs(el-*el2++) < epsilon );
	}

	SECTION("Mean of matrix in column-wise direction, even number of elements") {
		const scilib::Matrix2d<TestType> medMat = scilib::movmean(mat1, 3, 2);
		const fileSys::file<TestType> RESULT_FILE = {{3.5,3,2.333,2, 4,5,4.333,4, 2,8.666,8.333,11.5, 1.5,2,3,3.5}, 4,4};
		const scilib::Matrix2d<TestType> result(RESULT_FILE);
		const TestType *el2 = &result.data.at(0);
		for (const TestType el: medMat)
			REQUIRE( std::abs(el-*el2++) < epsilon );
	}
}