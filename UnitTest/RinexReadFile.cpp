#include "pch.h"
#include "CppUnitTest.h"
#include "../Garsim_C/Miscellaneous.c"
#include "../Garsim_C/Custom_Conversion.c"
#include "../Garsim_C/Simulation.c"
#include <iostream>
#include <fstream>




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReadRinexFile
{
	TEST_CLASS(ReadRinexFile)
	{
	public:
		TEST_METHOD(strtodouble)
		{
			char *string = "201900";
			int length = 12;
			double actual = 8.806410 ;
			double expected = str2double(string, length);
			Assert::AreEqual(expected, actual);
			
		}
		TEST_METHOD(strtofloat)
		{
			char* string = "2200";
			int length = 12;
			float actual = 8.806410;
			float expected = str2float(string, length);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(strtoint)
		{
			char* string = "2200";
			int length = 12;
			int actual = 8;
			int expected = str2int(string, length);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(strtoint2) {
			char* string = "2019-11-23 01:08:57";
			int expected_M = 11; //month	= str2int(string + 6, 2);
			int expected_D = 23; //day = str2int(string + 9, 2);
			int expected_H = 1; //hour = str2int(string + 12, 2);
			int expected_min = 8; //minute = str2int(string + 15, 2);
			int expected_S = 57; //second = str2int(string + 18, 3);

			int actual_M = str2int(string + 6, 2);
			int actual_D = str2int(string + 9, 2);
			int actual_H = str2int(string + 12, 2);
			int actual_min = str2int(string + 15, 2);
			int actual_S = str2int(string + 18, 3);

			Assert::AreEqual(expected_D, actual_D);
			/*Assert::AreEqual(expected_M, actual_M);
			Assert::AreEqual(expected_H, actual_H);
			Assert::AreEqual(expected_min, actual_min);
			Assert::AreEqual(expected_S, actual_S);*/
		}
		
		TEST_METHOD(ReadRFile1)
		{
			Simulation sim;
			createSimulation(&sim, (char*)"C:\\Users\\USER\\Desktop\\Garsim_son_hilmi\\Garsim_C\\Garsim_C\\ankr022m.19n1.txt", (char*)"22-Jan-2019 00:12:00", (char*)"22-Jan-2019 00:13:00");
			Satellite sat;
			ReadRinexNMFile(&sim, &sat);
			char *actualFile = "C:\\Users\\USER\\Desktop\\Garsim_son_hilmi\\Garsim_C\\Garsim_C\\ankr022m.19n1.txt";//file name
			char expectedFile[200];
			strcpy(expectedFile, sim.ephFile.fileName);
			Assert::AreEqual(expectedFile, actualFile);

		}
		TEST_METHOD(ReadRFile2)
		{
			Simulation  sim ;
			createSimulation(&sim, (char*)"C:\\Users\\USER\\Desktop\\Garsim_son_hilmi\\Garsim_C\\Garsim_C\\ankr022m.19n1.txt", (char*)"22-Jan-2019 00:12:00", (char*)"22-Jan-2019 00:13:00");
			Satellite sat ;
			ReadRinexNMFile(&sim, &sat);
			for (int i = 1; i < 5; i++) {
				/*
					8.3819D-09
					-7.4506D-09
					-5.9605D-08
					5.9605D-08
				*/
				float actual =8.3819F;//??;
				float expected = sat.alm.GPSA[i - 1];
				Assert::AreEqual(expected, actual);
			}
		}
		TEST_METHOD(ReadRFile3)
		{
			Simulation  sim;
			createSimulation(&sim, (char*)"C:\\Users\\USER\\Desktop\\Garsim_son_hilmi\\Garsim_C\\Garsim_C\\ankr022m.19n1.txt", (char*)"22-Jan-2019 00:12:00", (char*)"22-Jan-2019 00:13:00");
			Satellite sat;
			ReadRinexNMFile(&sim, &sat);
			float *actual = sat.alm.GPUT;
			float expected[] = { 8.3819, -7.4506,-5.9605,5.9605 };
			/*
			    sat->alm.GPUT[0] = str2float(string + 3, 19);
				sat->alm.GPUT[1] = str2float(string + 22, 19);
				sat->alm.GPUT[2] = str2float(string + 44, 50);
				sat->alm.GPUT[3] = str2float(string + 55, 4);
			*/
			for (int i = 0; i < 4; i++) 
			{
				Assert::AreEqual(actual[i], expected[i]);
			}
		}
		TEST_METHOD(ReadRFile4) {
			Simulation  sim;
			createSimulation(&sim, (char*)"C:\\Users\\USER\\Desktop\\Garsim_son_hilmi\\Garsim_C\\Garsim_C\\ankr022m.19n1.txt", (char*)"22-Jan-2019 00:12:00", (char*)"22-Jan-2019 00:13:00");
			Satellite sat;
			ReadRinexNMFile(&sim, &sat);
			char* string = "-842150451	-0.00014921	-6.4801e+00	0	31	-155.16	4.3023e+00	0.87429 -8.1342e+00	0.0083145	4.4480e+00	5153.7	1.44e+00	-5.0291e+00	-0.72328	\n- 842150451 - 0.00011929 - 1.0004e+00	0	58 - 138.66	4.7159e+00 - 0.19375 - 6.9365e+00	0.0018801	2.3711e+00	5153.6	1.66e+00	3.1106e+00 - 0.78957\n- 842150451	0.00017859	2.3874e+00	0	29 - 640.00	4.2670e+00 - 0.22867 - 3.2075e+00	0.0018952	1.2686e+00	5153.6	1.30e+00	8.3819e+00	0.31900\n- 842150451	0.00088708	1.1369e+00	0	12 - 682.50	4.4109e+00	0.17195 - 3.5558e+00	0.0055700	1.3087e+00	5153.6	1.73e+00 - 6.7055e+00	0.29356\n- 842150451	0.00029224 - 7.7307e+00	0	29 - 155.91	4.2405e+00 - 0.30499 - 7.9889e+00	0.0013806	3.9898e+00	5153.8	1.58e+00 - 3.7253e+00 - 0.73169	";
			float expected_af0 = 0.87429;
			float actual_af0 = sat.ephArray[63].af0;

			Assert::AreEqual(expected_af0, actual_af0);

			/*float expected_IODE = 4.4480e+00;
			float actual_IODE = sat.ephArray[50].af0;

			Assert::AreEqual(expected_IODE, actual_IODE);*/


		
		}
		};


}


