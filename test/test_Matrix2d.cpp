#include <string>
#include <vector>

#include "./catch/catch.hpp"
#include "scilib.h"
#include "fileSys.h"

TEMPLATE_TEST_CASE( "Matrix2d constructor without input data", "[matrix2d][template]", int, float, double, std::string) {
	const int rows = 2;
	const int columns = 3;

	scilib::Matrix2d<TestType> mat1(rows, columns);
    REQUIRE( mat1.getRows() == rows );
	REQUIRE( mat1.getColumns() == columns );
	REQUIRE( mat1.data.size() == rows*columns );
}

TEMPLATE_TEST_CASE( "Matrix2d constructor with std::vector", "[matrix2d][template]", int, float, double, std::string) {
	const int rows = 2;
	const int columns = 3;
	std::vector<TestType> vec;
	vec.resize(rows*columns);
	scilib::Matrix2d<TestType> mat1(vec, rows, columns);
    REQUIRE( mat1.getRows() == rows );
	REQUIRE( mat1.getColumns() == columns );
	REQUIRE( mat1.data.size() == rows*columns );
}

TEMPLATE_TEST_CASE( "Matrix2d constructor with fileSys::file", "[matrix2d][template]", int, float, double, std::string) {
	const int rows = 2;
	const int columns = 3;
	fileSys::file<TestType> file;
	file.data.resize(rows*columns);
	file.rows = rows;
	file.columns = columns;

	scilib::Matrix2d<TestType> mat1(file);
    REQUIRE( mat1.getRows() == rows );
	REQUIRE( mat1.getColumns() == columns );
	REQUIRE( mat1.data.size() == rows*columns );
}