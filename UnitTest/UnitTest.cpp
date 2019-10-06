#include "pch.h"
#include "CppUnitTest.h"
#include "../Garsim_C/Time.c"
#include <iostream>
#include <fstream>
//#include "../Garsim_C/UnitTest/Days.cpp"




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GetDateTime
{
	TEST_CLASS(GetDateTime)
	{
	public:
		TEST_METHOD(MonthMoreThanThree)
		{
			for (int v = 3; v <= 12; v = ++)
			{
				Assert::IsTrue(month(v, 2020) == 0);
			}
		}
		TEST_METHOD(MonthMoreThanThree1)
		{
			for (int v = 3; v <= 12; v = ++)
			{
				Assert::IsTrue(month(v, 2019) != 0);
			}
		}
		TEST_METHOD(MonthLessThanThree)
		{
			for (int v = 0; v < 3 ; v = ++)
			{
				Assert::IsTrue(month(v, 2020) == 0);
			}
		}
		TEST_METHOD(MonthLessThanThree1)
		{
			for (int v = 0; v < 3; v = ++)
			{
				Assert::IsTrue(month(v, 2019) != 0);
			}
		}
		
		
		TEST_METHOD(days1)
		{
			Assert::IsTrue(days(1980, 2020, 01, 10, 6, 28) == 122);
		}
		TEST_METHOD(days1Not)
		{
			Assert::IsTrue(days(1980, 2020, 01, 10, 6, 28) != 122);
		}
		TEST_METHOD(days2)
		{
			Assert::IsTrue(days(2020, 1980, 01, 10, 6, 28) == 122);
		}
		TEST_METHOD(days2Not)
		{
			Assert::IsTrue(days(2020, 1980, 01, 10, 6, 28) != 122);
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
			char splited[20] = "22-Jan-201900:00:00";//?????????????????????????????
			int actual[6] = { 2019,1,22,0,0,0 };
			int* expected = split(splited);
			Assert::AreEqual(expected[2], actual[2]);
		}
		TEST_METHOD(Split111)
		{
			char splited[20] = "22-Jan-201900:00:00";//?????????????????????????????
			int actual[6] = { 2019,1,22,0,0,0 };
			int* expected = split(splited);
			Assert::AreEqual(expected[1], actual[4]);
		}
		TEST_METHOD(Split2)
		{
			char splited[20] = "22-July-20100:00:00";//?????????????????????????????
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


