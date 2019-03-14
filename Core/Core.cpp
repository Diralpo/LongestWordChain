#include "stdafx.h"

#include "core.h"
#include "solver.h"
#include "exceptions_.h"

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多单词数量的
{
    /* 
    using std::cout;
    using std::endl;
    cout << "最多单词数量" << endl;
    */
    if (len <= 0)
    {
        throw IllegalInterfaceParaException();
    }
    if (head != 0 && !(head >= 'a' && head <= 'z') && !(head >= 'A' && head <= 'Z'))
    {
        throw IllegalInterfaceParaException();
    }
    if (tail != 0 && !(tail >= 'a' && tail <= 'z') && !(tail >= 'A' && tail <= 'Z'))
    {
        throw IllegalInterfaceParaException();
    }
    Solver newCore = Solver(words, len, result, head, tail, enable_loop, 0);
    return newCore.gen_chain();
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) // 计算最多字母数量的
{
    /*
    assert(head == 0 || (head <= 'Z' && head >= 'A') || (head <= 'z' && head >= 'a'));
    assert(tail == 0 || (tail <= 'Z' && tail >= 'A') || (tail <= 'z' && tail >= 'a'));
    */
    if (len <= 0)
    {
        throw IllegalInterfaceParaException();
    }
    if (head != 0 && !(head >= 'a' && head <= 'z') && !(head >= 'A' && head <= 'Z'))
    {
        throw IllegalInterfaceParaException();
    }
    if (tail != 0 && !(tail >= 'a' && tail <= 'z') && !(tail >= 'A' && tail <= 'Z'))
    {
        throw IllegalInterfaceParaException();
    }
    Solver newCore = Solver(words, len, result, head, tail, enable_loop, 1);
    return newCore.gen_chain();
}

