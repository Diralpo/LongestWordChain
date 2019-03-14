#include "stdafx.h"
#include "CppUnitTest.h"
#include <exception>

#include "../Core/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };
			
			wordIndex = 13;
			result = new char*[wordIndex];

			int ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
			
			Assert::AreEqual(4, ans);
			Assert::IsFalse(std::strcmp(result[0], "mogowquzdsmto"));
			Assert::IsFalse(std::strcmp(result[1], "oxkyhmgemdfpq"));
			Assert::IsFalse(std::strcmp(result[2], "quhxkzqxf"));
			Assert::IsFalse(std::strcmp(result[3], "fkapwouje"));
		}

		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];

			int ans = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(4, ans);
			Assert::IsFalse(std::strcmp(result[0], "mogowquzdsmto"));
			Assert::IsFalse(std::strcmp(result[1], "oxkyhmgemdfpq"));
			Assert::IsFalse(std::strcmp(result[2], "quhxkzqxf"));
			Assert::IsFalse(std::strcmp(result[3], "fkapwouje"));
		}

		TEST_METHOD(TestMethod3)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];
			headCh = 'k';

			int ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(3, ans);
			Assert::IsFalse(std::strcmp(result[0], "klebwukqbui"));
			Assert::IsFalse(std::strcmp(result[1], "iwoegjfbxhu"));
			Assert::IsFalse(std::strcmp(result[2], "ucqavnwkqseyy"));
		}

		TEST_METHOD(TestMethod4)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];
			endCh = 'y';

			int ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(3, ans);
			Assert::IsFalse(std::strcmp(result[0], "klebwukqbui"));
			Assert::IsFalse(std::strcmp(result[1], "iwoegjfbxhu"));
			Assert::IsFalse(std::strcmp(result[2], "ucqavnwkqseyy"));
		}

		TEST_METHOD(TestMethod5)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];
			headCh = 'm';

			int ans = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(4, ans);
			Assert::IsFalse(std::strcmp(result[0], "mogowquzdsmto"));
			Assert::IsFalse(std::strcmp(result[1], "oxkyhmgemdfpq"));
			Assert::IsFalse(std::strcmp(result[2], "quhxkzqxf"));
			Assert::IsFalse(std::strcmp(result[3], "fkapwouje"));
		}

		TEST_METHOD(TestMethod6)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];
			endCh = 'e';

			int ans = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(4, ans);
			Assert::IsFalse(std::strcmp(result[0], "mogowquzdsmto"));
			Assert::IsFalse(std::strcmp(result[1], "oxkyhmgemdfpq"));
			Assert::IsFalse(std::strcmp(result[2], "quhxkzqxf"));
			Assert::IsFalse(std::strcmp(result[3], "fkapwouje"));
		}

		TEST_METHOD(TestMethod7)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "annzcclv" };
			wordlist[1] = new char[20]{ "klebwukqbui" };
			wordlist[2] = new char[20]{ "qhqkibinpyew" };
			wordlist[3] = new char[20]{ "fkapwouje" };
			wordlist[4] = new char[20]{ "mitecsqa" };
			wordlist[5] = new char[20]{ "mogowquzdsmto" };
			wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
			wordlist[7] = new char[20]{ "hzvreibfb" };
			wordlist[8] = new char[20]{ "phgxdlmyrw" };
			wordlist[9] = new char[20]{ "kuckfwlghglua" };
			wordlist[10] = new char[20]{ "ucqavnwkqseyy" };
			wordlist[11] = new char[20]{ "quhxkzqxf" };
			wordlist[12] = new char[20]{ "iwoegjfbxhu" };

			wordIndex = 13;
			result = new char*[wordIndex];
			headCh = 'm';
			endCh = 'e';

			int ans = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(4, ans);
			Assert::IsFalse(std::strcmp(result[0], "mogowquzdsmto"));
			Assert::IsFalse(std::strcmp(result[1], "oxkyhmgemdfpq"));
			Assert::IsFalse(std::strcmp(result[2], "quhxkzqxf"));
			Assert::IsFalse(std::strcmp(result[3], "fkapwouje"));
		}

		TEST_METHOD(TestMethod8)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "rlqokvxuq" };
			wordlist[1] = new char[20]{ "vvitmqskdyeap" };
			wordlist[2] = new char[20]{ "llkgasgiuzlgx" };
			wordlist[3] = new char[20]{ "cxadwktc" };
			wordlist[4] = new char[20]{ "yinrlisikdjq" };
			wordlist[5] = new char[20]{ "cbrcxzoyigcv" };
			wordlist[6] = new char[20]{ "roeuzja" };
			wordlist[7] = new char[20]{ "pwwbogbwp" };
			wordlist[8] = new char[20]{ "rjztssi" };
			wordlist[9] = new char[20]{ "vypbjouumrc" };
			wordlist[10] = new char[20]{ "vgorbjxqpap" };
			wordlist[11] = new char[20]{ "vrczrlwavkfq" };

			wordIndex = 12;
			result = new char*[wordIndex];
			isRing = true;

			int ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(5, ans);
			Assert::IsFalse(std::strcmp(result[0], "vypbjouumrc"));
			Assert::IsFalse(std::strcmp(result[1], "cxadwktc"));
			Assert::IsFalse(std::strcmp(result[2], "cbrcxzoyigcv"));
			Assert::IsFalse(std::strcmp(result[3], "vgorbjxqpap"));
			Assert::IsFalse(std::strcmp(result[4], "pwwbogbwp"));
		}

		TEST_METHOD(TestMethod9)
		{
			// TODO: 在此输入测试代码
			//int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
			//int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

			int wordIndex = 0;
			char **result;
			char headCh = '\0';
			char endCh = '\0';
			bool isRing = false;
			char *wordlist[100];

			wordlist[0] = new char[20]{ "rlqokvxuq" };
			wordlist[1] = new char[20]{ "vvitmqskdyeap" };
			wordlist[2] = new char[20]{ "llkgasgiuzlgx" };
			wordlist[3] = new char[20]{ "cxadwktc" };
			wordlist[4] = new char[20]{ "yinrlisikdjq" };
			wordlist[5] = new char[20]{ "cbrcxzoyigcv" };
			wordlist[6] = new char[20]{ "roeuzja" };
			wordlist[7] = new char[20]{ "pwwbogbwp" };
			wordlist[8] = new char[20]{ "rjztssi" };
			wordlist[9] = new char[20]{ "vypbjouumrc" };
			wordlist[10] = new char[20]{ "vgorbjxqpap" };
			wordlist[11] = new char[20]{ "vrczrlwavkfq" };

			wordIndex = 12;
			result = new char*[wordIndex];
			isRing = true;

			int ans = gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);

			Assert::AreEqual(5, ans);
			Assert::IsFalse(std::strcmp(result[0], "vypbjouumrc"));
			Assert::IsFalse(std::strcmp(result[1], "cxadwktc"));
			Assert::IsFalse(std::strcmp(result[2], "cbrcxzoyigcv"));
			Assert::IsFalse(std::strcmp(result[3], "vvitmqskdyeap"));
			Assert::IsFalse(std::strcmp(result[4], "pwwbogbwp"));
		}

        TEST_METHOD(TestMethod10)
        {
            // TODO: 在此输入测试代码
            //int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多单词数量的
            //int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);  // 计算最多字母数量的

            int wordIndex = 0;
            char **result;
            char headCh = '\0';
            char endCh = '\0';
            bool isRing = false;
            char *wordlist[100];

            wordlist[0] = new char[20]{ "annzcclv" };
            wordlist[1] = new char[20]{ "klebwukqbui" };
            wordlist[2] = new char[20]{ "qhqkibinpyew" };
            wordlist[3] = new char[20]{ "fkapwouje" };
            wordlist[4] = new char[20]{ "mitecsqa" };
            wordlist[5] = new char[20]{ "mogowquzdsmto" };
            wordlist[6] = new char[20]{ "oxkyhmgemdfpq" };
            wordlist[7] = new char[20]{ "hzvreibfb" };
            wordlist[8] = new char[20]{ "phgxdlmyrw" };
            wordlist[9] = new char[20]{ "wuckfwlghglup" };

            wordIndex = 13;
            result = new char*[wordIndex];
            int ans = 0;
            try
            {
                ans = gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
            }
            catch (std::exception &excpt)
            {
                Assert::IsFalse(std::strcmp(excpt.what(), " word rings "));
            }
            try
            {
                ans = gen_chain_word(wordlist, -1, result, headCh, endCh, isRing);
            }
            catch (std::exception &excpt)
            {
                Assert::IsFalse(std::strcmp(excpt.what(), " illegal interface parameters "));
            }
            try
            {
                ans = gen_chain_word(wordlist, wordIndex, result, '&', endCh, isRing);
            }
            catch (std::exception &excpt)
            {
                Assert::IsFalse(std::strcmp(excpt.what(), " illegal interface parameters "));
            }
            try
            {
                ans = gen_chain_word(wordlist, wordIndex, result, 'a', '8', isRing);
            }
            catch (std::exception &excpt)
            {
                Assert::IsFalse(std::strcmp(excpt.what(), " illegal interface parameters "));
            }
            

        }
	};
}