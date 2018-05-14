#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Game_of_life/matrix.h"
#include "../Game_of_life/newGame.h"
#include "../Game_of_life/By_Generation.h"
#include "../Game_of_life/By_Queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
* https://msdn.microsoft.com/en-us/library/ee782531.aspx
* From the Visual Studio menu, choose Test, then choose Settings, and then choose Processor Architecture. Choose x64 to run the tests as a 64-bit process.
*/

namespace Unit_test
{		
	TEST_CLASS(matrix_test){
	public:
		TEST_METHOD(row_0_col_0)
		{
			//empty matrix using default constructor
			Matrix *m = new Matrix();
			Assert::AreEqual(m->get_row(), 0);
			Assert::AreEqual(m->get_col(), 0);
			delete m;
		}
		TEST_METHOD(row_n_col_n)
		{
			//matrix using constructor (parameter)
			Matrix *m = new Matrix(35,35);
			Assert::AreEqual(m->get_row(), 35);
			Assert::AreEqual(m->get_col(), 35);
			delete m;
		}

	};

	TEST_CLASS(newgame_test){
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};

	TEST_CLASS(bygeneration_test){
	public:
		TEST_METHOD(zombie_mode_wait_rate)
		{
			// set / get wait rate thing
		}

	};

	TEST_CLASS(byqueue_test){
	public:
		TEST_METHOD(resurrection_rate)
		{
			// set and get resurrection rate
		}

	};
}