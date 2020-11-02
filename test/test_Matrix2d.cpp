#include <string>
#include <vector>

#include "./catch/catch.hpp"
#include "scilib.h"
#include "fileSys.h"

TEMPLATE_TEST_CASE("Matrix2d constructor", "[matrix2d][numeric]", int, float, double)
{
	const int rows = 2;
	const int columns = 3;

	SECTION("Empty constructor")
	{
		const scilib::Matrix2d<TestType> mat1;
		REQUIRE(mat1.getRows() == 0);
		REQUIRE(mat1.getColumns() == 0);
		REQUIRE(mat1.data.size() == 0);
	}

	SECTION("Without input data")
	{
		const scilib::Matrix2d<TestType> mat1(rows, columns);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}

	SECTION("With std::vector<T> input")
	{
		std::vector<TestType> vec;
		vec.resize(rows * columns);
		const scilib::Matrix2d<TestType> mat1(vec, rows, columns);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}

	SECTION("With fileSys::file<T> input")
	{
		const fileSys::file<TestType> file = {{1, 2, 3, 4, 5, 6}, 2, 3};

		const scilib::Matrix2d<TestType> mat1(file);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}
}

TEMPLATE_TEST_CASE("Matrix2d constructor", "[matrix2d][string]", std::string)
{
	const int rows = 2;
	const int columns = 3;

	SECTION("Empty constructor")
	{
		const scilib::Matrix2d<TestType> mat1;
		REQUIRE(mat1.getRows() == 0);
		REQUIRE(mat1.getColumns() == 0);
		REQUIRE(mat1.data.size() == 0);
	}

	SECTION("Without input data")
	{
		const scilib::Matrix2d<TestType> mat1(rows, columns);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}

	SECTION("With std::vector<T> input")
	{
		std::vector<TestType> vec;
		vec.resize(rows * columns);
		const scilib::Matrix2d<TestType> mat1(vec, rows, columns);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}

	SECTION("With fileSys::file<T> input")
	{
		const fileSys::file<TestType> file = {{"hello", "world", "grey", "fox", "jumped", "over"}, 2, 3};

		const scilib::Matrix2d<TestType> mat1(file);
		REQUIRE(mat1.getRows() == rows);
		REQUIRE(mat1.getColumns() == columns);
		REQUIRE(mat1.data.size() == rows * columns);
	}
}

TEMPLATE_TEST_CASE("Matrix2d begin() & end()", "[matrix2d][numerics]", int, float, double)
{
	// Init matrix
	const int rows = 2;
	const int columns = 2;
	const std::vector<TestType> vec = {1, 2, 3, 4};
	const scilib::Matrix2d<TestType> mat1(vec, rows, columns);

	// The actual test
	const TestType *v = &vec.at(0);
	for (const TestType &el : mat1)
		REQUIRE(el == *v++);
}

TEMPLATE_TEST_CASE("Matrix2d begin() & end()", "[matrix2d][string]", std::string)
{
	// Init matrix
	const int rows = 2;
	const int columns = 2;
	const std::vector<TestType> vec = {"1", "Hello", "World!", ":("};
	const scilib::Matrix2d<TestType> mat1(vec, rows, columns);

	// The actual test
	const TestType *v = &vec.at(0);
	for (const TestType &el : mat1)
		REQUIRE(el == *v++);
}

TEMPLATE_TEST_CASE("Matrix2d resize()", "[matrix2d][all]", int, float, double, std::string)
{
	// Init matrix
	const short rows = 2;
	const short columns = 2;
	const short newRows = 4;
	const short newColumns = 5;
	scilib::Matrix2d<TestType> mat1(rows, columns);

	mat1.resize(newRows, newColumns);
	REQUIRE(mat1.getRows() == newRows);
	REQUIRE(mat1.getColumns() == newColumns);
	mat1.resize(-1, 0);
	REQUIRE(mat1.getRows() == newRows);
	REQUIRE(mat1.getColumns() == newColumns);
}

TEMPLATE_TEST_CASE("Matrix2d popRow() & popColumn() for numerics", "[matrix2d][numerics]", int, float, double)
{
	const fileSys::file<TestType> TEST_FILE = {{1, 2, 3, 5, 6, 7, 10, 12, 14}, 3, 3};
	SECTION("Test 1")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1.popRow(2);
		mat1.popColumn(1);
		REQUIRE(mat1.getRows() == 2);
		REQUIRE(mat1.getColumns() == 2);
		REQUIRE(mat1.data.at(1) == 3);
		REQUIRE(mat1.data.at(3) == 7);
	}
	SECTION("Test 2")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1.popRow(-1);
		mat1.popRow(0);
		mat1.popColumn(-1);
		REQUIRE(mat1.getRows() == 2);
		REQUIRE(mat1.getColumns() == 3);
	}
}

