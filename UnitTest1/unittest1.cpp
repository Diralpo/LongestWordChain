#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\LongestWordChain\commenFuncs.h"
#include "..\LongestWordChain\def.h"
#include "..\LongestWordChain\exceptions_.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char* argv[10];
		int tag;
		char headCh, endCh;
		bool isRing;
		std::string filename;

		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			argc = 3;
			argv[1] = "-c";
			argv[2] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);
			//getopt(int argc, char *argv[], int &tag, char &headCh, char &endCh, bool &isRing, std::string &filename);

			Assert::AreEqual(1, tag);
			Assert::AreEqual(headCh, '\0');
			Assert::AreEqual(endCh, '\0');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			argc = 3;
			argv[1] = "-w";
			argv[2] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);

			Assert::AreEqual(0, tag);
			Assert::AreEqual(headCh, '\0');
			Assert::AreEqual(endCh, '\0');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

		TEST_METHOD(TestMethod3)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			argv[1] = "-w";
			argv[2] = "-h";
			argv[3] = "c";
			argv[4] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);

			Assert::AreEqual(0, tag);
			Assert::AreEqual(headCh, 'c');
			Assert::AreEqual(endCh, '\0');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

		TEST_METHOD(TestMethod4)
		{
			// TODO: 在此输入测试代码
			argc = 5;
			argv[1] = "-w";
			argv[2] = "-t";
			argv[3] = "z";
			argv[4] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);

			Assert::AreEqual(0, tag);
			Assert::AreEqual(headCh, '\0');
			Assert::AreEqual(endCh, 'z');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

		TEST_METHOD(TestMethod5)
		{
			// TODO: 在此输入测试代码
			argc = 7;
			argv[1] = "-c";
			argv[2] = "-h";
			argv[3] = "c";
			argv[4] = "-t";
			argv[5] = "z";
			argv[6] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);

			Assert::AreEqual(1, tag);
			Assert::AreEqual(headCh, 'c');
			Assert::AreEqual(endCh, 'z');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

		TEST_METHOD(TestMethod6)
		{
			// TODO: 在此输入测试代码
			argc = 8;
			argv[1] = "-c";
			argv[2] = "-h";
			argv[3] = "c";
			argv[4] = "-t";
			argv[5] = "z";
			argv[6] = "-r";
			argv[7] = "input.txt";
			tag = -1;
			headCh = '\0';
			endCh = '\0';
			isRing = false;
			filename = std::string();
			getopt(argc, argv, tag, headCh, endCh, isRing, filename);

			Assert::AreEqual(1, tag);
			Assert::AreEqual(headCh, 'c');
			Assert::AreEqual(endCh, 'z');
			Assert::IsTrue(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}
	};
}