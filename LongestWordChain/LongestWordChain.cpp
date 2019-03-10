// LongestWordChain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

#include "commenFuncs.h"
#include "node.h"
#include "def.h"

char *wordlist[20000];
int wordIndex = 0;

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    int tag = -1;
    char headCh = '\0';
    char endCh = '\0';
    bool isRing = false;
    std::string filename = std::string();

    getopt(argc, argv, tag, headCh, endCh, isRing, filename);

    getFileInput(filename);
    char **result = new char*[wordIndex];
    if (tag == 0)
    {
        gen_chain_word(wordlist, wordIndex, result, headCh, endCh, isRing);
    }
    else
    {
        gen_chain_char(wordlist, wordIndex, result, headCh, endCh, isRing);
    }

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