TEMPLATE_TEST_CASE("Matrix2d popRow() & popColumn() for std::string", "[matrix2d][string]", std::string)
{
	const fileSys::file<TestType> TEST_FILE = {{"1", "2", "3", "hello", "2", "world", "a4", "b4", "c4"}, 3, 3};
	SECTION("Test 1")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1.popRow(2);
		mat1.popColumn(1);
		REQUIRE(mat1.getRows() == 2);
		REQUIRE(mat1.getColumns() == 2);
		REQUIRE(mat1.data.at(1) == "3");
		REQUIRE(mat1.data.at(3) == "world");
	}
	SECTION("Test 2")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1.popRow(-1);
		mat1.popRow(0);
		mat1.popColumn(-1);
		REQUIRE(mat1.getRows() == 2);
		REQUIRE(mat1.getColumns() == 3);
	}
}

TEMPLATE_TEST_CASE("Matrix2d T &operator()", "[matrix2d][numerics]", int, float, double)
{
	const fileSys::file<TestType> TEST_FILE = {{1, 2, 3, 5, 6, 7, 10, 12, 14}, 3, 3};
	SECTION("Accessing values")
	{
		const scilib::Matrix2d<TestType> mat1(TEST_FILE);
		REQUIRE(mat1(0) == 1);
		REQUIRE(mat1(7) == 12);
		REQUIRE(mat1(0, 0) == 1);
		REQUIRE(mat1(1, 2) == 7);
	}
	SECTION("Redefining values")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1(1, 2) = 123;
		REQUIRE(mat1(1, 2) == 123);
		mat1(2) = 321;
		REQUIRE(mat1(2) == 321);
		REQUIRE(mat1(0, 2) == 321);
	}
}

TEMPLATE_TEST_CASE("Matrix2d &operator()", "[matrix2d][string]", std::string)
{
	const fileSys::file<TestType> TEST_FILE = {{"1", "2", "3", "hello", "2", "world", "a4", "b4", "c4"}, 3, 3};
	SECTION("Accessing values")
	{
		const scilib::Matrix2d<TestType> mat1(TEST_FILE);
		REQUIRE(mat1(0) == "1");
		REQUIRE(mat1(7) == "b4");
		REQUIRE(mat1(0, 0) == "1");
		REQUIRE(mat1(1, 2) == "world");
	}
	SECTION("Redefining values")
	{
		scilib::Matrix2d<TestType> mat1(TEST_FILE);
		mat1(1, 2) = "123";
		REQUIRE(mat1(1, 2) == "123");
		mat1(2) = "321";
		REQUIRE(mat1(2) == "321");
		REQUIRE(mat1(0, 2) == "321");
	}
}

TEMPLATE_TEST_CASE("Matrix2d product operator*", "[matrix2d][numerics]", int, float, double)
{
	const fileSys::file<TestType> TEST_FILE = {{1, 2, 3, 5, 6, 7, 10, 12, 14}, 3, 3};
	const fileSys::file<TestType> TEST_FILE2 = {{3, 2, 1, -1, -2, -3}, 2, 3};
	const scilib::Matrix2d<TestType> mat1(TEST_FILE);
	const scilib::Matrix2d<TestType> mat2(TEST_FILE2);
	SECTION("Accessing values")
	{
		const scilib::Matrix2d<TestType> mat3 = mat2 * mat1;
		REQUIRE(mat3(0, 0) == 23);
		REQUIRE(mat3(1, 2) == -59);
		REQUIRE(mat3.getRows() == 2);
		REQUIRE(mat3.getColumns() == 3);
	}
	SECTION("Incompatible sizes")
	{
		const scilib::Matrix2d<TestType> mat3 = mat1 * mat2;
		REQUIRE(mat3.getRows() == 0);
		REQUIRE(mat3.getColumns() == 0);
	}
}

TEMPLATE_TEST_CASE("Matrix2d transpose operator~", "[matrix2d][numerics]", int, float, double)
{
	const fileSys::file<TestType> TEST_FILE = {{1, 2, 3, 5, 6, 7, 10, 12, 14}, 3, 3};

	const scilib::Matrix2d<TestType> mat1(TEST_FILE);
	const scilib::Matrix2d<TestType> mat2 = ~mat1;
	REQUIRE(mat2(0, 0) == 1);
	REQUIRE(mat2(0, 1) == 5);
	REQUIRE(mat2(2, 1) == 7);
	REQUIRE(mat2.getRows() == 3);
	REQUIRE(mat2.getColumns() == 3);
}

TEMPLATE_TEST_CASE("Matrix2d inverse operator!", "[matrix2d][numerics]", float, double)
{
	const fileSys::file<TestType> TEST_FILE = {{1, 2, 3, 5, 6, 7, 10, 12, 14}, 3, 3};
	const fileSys::file<TestType> TEST_FILE2 = {{4, 2, 3, 5, 6, 7, 2, 3, 1}, 3, 3};

	SECTION("Test singularity")
	{
		const scilib::Matrix2d<TestType> mat1(TEST_FILE);
		const scilib::Matrix2d<TestType> mat2 = !mat1;
		for (const TestType &el : mat2)
			REQUIRE(el == 0);
	}
	SECTION("Test inverse")
	{
		const scilib::Matrix2d<TestType> mat1(TEST_FILE2);
		const scilib::Matrix2d<TestType> mat2 = !mat1;
		const double epsilon = 1e-6;
		REQUIRE(std::abs(mat2(1, 1) - 0.060606) < epsilon);
	}
}