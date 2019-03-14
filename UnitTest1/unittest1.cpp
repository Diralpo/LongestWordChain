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
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			int argc = 3;
			char* argv[10];
			argv[1] = "-c";
			argv[2] = "input.txt";
			
			int tag = -1;
			char headCh = '\0', endCh = '\0';
			bool isRing = false;
			std::string filename = std::string();

			getopt(argc, argv, tag, headCh, endCh, isRing, filename);
			//getopt(int argc, char *argv[], int &tag, char &headCh, char &endCh, bool &isRing, std::string &filename);

			Assert::AreEqual(1, tag);
			Assert::AreEqual(headCh, '\0');
			Assert::AreEqual(endCh, '\0');
			Assert::IsFalse(isRing);
			Assert::AreEqual(0, filename.compare("input.txt"));
		}

	};
}