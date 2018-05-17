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
		TEST_METHOD(matrix_row_0_col_0)
		{
			//empty matrix using default constructor
			Matrix *m = new Matrix();
			Assert::AreEqual(m->get_row(), 0);
			Assert::AreEqual(m->get_col(), 0);
			delete m;
		}
		TEST_METHOD(matrix_row_n_col_n)
		{
			//matrix using constructor (parameter)
			Matrix *m = new Matrix(35,35);
			Assert::AreEqual(m->get_row(), 35);
			Assert::AreEqual(m->get_col(), 35);
			delete m;
		}
		TEST_METHOD(matrix_set_n_get)
		{
			//matrix set and get
			Matrix *m = new Matrix(5, 5);
			m->set(3,3,1);
			Assert::AreEqual(m->get(3, 3), 1);
			delete m;
		}

	};

	TEST_CLASS(newgame_test){
	public:
		TEST_METHOD(newgame_set_n_get)
		{
			// set and then get
			newGame *ng = new newGame(5, 5);
			ng->set(3, 3, 1);
			Assert::AreEqual(ng->get(3, 3), 1);
			delete ng;
		}

	};

	TEST_CLASS(bygeneration_test){
	public:
		TEST_METHOD(zombie_mode_wait_rate)
		{
			// set / get wait rate
			By_Generation *g = new By_Generation();
			Assert::AreEqual(g->get_zombie_mode_wait_rate(), 5);
			delete g;
		}

	};

	TEST_CLASS(byqueue_test){
	public:
		TEST_METHOD(resurrection_rate)
		{
			// set / get res rate
			By_Queue *q = new By_Queue();
			Assert::AreEqual(q->get_resurrection_rate(), 10);
			delete q;
		}

	};
}