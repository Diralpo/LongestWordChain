#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Core\def.h"
#include "..\Core\node.h"
#include "..\Core\core.h"
#include "..\Core\solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
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
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			char *wordlist[100];
			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;

			wordlist[0] = "annzcclv";
			wordlist[1] = "klebwukqbui";
			wordlist[2] = "qhqkibinpyew";
			wordlist[3] = "fkapwouje";
			wordlist[4] = "mitecsqa";
			wordlist[5] = "mogowquzdsmto";
			wordlist[6] = "oxkyhmgemdfpq";
			wordlist[7] = "hzvreibfb";
			wordlist[8] = "phgxdlmyrw";
			wordlist[9] = "kuckfwlghglua";
			wordlist[10] = "ucqavnwkqseyy";
			wordlist[11] = "quhxkzqxf";
			wordlist[12] = "iwoegjfbxhu";
			
			wordIndex = 13;
			result = new char*[wordIndex];

			int ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
			
			Assert::AreEqual(3, ans);
			//Assert::AreEqual(headCh, '\0');
			//Assert::AreEqual(endCh, '\0');
			//Assert::IsFalse(isRing);
			//Assert::AreEqual(0, filename.compare("input.txt"));


		}
	};
}