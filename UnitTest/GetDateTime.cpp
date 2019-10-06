#include "pch.h"
#include "CppUnitTest.h"
#include "../Garsim_C/Time.c"
#include <iostream>
#include <fstream>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GETDATETIME
{
	TEST_CLASS(GETDATETIME)
	{
	public:
		TEST_METHOD(Month1)
		{
			int mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			
			for (int v = 3; v <= 12; v++) {
				int x = 0, c;
				for (c = 0; c < v - 1; c++)
				{
					if (c == 1)
						x += 29;
					else
						x += mon[c];
				}
				Assert::IsTrue(month(v, 2020) == x);
			}
			
		}
		TEST_METHOD(Month1Not)
		{
			Assert::IsTrue(month(03, 2020) != 60);
		}
		TEST_METHOD(Month2)
		{
			Assert::IsTrue(month(03, 2019) != 0);
		}
		TEST_METHOD(Month2Not)
		{
			Assert::IsTrue(month(03, 2019) == 59);
		}
		TEST_METHOD(Month3)
		{
			Assert::IsTrue(month(02, 2020) == 31);
		}
		TEST_METHOD(Month3Not)
		{
			Assert::IsTrue(month(02, 2020) != 0);
		}
		TEST_METHOD(Month4)
		{
			Assert::IsTrue(month(02, 2019) == 31);
		}
		TEST_METHOD(Month4Not)
		{
			Assert::IsTrue(month(02, 2019) != 0);
		}

		
		TEST_METHOD(days1)
		{
			Assert::IsTrue(days(1980, 2020, 01, 10, 6, 28) == 1496);
		}
		TEST_METHOD(days1Not)
		{
			Assert::IsTrue(days(1980, 2020, 10, 01, 6, 28) != 14358);
		}
		TEST_METHOD(days2)
		{
			Assert::IsTrue(days(2020, 1980, 01, 10, 28, 6) == 252);
		}
		TEST_METHOD(days2Not)
		{
			Assert::IsTrue(days(2020, 1980, 01, 10, 6, 28) != 296);
		}
		
		TEST_METHOD(Split1)
		{
			char splited[20] = "22-Jan-201900:00:00";//?????????????????????????????
			int actual[6] = {2019,1,22,0,0,0};
			int* expected = split(splited);
			Assert::AreEqual(expected[1], actual[1]);
		}
		TEST_METHOD(Split11)
		{
			char splited[] = "22-Jan-2019 00:00:00";//?????????????????????????????
			//splitted[20] = '\0';
			int actual[6] = { 2019,1,22,0,0,0 };
			int* expected = split(splited);
			Assert::AreEqual(expected[2], actual[2]);
		}
		TEST_METHOD(Split111)
		{
			char splited[] = "22-Jan-2019 00:00:00";//?????????????????????????????
			int actual[6] = { 2019,1,22,0,0,0 };
			int* expected = split(splited);
			Assert::AreEqual(expected[1], actual[4]);
		}
		TEST_METHOD(Split2)
		{
			char splited[] = "22-Jul-2010 00:00:00";//?????????????????????????????
			int actual[6] = { 2019,7,22,0,0,0 };
			int* expected = split(splited);
			Assert::AreEqual(expected[1], actual[1]);
		}
		
		TEST_METHOD(GetDateTime1) 
		{
			/*char dt[30];
			float jd;
			int dv[6];
			int gwn;
			int dow;
			int sow;*/
			Time* time=NULL;
			char utcDateTime[] = "22-Jan-201900:00:00";
			GetDateTime(time, utcDateTime);
			int actual_dv = 2019;
			int expected_dv = time->dv[0];
			Assert::AreEqual(actual_dv, expected_dv);
		}
		TEST_METHOD(GetDateTime11)
		{
			/*char dt[30];
			float jd;
			int dv[6];
			int gwn;
			int dow;
			int sow;*/
			Time* time = NULL;
			char utcDateTime[] = "22-Jan-201900:00:00";
			GetDateTime(time, utcDateTime);
			
			int actual_gwn = 2037;
			int expected_gwn = time->gwn;
			Assert::AreEqual(actual_gwn, expected_gwn);

		}
		TEST_METHOD(GetDateTime111)
		{
			/*char dt[30];
			float jd;
			int dv[6];
			int gwn;
			int dow;
			int sow;*/
			Time* time = NULL;
			char utcDateTime[] = "22-Jan-201900:00:00";
			GetDateTime(time, utcDateTime);

			int actual_dow = 2;
			int expected_dow = time->dow;
			Assert::AreEqual(actual_dow, expected_dow);
		}
	};
	
	
}


